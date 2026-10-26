# Controller — Blue Pill / CW1

This is the current classroom Controller project. It uses the STM32F103xB
device configuration, a C8 IOC profile, and conservative 64 KB Flash / 20 KB RAM
linker limits. Keep the supplied startup file, device headers and linker script
together when building this project.

- PA0/PA1/PA2/PA3 -> J1X/J1Y/J2X/J2Y; ADC1 Rank 1/2/3/4.
- ADC calibration and four-halfword circular DMA: `Core/Src/joystick.c`.
- Defaults: min=0, centre=2048, max=4095, deadband=120, in `Core/Inc/joystick_config.h`.
- Both Y direction settings are -1. The application applies the sign flip once.
- CW1A: call the supplied `Joystick_Read()` and identify all four axes.
- CW1B: implement `CW1_NormalizeAxis()` in `Core/Src/student_tasks.c`: signed
  subtraction, range checks, inclusive deadband, separate spans and clamping.
  No completed axis-normalization helper is supplied in the student project.
- Whole-stick PUSH is provided in `Core/Src/joystick_normalization.c`.
- CW1C: measure four-axis endpoints/centres in `Core/Inc/joystick_config.h`,
  rebuild/flash and compare two deadband settings.

Use **CMake: Build → Debug → Run and Debug / STLINK GDB Server**, as in
[Getting started](../../hardware/classwork-setup.md). Select
`build/Debug/Controller.elf` and Continue if the debugger pauses at startup.
The supplied Debug preset selects the student tasks automatically.

Read [CW1](../../notes/02-joystick.md). Mechanical endpoints start at the
default range; measure and update them during CW1C.
