# MainBoard — IR and Ultrasonic Together

Use **CMake: Build → Debug → Run and Debug / STLINK GDB Server**, as before.
Flash `build/Debug/MainBoard.elf` and Continue if paused at startup.
CW2 and CW3 share this one project, one ELF and one screen.

- IR: UART2 **V/T/R/G = VCC/D0/A0/GND**. D0 PA2 input; A0 PA3 ADC1 CH3.
- Ultrasonic: **V/PA0/PA1/G = VCC/Trig/Echo/GND**. Fixed Trig PA0 / Echo PA1.
- Both V pins were reported as 3.3 V; confirm your board supply. USART2 stays
  disabled. I2C2 PB10/PB11 stays independent; TOF is initially disabled.

The starter shows IR A0/D0 for sampling and DO CW3 TODO for ultrasonic.
Ultrasonic does not trigger or display a distance until its task is implemented.
In `Core/Src/student_tasks.c`:

1. CW2: classify `sample->raw` with a threshold chosen from black/white samples.
2. CW3: fill trigger timing, pulse width and distance calculation in the prepared
   function. Remove its top early return after completing the TODOs.

After implementing CW3, the app displays your result or error. Keep CW2.
The supplied helpers own initialization, bounded waits and diagnostic state.

[CW2](../../notes/03-ir.md) | [CW3](../../notes/04-ultrasonic.md) |
[CW3 task guide](cw3-task-guide.md) | [Setup](../../hardware/classwork-setup.md) |
[IOC guide](../../hardware/ioc-guide.md)
