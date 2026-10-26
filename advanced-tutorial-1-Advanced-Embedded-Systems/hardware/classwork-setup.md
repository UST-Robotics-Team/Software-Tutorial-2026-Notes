[Tutorial](../notes/README.md) | [Terms](../notes/00-getting-started.md)

# Getting started

## Two boards, two projects

| Classwork | Open this folder in VS Code | Board |
| --- | --- | --- |
| CW1: joystick | `projects/Controller` | Blue Pill Controller / STM32F103xB |
| CW2 + CW3: IR and ultrasonic together | `projects/MainBoard` | New RDC Mainboard / STM32F405RG profile |

CW2 and CW3 use **one program and one screen**. Connect both sensors, open
MainBoard once, and keep using it for both classworks. The starter already
reads IR A0/D0 for threshold sampling. CW2 adds ADC classification;
CW3 starts as an unfinished measurement task, without an automatic distance.

Both projects include a configured IOC, startup code, HAL, CMake and the familiar
TFT functions. The lecturer supplies ADC and ultrasonic `.c`/`.h` drivers.
You do not need to regenerate CubeMX code or change a build setting for CW2/CW3.
Never flash the Controller program onto the Mainboard or vice versa.

## Build and flash: the same Debug workflow as before

1. Open the **project folder** in VS Code, not the whole repository. If prompted
   to configure the discovered CMake project as an STM32Cube project, choose Yes.
2. Run **CMake: Build** from the command palette and select **Debug**. Resolve
   build errors before flashing.
3. Open **Run and Debug**. If this folder has no launch configuration, choose
   **create a launch.json file**, then **STLINK GDB Server**, as in
   [Tutorial 1's setup guide](https://github.com/UST-Robotics-Team/Software-Tutorial-2026-Notes/blob/main/tutorial-1-basic-io/00-introduction.md#5-generate-a-launchjson-to-flash-code).
   Let the installed STM32 extension generate its machine-specific configuration.
4. Check the board and ELF: `build/Debug/Controller.elf` for CW1;
   `build/Debug/MainBoard.elf` for CW2 **and** CW3. Use Run and Debug to flash.
5. Continue execution if the debugger stops at startup. Check the screen below.

After each code edit: **save → CMake: Build (Debug) → Run and Debug → Continue**.
There is no sensor selection to change, and no terminal command is required for
these classworks. Keep the prepared student build settings. If setup fails, ask a
lecturer to check the toolchain rather than changing compiler or target settings.

When moving from CW1 to CW2, power off, move ST-Link to the Mainboard, and open
its project. When moving from CW2 to CW3, keep the same Mainboard project,
Debug configuration, sensor wiring and ELF. Preserve your CW2 code while adding CW3.

## Connect both Mainboard sensors

Power off before wiring. Match signal labels, not cable colours or connector
position. These mappings passed individual sensor tests on the new board.
The two V pins were reported as 3.3 V; confirm the supply on each classroom board.

| Sensor pin | Mainboard header | MCU pin |
| --- | --- | --- |
| IR VCC / D0 / A0 / GND | UART2 V / T / R / G | Power / PA2 / PA3 ADC1 CH3 / ground |
| Ultrasonic VCC / Trig / Echo / GND | V / PA0 / PA1 / G | Power / PA0 output / PA1 input / ground |

The UART2 connector carries IR signals here; **USART2 serial communication is
disabled**. I2C2 remains available independently on PB10/PB11. TOF is optional and
is disabled until its supply, pull-ups and SHUT wiring are checked; see the
[connector map](pin-mapping.md).

## First-flash check

With both sensors connected, the untouched Mainboard starter should show:

```text
IR + ULTRASONIC
A0:2810 D0:1
SURFACE: ?
UART2 A0:R D0:T
ULTRASONIC CW3
DO CW3 TODO
DIST: -----
NEAR: ---
PA0:T PA1:E
RUN 3 s
```

The A0/D0 numbers are illustrative. Move the IR over black and white paper to
collect samples. `SURFACE: ?` marks the unfinished classification.
`DO CW3 TODO` means the ultrasonic task has not been implemented: the starter
does not send a trigger or provide a reference distance. Test the ultrasonic
sensor after completing and flashing its measurement code.

The supplied app updates the combined screen about every 300 ms. Once CW3 is
implemented, a missing Echo can add up to the driver's 250 ms wait to an update.
A failed measurement shows its error and dashes. IR continues to be read while
CW3 is unfinished or has a measurement error.

The Controller initially shows `CW1 NORMALIZED` / `DO CW1 TODO`;
[CW1](../notes/02-joystick.md) explains acquisition, your normalization calculation,
and the calibration/deadband experiment.

## Where to write code

| File | Your work |
| --- | --- |
| Controller `Core/Src/student_tasks.c` | CW1 joystick read and normalization |
| MainBoard `Core/Src/student_tasks.c` | CW2 A0 threshold classifier; CW3 trigger pulse, Echo width and mm conversion |
| MainBoard `Core/Inc/tutorial_config.h` | Measured ADC threshold/polarity; supplied timing constants |

The app always reads IR and calls `CW2_ProcessIR()` only after a successful
conversion. Use the familiar `tft_prints(0, 2, ...)` for the software label.

For CW3, complete the marked lines in `CW3_MeasureUltrasonic()`, then remove its
early `return false`. The prepared guards and helper functions manage errors.
`DO CW3 TODO` is replaced by your distance or a measurement error; no build
setting changes. The app always uses the student measurement path.
Keep the completed CW2 function while doing CW3.

Keep labels within 16 characters. Use `%u` with `(unsigned)` values;
the TFT formatter does not implement `%lu` or floating-point formatting.
The app commits one full frame. Do not add a second `tft_update()` or `main()`.

## IOC recap with the lecturer

Open the supplied IOC to identify PA2 GPIO input, PA3 ADC1 Channel 3, PA0 Trig,
PA1 Echo, and the TFT pins. Explain why the UART2-labelled connector can carry
analog and GPIO inputs when USART2 is disabled. The pins are already configured;
code regeneration is not part of these classworks. A lecturer who regenerates a
copy must preserve the custom drivers, app calls, CMake sources and USART2 disable.
Use a copy for regeneration practice; the classroom starter is already configured.
