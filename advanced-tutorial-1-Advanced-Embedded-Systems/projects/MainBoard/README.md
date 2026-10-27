# MainBoard — IR, Ultrasonic and Optional TOF

One project, one Debug ELF and one screen covers CW2, CW3 and optional TOF.
Build Debug, Run and Debug / STLINK GDB Server, then Continue after the entry
breakpoint. Select `build/Debug/MainBoard.elf` on the F405 Mainboard.

The starter prepares display SPI/DMA, clocks, buttons, LEDs, USART1 and SWD.
**ADC1, TIM2 and I2C2 start disabled.** Sensor pins remain passive until their
IOC configuration is completed; USART2 is always disabled. No sensor reference
implementation runs automatically. The initial screen shows IR/US NOT READY
and increasing RUN time.

| Part | Configure in IOC | Write in existing application files |
| --- | --- | --- |
| CW2A | PA2 GPIO input, no pull | `ir_sensor.c`: `IR_ReadDigital()` |
| CW2B | PA3 ADC1 IN3, one software-triggered conversion | `ir_sensor.c`: `IR_Read()` |
| CW2C | Retain acquisition | `student_tasks.c`: classify measured A0 |
| CW3A | PA0 output LOW, PA1 input, TIM2 1 MHz | `ultrasonic_gpio_port.c`: start/counter/GPIO; `ultrasonic.c`: microsecond delay |
| CW3B/C | Keep generated setup | `ultrasonic.c`: bounded edge waits; `student_tasks.c`: transaction and distance |
| TOF A/B/C | I2C2 PB10/PB11, 100 kHz | `tof_sensor.c`: probe/read; `vl53l1_platform.c`: bus transfers and word decoding |

Generate Code produces every peripheral initialization and its call once.
Do not write `HAL_GPIO_Init()`, timer register setup or extra MX init calls in
application files. Runtime HAL start/read/write operations belong to the tasks.
Add generated `adc.h`, `tim.h` or `i2c.h` includes only after enabling/generating
that peripheral. Keep all task files, root CMake user sources and USER CODE calls.

IR uses UART2 V/T/R/G = VCC/D0/A0/GND (PA2 D0, PA3 A0). Ultrasonic uses
V/PA0/PA1/G = VCC/Trig/Echo/GND. Both V supplies were reported as 3.3 V; confirm
your board. TOF supply/pull-ups/SHUT remain pending; its wiring flag stays zero.

[CW2](../../notes/03-ir.md) | [CW3](../../notes/04-ultrasonic.md) |
[CW3 task map](cw3-task-guide.md) | [I2C](../../notes/05-i2c.md) |
[TOF](../../notes/06-optional-tof.md) | [IOC guide](../../hardware/ioc-guide.md)

The complete earlier IR/ultrasonic/TOF software is preserved separately in the
repository's `reference/MainBoard`, with its physical-validation limits stated.
