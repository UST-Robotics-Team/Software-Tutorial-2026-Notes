# IOC Guide: Settings and Their Purpose

[Tutorial](../README.md) | [Setup](classwork-setup.md) |
[Terms](../notes/00-getting-started.md)

The **`.ioc` file** stores STM32CubeMX pin/peripheral configuration. Generation
creates initialization code; application code still starts operations.
For example, generated `MX_ADC1_Init()` configures ADC. Your `Joystick_Start()`
performs one startup calibration; your polling function requests each conversion.

Controller ADC1 and Mainboard ADC1/TIM2/I2C2 start disabled for the corresponding
student exercises. The display, buttons, clocks and debug setup are prepared. Open the IOC inside the
extracted project. Keep the skeleton's display, UART, debug and clock setup;
menu labels may vary by CubeMX version. Pin settings do not confirm physical
sensor connections.

## 1. Controller: configure ADC1 yourself for CW1A

Open `projects/Controller/Controller.ioc` (STM32F103C8T6). The starter deliberately
has **no ADC1 or ADC DMA configured**. PA0-PA3 start as passive analog GPIOs;
this alone does not connect them to an ADC. The unedited project can build and
show the unfinished setup message without generated `adc.c` or `adc.h` files.

Follow the [seven-step CubeMX screenshot walkthrough](../notes/01-adc.md#cubemx-screenshot-walkthrough)
for the exact panels and dropdowns. In **Pinout & Configuration → Analog → ADC1**,
first assign **PA0 → ADC1_IN0** using the chip pin menu. IN0 can be pink/unavailable
while the starter's `GPIO_Analog` assignment is active; selecting ADC1_IN0 from
PA0's menu replaces it and checks IN0. Use the following settings, then explain
their meanings:

| Setting | Value | Purpose |
| --- | --- | --- |
| Scan | Disabled | Select one channel per call |
| Continuous | Disabled | Software requests every conversion |
| Discontinuous | Disabled | Not used |
| Trigger | Software start | Your polling function starts it |
| Alignment | Right | Integer raw code |
| Enable Regular Conversions | Enable | Use the regular conversion group |
| Regular conversions | 1 | One result per request |
| Rank 1 | Channel 0 initially | Select the first joystick input |
| Sampling | 71.5 cycles | Allow time for input settling |
| ADC DMA / interrupt | Not enabled | Use polling |

The F103 ADC is fixed at 12-bit. Keep HCLK/APB2 at 72 MHz and the prepared ADC
prescaler `/6`, giving 12 MHz. Check the ADC clock when enabling ADC1; it is not
the TFT update rate. Keep the remaining clock, display, UART and SWD settings.

Save and **Generate Code**. Check that `adc.c`/`adc.h` exist, that the initialization
matches the table, and that generated `main.c` calls `MX_ADC1_Init()` once before
`TutorialApp_Init()`. Add `#include "adc.h"` to `joystick.c` and `student_tasks.c`
when implementing acquisition. Use the generated handle, not another `hadc1`.
The app already calls your `Joystick_Start()` once; do not add a duplicate call.

After one axis works, enable **IN1/IN2/IN3 on PA1/PA2/PA3** and generate again.
Keep scan/continuous off and the number of regular conversions at **1**.
For each read, your `Joystick_ReadChannel()` configures the requested channel
as Rank 1 with 71.5-cycle sampling, then completes one conversion and stops.
The four inputs are read sequentially, not as a four-rank scan or DMA buffer.
Set `JOYSTICK_AXIS_COUNT=4U` only after implementing all four reads.

Inspect the generated GPIO analog modes for PA0-PA3. Keep the app/TFT calls and
custom sources after generation. Use the same `Controller.elf` and Debug workflow
through A/B/C; there is no second Controller project or build mode.

For the exact order of function edits and screen checkpoints, follow
[CW1A step by step](../notes/02-joystick.md#2-cw1a--configure-and-acquire):

1. Generate ADC1 initialization and build; the startup TODO still gives
   `ADC NOT READY`.
2. Complete `Joystick_Start()` calibration. Compare its HAL status with `HAL_OK`
   rather than returning the status as a Boolean: `HAL_OK` is zero.
3. Successful startup with acquisition still unfinished gives `READ NOT READY`.
4. Implement both `Joystick_ReadChannel()` and its J1X caller to reach
   `1 AXIS RAW VALID` with `JOYSTICK_AXIS_COUNT=1U`.
5. Enable IN1–IN3, regenerate, extend the caller and select `4U` to reach
   `4 AXES RAW VALID`. Every conversion still uses Rank 1.

Neither raw-valid message confirms B or C. The normalization stub returns zero
until you replace it; endpoint and centre defaults still need measurement.
After an application-only edit, rebuild/flash; regenerate only when you change
IOC configuration. In particular, changing deadband or measured endpoints does
not require another ADC setup function.

## 2. Mainboard CW2: GPIO and one ADC conversion

The starter keeps ADC1 disabled, PA2 passive input and PA3 analog GPIO. Preserve
SPI1/display DMA, buttons, LEDs, clock tree, USART1 and SWD. USART2 stays disabled.
For CW2A, check/set PA2 GPIO_Input / no pull; generate and implement D0 reading.
For CW2B enable ADC1 IN3 on PA3 and use:

| Setting | Value |
| --- | --- |
| ADC prescaler | PCLK2 / 4 = 21 MHz |
| Resolution / alignment | 12-bit / right |
| Scan / continuous / discontinuous | Disabled |
| Trigger edge/source | None / software start |
| Number / Rank 1 | 1 / Channel 3 |
| Sampling | 144 cycles |
| ADC DMA/interrupt | Not enabled |

Generate `adc.c`/`adc.h` and one `MX_ADC1_Init()` call. Add the generated header
when writing `IR_Read()`. Do not add another init call in USER CODE and do not
copy the F103 self-calibration API. See [CW2](../notes/03-ir.md).

## 3. Mainboard CW3: GPIO and generated TIM2

Set PA0 to push-pull output, no pull, initial LOW; PA1 input / no pull. Enable
TIM2 Internal Clock, up-counting, prescaler 83, period 4294967295, division DIV1,
with no timer interrupt/DMA. APB1 timer clock is 84 MHz, so the counter is 1 MHz.

Generate `tim.c`/`tim.h` and one `MX_TIM2_Init()` before the app. Add the header
when implementing `Ultrasonic_Start()` and the counter read. Start the generated
timer once with HAL; do not reset/program TIM2 registers or initialize GPIO in
an application file. Student code supplies trigger, edge waits, timeouts and
conversion. SPI display DMA stays enabled; it is separate from timer/ADC DMA.

## 4. Mainboard optional TOF: generated I2C2

Enable I2C2 on PB10 SCL / PB11 SDA, standard mode 100 kHz, 7-bit addressing,
own address 0, dual address/general call off. Check AF4 open-drain and compatible
external pull-ups. The module supply, pull-ups and SHUT handling remain pending.
Keep TOF_WIRING_CONFIRMED=0 until checked.

Generate `i2c.c`/`i2c.h` and one `MX_I2C2_Init()` before the app. Implement the
probe and transfers in independent TOF/platform files. Use device argument 0x52
(7-bit address 0x29 shifted once), not Own Address. The sensor uses 16-bit register
addresses. Bus initialization does not initialize the optical ranging engine.

## 5. Save/generate without losing the starter

CW1A requires configuring and regenerating Controller. Mainboard CW2/CW3 and
optional TOF also require their own IOC configuration/generation. Use STM32CubeMX 6.18.1 with FW_F1 V1.8.7 for Controller;
Mainboard uses FW_F4 V1.28.3. Install the required firmware package before class.
Keep a copy of your work before generation. Generation/build checks do not replace
measurements on your Controller or sensor tests on Mainboard.

Both classroom projects use normal CubeMX-generated initialization calls.
Mainboard ADC1/TIM2/I2C2 are enabled progressively; no application file initializes
them a second time. GPIO initial states, including all four inactive-high LEDs,
are recorded in IOC rather than patched into generated C.

1. **Project Manager → Project:** retain the CMake target/toolchain.
2. **Code Generator:** retain user code and separate peripheral `.c/.h` files.
3. Save IOC → **Generate Code** → review the diff.
4. Preserve `TutorialApp_Init()/Update()`, custom sources/includes and Controller
   normalization source in the build.
5. Keep USART2 disabled and the fixed signal map. Preserve the student tasks,
   bounded-wait contracts and measurement-validity checks.
6. Reconfigure/build and check the expected starter screen before sensors.

Read the generated `adc.c`, `i2c.c`, `main.c` and `ultrasonic_gpio_port.c`
to connect settings with runtime behavior. A valid IOC/build does not confirm wiring.

UART = **Universal Asynchronous Receiver/Transmitter**; TFT =
**Thin-Film Transistor** display; SWD = **Serial Wire Debug**.
Their existing board settings remain in the skeleton.
