# Controller — Blue Pill / CW1

One Controller project covers **A: ADC acquisition, B: normalization,
C: calibration and deadband**. It uses the STM32F103xB device configuration,
a C8 IOC profile, and conservative 64 KB Flash / 20 KB RAM limits.

The display, clocks, buttons, UART and SWD are prepared. **ADC1 starts disabled**;
PA0-PA3 are passive analog GPIOs. There is no automatic conversion or DMA path.
The untouched starter builds and shows `CW1 NORMALIZED`, `ADC NOT READY`,
`CHECK CW1A SETUP`, and increasing RUN time.

| File | Student work |
| --- | --- |
| `Controller.ioc` | Enable ADC1 IN0 first, then IN1/IN2/IN3; use single software-triggered polling |
| `Core/Src/joystick.c` | Implement startup ADC calibration and one-channel polling with status checks |
| `Core/Src/student_tasks.c` | Assemble one/four channel readings; implement signed normalization |
| `Core/Inc/joystick_config.h` | Change axis count from 1 to 4; record calibration and choose deadband |

Generate ADC1 code before adding `#include "adc.h"` to both student-edited C
files. Keep scan/continuous off, one regular conversion, Rank 1, 71.5-cycle
sampling, and no ADC DMA/interrupt. Select the requested channel for each read.
PA0/PA1/PA2/PA3 correspond to J1X/J1Y/J2X/J2Y; each conversion uses Rank 1.

The app calls `Joystick_Start()` once, then `CW1_ReadJoystick()` about every
100 ms. A failed read hides the current sample. Unmeasured axes/PUSH show dashes
in one-axis mode. Normalized values stay zero until CW1B is implemented.
PUSH and TFT formatting are supplied. Both Y directions start at -1 and the app
applies them once, after normalization. Default endpoints are not measured values.

Use **CMake: Build → Debug → Run and Debug / STLINK GDB Server** as in
[setup](../../hardware/classwork-setup.md). Select `build/Debug/Controller.elf`
and Continue after the entry breakpoint. Rebuild/reflash after each change;
regenerate after IOC edits. Keep application code out of generated ADC functions.

Follow the [ADC explanation](../../notes/01-adc.md),
[CW1 instructions](../../notes/02-joystick.md) and
[IOC guide](../../hardware/ioc-guide.md). The earlier complete DMA implementation
remains in the repository's `reference/Controller` directory.
