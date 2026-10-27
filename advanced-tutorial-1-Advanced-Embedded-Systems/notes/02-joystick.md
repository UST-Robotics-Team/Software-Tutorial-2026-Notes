[Contents](README.md) | [Previous: ADC](01-adc.md) | [Next: IR](03-ir.md)

# 2. Joysticks — CW1 (Classwork 1)

**A: configure and read ADC → B: implement normalization → C: calibrate and
compare deadbands.** Use the same Controller project throughout.

The display, clocks, buttons, HAL and build support are supplied. You configure
ADC1, write its startup calibration and polling acquisition, collect the axes,
and implement normalization. The app supplies Y-direction handling and PUSH.

Start from your own student Controller folder. A completed lecturer project or
the earlier reference library has different task progress; it is not the starter
for these steps. Keep the supplied function names and signatures, and replace
the TODO bodies rather than adding duplicate functions.

| Stage | What you do | Expected screen after build/flash/Continue |
| --- | --- | --- |
| Before A | Open and run the untouched starter | `CW1 NORMALIZED`, `ADC NOT READY`, `CHECK CW1A SETUP`; RUN increases |
| A: IOC generated | Configure ADC1 IN0 and generate initialization | Still `ADC NOT READY` while startup calibration is a TODO |
| A: startup calibration | Complete `Joystick_Start()` successfully | `READ NOT READY` / `CHECK CW1A READ` while acquisition is unfinished |
| A: one axis | Complete polling and its J1X caller | Changing J1X RAW; `1 AXIS RAW VALID`; other axes/PUSH show dashes |
| A: four axes | Enable/read IN1–IN3 and select four-axis mode | Four RAW values; `4 AXES RAW VALID`; B still controls whether positions remain zero |
| B | Implement the signed calculation | Positive/negative intermediate positions and changing PUSH |
| C | Measure calibration and compare deadbands | Explain your own measurements and the behavior of both settings |

The title always says `CW1 NORMALIZED`; it does not change at each stage.
`RAW VALID` confirms raw-code checks, not completion of normalization or calibration.

## 1. Know which number you are looking at

| Number | Range | Meaning |
| --- | --- | --- |
| Raw ADC | 0–4095 | Voltage code |
| Signed X/Y | -1 to +1 | Axis position and direction |
| PUSH | 0–1 | Whole-stick displacement magnitude, not force |

Each stick has two potentiometers. The assembled Controller needs no additional
sensor wires. Its map is:

| Axis | MCU pin | ADC1 channel | Output slot |
| --- | --- | --- | --- |
| J1 X | PA0 | 0 | `values[0]` |
| J1 Y | PA1 | 1 | `values[1]` |
| J2 X | PA2 | 2 | `values[2]` |
| J2 Y | PA3 | 3 | `values[3]` |

The channel selects a physical input. In this polling exercise every requested
channel uses **Rank 1**; your C code selects the output slot. Four channels are
four sequential measurements through ADC1, not four simultaneous ADCs.

| File in your Controller folder | Your work |
| --- | --- |
| `Controller.ioc` | Configure IN0 first, then IN1/IN2/IN3; generate initialization |
| `Core/Src/joystick.c` | `Joystick_Start()` and `Joystick_ReadChannel()` |
| `Core/Src/student_tasks.c` | `CW1_ReadJoystick()` and `CW1_NormalizeAxis()` |
| `Core/Inc/joystick_config.h` | Axis count, measured MIN/CENTRE/MAX, Y direction and deadband |

Initialization belongs to the IOC and its generated files. Write the acquisition
and calculation in the existing independent task files. Use the generated
`hadc1`; do not create another handle, `main`, or ADC initialization function.

## 2. CW1A — configure and acquire

### Open, build and run the starter

Open the **Controller folder itself** in VS Code. Use the normal Debug workflow
from [Classwork setup](../hardware/classwork-setup.md), with the ST-Link attached
to the Controller rather than the MainBoard.

If initial STM32 project setup is requested, choose Controller and **Debug** and
keep the correct F103 target and complete Arm toolchain. Use the STM32 sidebar's
project setup action if needed; you do not need to find a particular command
name in the Command Palette. If a debug launch configuration is missing, create
STLINK GDB Server through the STM32 extension as described in the setup guide.

For every application edit in this walkthrough:

1. Save the changed source files.
2. Run **CMake: Build** and choose **Debug**; resolve build errors first.
3. Open **Run and Debug**, use **STLINK GDB Server**, and verify that its program
   is this folder's `build/Debug/Controller.elf`.
4. Press **F5** to flash and start debugging. If it pauses
   at the entry breakpoint, press **Continue / F5** to let the program run.
5. Check the expected screen for the current stage before making another change.

The untouched starter shows `ADC NOT READY` / `CHECK CW1A SETUP` with increasing
RUN time. This is expected: ADC1 is deliberately disabled and its acquisition
functions are TODOs. A running title is not evidence that ADC acquisition works.

After an **IOC edit**, first save the IOC, **Generate Code**, and inspect the
result; then use the same save/build/flash/Continue workflow. Changing an IOC or
a C file alone does not update firmware already running on the board.

### First read J1 X

#### A1. Configure PA0 and ADC1

Open your `Controller.ioc` in CubeMX. Follow the
[seven screenshot steps](01-adc.md#cubemx-screenshot-walkthrough).
In **Pinout & Configuration → Analog → ADC1**, click **PA0 on the chip diagram**
and select **ADC1_IN0**. If IN0 is pink/unavailable, this replaces the starter's
passive `GPIO_Analog` assignment. Select ADC1, not ADC2.

Keep the other three pins as supplied for now. Use the
[ADC settings table](01-adc.md#2-configure-the-adc-yourself):

- Independent mode; scan, continuous and discontinuous conversion **Disabled**.
- Software start; right alignment; **Enable Regular Conversions = Enable**.
- **Number Of Conversion = 1**, **Rank 1 = Channel 0**, sampling **71.5 cycles**.
- No ADC DMA request or ADC interrupt.
- Keep the prepared APB2 clock at 72 MHz and ADC prescaler `/6`, giving 12 MHz.

**Before continuing:** identify which setting chooses the input, which starts a
conversion, and which determines its sample window. Explain why repeated
software requests do not require Continuous Conversion Mode.

#### A2. Generate, inspect and build

Save and click **Generate Code**. Check these items in the same project folder:

- `Core/Src/adc.c` and `Core/Inc/adc.h` now exist.
- `adc.c` has ADC1, the single software-triggered conversion and 71.5-cycle setup.
- `main.c` calls `MX_ADC1_Init()` once, **before** `TutorialApp_Init()`.
- The app/TFT initialization and update calls are retained.
- `joystick.c`, `student_tasks.c`, `joystick_config.h` and the custom sources in
  CMake remain present. Do not hand-copy another init call into `main.c`.

Build and flash. `ADC NOT READY` is still expected because generating initialization
does not fill `Joystick_Start()`. Use your own folder: the directory shown in a
screenshot is only the lecturer's demonstration copy.

#### A3. Implement startup self-calibration

In both `Core/Src/joystick.c` and `Core/Src/student_tasks.c`, add the generated
header alongside the existing includes, after ADC1 generation:

```c
#include "adc.h"
```

In `joystick.c`, replace the TODO body of `Joystick_Start()`. Look up
`HAL_ADCEx_Calibration_Start()` and use the existing `hadc1`. Report whether the
status equals `HAL_OK`. **`HAL_OK` is numeric zero**, so do not return a HAL status
directly as a Boolean: success must produce `true`, not `false`.

The app already calls this function once after initialization. Do not recalibrate
for every reading or add a second startup call. Electrical ADC self-calibration
is different from measuring mechanical joystick travel in C.

**Build/flash/Continue:** if calibration succeeds, the still-unfinished reading
task produces `READ NOT READY` / `CHECK CW1A READ`. This is the next checkpoint.
If `ADC NOT READY` remains, check the calibration result and generated setup.

#### A4. Implement one complete channel read

Still in `joystick.c`, implement the existing
`Joystick_ReadChannel(uint32_t channel, uint16_t *raw)` using the
[ADC API contracts](01-adc.md#3-write-one-complete-conversion).

The `channel` parameter selects an input. The `raw` pointer gives the location
where a successful result must be written. Reject a null output pointer.

Work out and implement this sequence:

```text
Configure requested channel → Start → Wait for completion → Get value → Stop
                                                                         ↓
                                                              Write output; return true
```

Use `ADC_ChannelConfTypeDef`, the requested channel, `ADC_REGULAR_RANK_1`, and
`ADC_SAMPLETIME_71CYCLES_5`. The HAL APIs to read are `HAL_ADC_ConfigChannel`,
`HAL_ADC_Start`, `HAL_ADC_PollForConversion`, `HAL_ADC_GetValue`, and `HAL_ADC_Stop`.

Your function must:

- Check operations that return a HAL status.
- Wait for completion with a finite timeout, such as **10 ms**. This is a maximum
  wait, not a fixed delay or sample interval.
- Read the result only after completion is confirmed.
- Stop/clean up an operation you started, including after a failed wait.
- Hold the value locally until the full operation, including stop, succeeds.
- Leave `*raw` unchanged and return `false` on failure; publish the result and
  return `true` only on success. A valid result of zero is not an error.

**Before continuing:** explain what happens if the ADC never reports completion.
Why is `HAL_Delay()` alone insufficient? Where does `HAL_ADC_GetValue()` obtain
its result? Find the relevant descriptions in the bundled HAL source rather than
guessing the arguments.

Implementing this function alone does not finish the app's caller, so the screen
may still show `READ NOT READY` until A5 is complete.

#### A5. Connect your reader to J1X

Open `Core/Src/student_tasks.c` and find the existing `CW1_ReadJoystick(values)`.
Keep `JOYSTICK_AXIS_COUNT` at **1U** in `Core/Inc/joystick_config.h`.

Use your own `Joystick_ReadChannel()` to request `ADC_CHANNEL_0` and store the
result in `values[0]`. That function writes through a pointer, so pass the address
of the element, `&values[0]`. Return its actual success/failure result, rather than
unconditionally returning `true`. Do not create a second local `values` array.

**Build/flash/Continue:** move the first stick left/right. Expect:

- J1X RAW changes within 0–4095 and the screen shows `1 AXIS RAW VALID`.
- J1Y, J2X, J2Y and both PUSH fields show dashes because they are not measured yet.
- J1X signed position remains zero while B is a TODO. This does not prevent testing A.

Predict the released and two end-stop readings first, then record observations.
Use one RAW reading to estimate voltage with the assumed 3.3 V reference. The
released value need not be exactly 2048 and the stops need not be exactly 0/4095.

### Extend to all four axes

#### A6. Enable the other physical inputs and regenerate

Return to the **same** IOC. Assign:

| Pin | Function to select |
| --- | --- |
| PA0 | Keep ADC1_IN0 |
| PA1 | ADC1_IN1 |
| PA2 | ADC1_IN2 |
| PA3 | ADC1_IN3 |

Use the pin menu if a pink checkbox prevents selection. Keep **scan off,
continuous off, one regular conversion, Rank 1**. The generated initial Rank 1
can remain Channel 0; your runtime function selects a different channel per call.
Do not change the conversion count to four or add ADC DMA.

Save and Generate Code. Repeat the A2 checks, including preservation of your
completed independent functions and one generated ADC init call.

#### A7. Collect channels in the required order

Extend the existing `CW1_ReadJoystick()` in `student_tasks.c` to request
channels 0/1/2/3 into `values[0]/[1]/[2]/[3]`, using the map above. Reuse your
one-channel function; no new ADC driver is needed. You may use explicit calls or
a channel table and loop, but all requested reads must succeed before the caller
returns `true`. If any fails, return `false`; the app hides that incomplete set.

Then edit the existing macro in `joystick_config.h`:

```c
#define JOYSTICK_AXIS_COUNT 4U
```

Keep one definition. If you use a loop, let `JOYSTICK_AXIS_COUNT` control the
number of requested axes; the starter allows 1 or 4.

#### A8. Check the complete mapping

**Build/flash/Continue:** confirm `4 AXES RAW VALID`. Move one axis at a time and
check J1X, J1Y, J2X and J2Y separately. Record approximate released values and
both stops. Correct a wrong input/slot mapping before continuing to B.

The four signed positions and both PUSH values remain zero until normalization
is implemented. The title and `RAW VALID` message alone do not prove B is done.

**Explain A:** Why can four channels all use Rank 1? What decides the array order?
Are the four samples simultaneous? How is failure different from a successful
zero? ADC/DMA acquisition from the earlier reference must not run alongside your
polling path.

## 3. CW1B — implement normalization

### Understand the calculation before editing

We want a released stick to mean zero and the two directions to approach -1/+1.
`raw / 4095.0f` instead puts the released stick near 0.5.

![Deadband and separate negative/positive spans](images/joystick-normalization.png)

Open `CW1_NormalizeAxis()` in the **same** `student_tasks.c`. Replace its
placeholder body while preserving its five parameters:

| Parameter | Meaning |
| --- | --- |
| `raw` | Current code from the selected axis |
| `minimum` | Lowest calibrated RAW value for that axis |
| `centre` | Released RAW centre |
| `maximum` | Highest calibrated RAW value |
| `deadband` | Half-width of the zero region, in ADC counts |

The app calls this function for each measured axis and supplies calibration
from `joystick_config.h`. Your job is to calculate one signed position, not to
start ADC again, redraw the display, or calculate PUSH inside this function.

Derive and implement the following:

1. Subtract centre from RAW to find the signed offset. Preserve negative results.
2. Calculate the two centre-to-endpoint spans separately; they can differ.
3. Before division, reject invalid calibration: if either span is less than or
   equal to the deadband, return zero.
4. Return zero inside the **inclusive** centre deadband.
5. Outside it, remove the deadband from the remaining travel and scale each
   side separately, preserving continuity and sign. Derive the negative side.
6. Clamp the result to [-1,1] and return the calculated value, not the placeholder zero.

Defaults are MIN=0, CENTRE=2048, MAX=4095, deadband=120. The zero region is
1928–2168. On the positive side, raw 3132 has moved 964 counts beyond the zero
region, out of 1927 usable counts: approximately +0.50.

Use all five parameters so measured calibration can replace the defaults in C.
Do not hard-code 2048, 4095 or 120 in the calculation. Use floating-point division
before the result is truncated. If a signed difference is stored in an unsigned
variable, negative positions can become large positive values; choose suitable
types or convert to float before subtracting.

The app applies Y direction **after** your return. Keep this function's positive
direction tied to increasing RAW, and do not reverse Y here again.

### Predict, then inspect the function with fixed inputs

| raw | MIN / CENTRE / MAX / deadband | Expected result |
| --- | --- | --- |
| 2100 | 0 / 2048 / 4095 / 120 | 0 |
| 1928 or 2168 | 0 / 2048 / 4095 / 120 | 0: inclusive boundaries |
| 3132 | 0 / 2048 / 4095 / 120 | approximately +0.50 |
| 964 | 0 / 2048 / 4095 / 120 | -0.50 |
| 1000 | 200 / 1900 / 3700 / 100 | -0.50 |
| 4095 | 200 / 1900 / 3700 / 100 | +1.00 after clamping |
| 1700 | 2000 / 1900 / 3700 / 100 | 0: invalid calibration |
| 4095 | 0 / 120 / 4095 / 120 | 0: one span equals the deadband |

These are controlled function inputs; you do not need to hold the physical stick
at an exact code such as 3132. First calculate the expected results on paper.
To inspect your implementation using the same project, you can temporarily add
these two lines near the start of `CW1_ReadJoystick()`, before any return:

```c
/* Temporary calculation check; remove after inspecting in the debugger. */
volatile float check = CW1_NormalizeAxis(3132U, 0U, 2048U, 4095U, 120U);
(void)check;
```

Save and build Debug. Place a breakpoint on `(void)check`, start debugging and
Continue past the entry breakpoint if necessary. When it pauses on that line,
inspect the local variable `check` in the **Variables** pane; you can also add
`check` to Watch while in that function's scope. For this case it should be about
0.50. Change the five test arguments to another row, rebuild/reflash, and inspect
again. The non-default case checks whether your function uses its parameters.

After inspecting the cases, remove the two temporary lines/comment and their
breakpoint, then rebuild/flash/Continue for live testing. This check calls your
function; it does not replace its implementation or change ADC configuration.

### Verify B with real movement

Move slowly through the centre and toward both stops. Look for intermediate
positive and negative values, not just -1, 0 and +1. Just outside the deadband,
the position should start near zero rather than jump to a large value. The screen
shows two decimal places, so a very small nonzero result may still print as 0.00.

Both PUSH values should now respond to stick movement. With default calibration,
a physical stop might show only about 0.85; measure its actual RAW endpoint in C
before treating that as an ADC problem.

`CHECK CW1B MATH` means the app received a non-finite or out-of-range result.
It does not detect every wrong formula: a function that always returns zero can
pass that check. Verify both your calculations and the physical behavior.

## 4. CW1C — calibrate and compare deadbands

### C1. Measure your own RAW range

ADC self-calibration does not locate the mechanical centre or stops. The default
0 / 2048 / 4095 values are starting settings, not measurements of your Controller.
Use the screen's **RAW column**, not the normalized position, to fill this table:

| Axis | Smallest repeatable RAW at a stop | Average released RAW | Largest repeatable RAW at a stop |
| --- | --- | --- | --- |
| J1 X | | | |
| J1 Y | | | |
| J2 X | | | |
| J2 Y | | | |

For each axis, move to both stops several times and record repeatable extrema.
Then release it, wait for it to settle and record at least ten readings. Average
and round to an integer for its centre. Retain the individual readings so you can
describe idle variation. Repeat for all four axes; one stick's calibration does
not automatically apply to the other.

### C2. Replace the existing calibration macros

Open `Core/Inc/joystick_config.h`. Update the twelve existing calibration values:

| Axis | Existing macros to edit |
| --- | --- |
| J1 X | `J1_X_MIN`, `J1_X_CENTRE`, `J1_X_MAX` |
| J1 Y | `J1_Y_MIN`, `J1_Y_CENTRE`, `J1_Y_MAX` |
| J2 X | `J2_X_MIN`, `J2_X_CENTRE`, `J2_X_MAX` |
| J2 Y | `J2_Y_MIN`, `J2_Y_CENTRE`, `J2_Y_MAX` |

For example, **only if** an axis measured minimum 200, centre 1900 and maximum
3700, the J1X entries would be:

```c
/* Example only: replace these with your own J1X measurements. */
#define J1_X_MIN 200U
#define J1_X_CENTRE 1900U
#define J1_X_MAX 3700U
```

Edit existing definitions rather than adding duplicates. Keep
MIN < CENTRE < MAX, with both spans greater than the selected deadband.
Keep `JOYSTICK_AXIS_COUNT=4U`. Do not swap MIN and MAX to reverse a direction.
There is no new sampling or automatic-calibration function to write in C.

### C3. Rebuild and check the measured endpoints

Save, build Debug, flash and Continue. Release each stick, then move each axis
slowly through its travel and to both stops. With your measured calibration,
expect a released value of zero inside the deadband and stop positions approaching
-1/+1. Default maximum 4095 with a real stop at RAW 3800 gives about +0.85; updating
the measured endpoint changes the scale rather than the voltage being measured.

Both Y-direction macros start at -1. If physical direction needs correcting,
change the corresponding direction macro and rebuild/flash. The app applies it
once after normalization. RAW MIN/MAX stay ordered numerically even for a
reversed display direction.

### C4. Compare deadbands while holding calibration fixed

First test the current setting:

```c
#define JOYSTICK_DEADBAND 120U
```

Then replace that one existing definition with:

```c
#define JOYSTICK_DEADBAND 60U
```

Rebuild/flash after each change. Keep the measured MIN/CENTRE/MAX values and
Y-direction settings the same. Observe both idle stability and the small movement
required before a nonzero output appears:

| Deadband | Released behavior | Small intentional movement / onset of response |
| --- | --- | --- |
| 120 | Record what you observe | Record what you observe |
| 60 | Record what you observe | Record what you observe |

A larger deadband covers more idle variation but ignores more small intentional
movement. A smaller deadband responds sooner but may expose jitter. A stable
centre can give zero with both; that is a valid result, so compare movement
sensitivity as well. Select a suitable value and explain the tradeoff.

Save your final choice and rebuild/flash once more if you changed it. C is complete
when you can show your four-axis measurements and explain both observations.
B and C need no additional IOC generation unless you change peripheral settings.

## 5. PUSH and explaining your result

The supplied PUSH calculation is `min(1, sqrt(x*x + y*y))`. For example, x=0.30
and y=0.40 give PUSH=0.50. It combines displacement along both axes, not physical
force. Diagonal travel can exceed length 1, so it is capped at 1. PUSH is shown
only after all four axes are enabled; it is calculated after Y-direction handling.

Show and explain, without additional marks:

- **A:** your IOC configuration, once-only ADC self-calibration, complete polling
  sequence, four-axis mapping, one voltage estimate, and failure versus valid zero.
- **B:** your implementation, signed/floating-point calculations, boundary and
  asymmetric-range predictions, continuity and clamping. Demonstrate intermediate
  positions and explain why default endpoint values may need calibration.
- **C:** four measured calibration records, zero within the released deadband,
  physical stops approaching -1/+1, correct direction, and observations for both
  deadbands. Explain why ADC self-calibration did not supply these values.
- **PUSH:** both values change within 0–1, and you can explain the 0.3/0.4 example.

ADC/joystick CW1 ends here. Move to the MainBoard for
[IR CW2](03-ir.md) and [ultrasonic CW3](04-ultrasonic.md); TOF is the homework.
For stage-specific problems, use [Troubleshooting](07-troubleshooting.md).

The earlier complete library/DMA implementation remains available in
[reference](https://github.com/UST-Robotics-Team/Software-Tutorial-2026-Notes/tree/main/reference/Controller).
Both teaching groups may use it. Keep the classroom polling acquisition separate
from that DMA path. Explain the code you use and repeat a prediction after changing
a channel or calibration value; a working screen alone does not explain conversion.
