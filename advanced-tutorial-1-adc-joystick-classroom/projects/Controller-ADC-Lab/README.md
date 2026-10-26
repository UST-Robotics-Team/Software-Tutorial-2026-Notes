# Controller ADC Lab

New ungraded classroom project. This is separate from the earlier Controller
exercise and its complete released reference.

Open this folder in VS Code and use Debug / ST-Link GDB Server. The expected ELF
is `build/Debug/Controller_ADC_Lab.elf` for STM32F103C8T6 / Cortex-M3.

Read [setup](../../hardware/setup.md), [experiment A](../../notes/01-adc-lab.md)
and [experiments B/C](../../notes/02-joystick-lab.md).

- Write acquisition and processing functions in `Core/Src/lab_tasks.c`.
- Choose A/B/C and measured parameters in `Core/Inc/lab_config.h`.
- For B/C, edit `Controller_ADC_Lab.ioc`, Generate Code, then rebuild.
- The display and persistent buffer are supplied in `Core/Src/lab_app.c`.
- No complete task implementation or automatic answer fallback is included.

The initial IOC is a single regular conversion with Continuous disabled. The
prepared Normal DMA route is unused in A. It is intentionally not the final
four-channel continuous/Circular configuration that B asks you to establish.
