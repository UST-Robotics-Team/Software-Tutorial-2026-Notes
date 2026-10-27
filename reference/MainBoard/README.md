# Complete MainBoard Reference

This standalone project preserves the earlier complete IR and ultrasonic
application logic. The completed task body comes from the earlier lecturer
MainBoard_tasks.c; the ADC, edge-wait and distance library implementations are
retained. It also includes complete TOF software, whose new-board supply,
pull-ups and SHUT remain unverified. Keep TOF_WIRING_CONFIRMED=0 until checked.

Initialization has been migrated to the same ownership rule as the classroom:
GPIO/ADC1/I2C2/TIM2 are generated from MainBoard.ioc, with one generated call each.
The ultrasonic port only starts the generated TIM2 and reads its counter; it no
longer configures GPIO or writes timer setup registers. This initialization
migration requires a fresh board test; generation/build is not physical acceptance.
The earlier IR/ultrasonic wiring was functionally checked on the new board, but
that does not validate the optional TOF or every newly generated image.

Open this folder in VS Code, configure STM32F405RGT6 / Cortex-M4 / GCC, build
Debug and flash build/Debug/MainBoard.elf with STLINK GDB Server, then Continue.
Use CubeMX 6.18.1 / FW_F4 V1.28.3 for regeneration, retaining user code and root
CMake sources. The wiring is IR UART2 V/T/R/G = VCC/D0/A0/GND and ultrasonic
V/PA0/PA1/G = VCC/Trig/Echo/GND. Both V rails were reported as 3.3 V; confirm your
board. USART2 remains disabled. Physical TOF wiring checks are still required.

The complete functions are in ir_sensor.c, ultrasonic.c, student_tasks.c,
tof_sensor.c and vl53l1_platform.c under Core/Src. Default IR thresholds require
measurement. This reference is separate from the student archive and carries
no unfinished CW2/CW3 task bodies. All vendor and adapted-library licenses are
retained in their original files.
