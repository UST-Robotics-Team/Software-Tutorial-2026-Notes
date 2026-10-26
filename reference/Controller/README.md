# Released Controller Reference v1

Complete library-based ADC/joystick implementation retained for both teaching
groups. The original student Controller directory remains unchanged. This is a
separate reference project.

Open this folder in VS Code. Trust only this folder if prompted. Set up the
existing STM32Cube project as STM32F103C8T6 / Cortex-M3 / GCC, then use Debug
and build. Create the ST-Link GDB Server launch configuration if absent, and
select `build/Debug/Controller.elf`. Press F5 and Continue after the entry breakpoint. This code is
for the STM32F103 Blue Pill Controller, not the Mainboard.

The reference includes four-channel circular ADC DMA, signed normalization,
deadband, both Y direction settings, and whole-stick PUSH. Default endpoints
are starting values, not measured calibration. The screen is `CW1 NORMALIZED`.

`Core/Src/joystick.c` contains acquisition, `joystick_normalization.c` contains
the completed library calculations, and `student_tasks.c` connects them to the
existing display. There are no unfinished CW1 task bodies in this reference.

All bundled HAL/CMSIS/display licenses remain in their original files.
