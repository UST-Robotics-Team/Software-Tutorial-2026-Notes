[Tutorial](../notes/README.md) | [Terms](../notes/00-getting-started.md)

# Getting started

## Two boards, two projects

| Classwork | Open in VS Code | Board |
| --- | --- | --- |
| CW1 ADC/joystick | `projects/Controller` | Blue Pill / STM32F103xB |
| CW2 IR + CW3 ultrasonic + optional TOF | `projects/MainBoard` | New RDC Mainboard / STM32F405RG profile |

Keep one MainBoard program and screen throughout the sensor exercises. Preserve
your completed IR code when adding ultrasonic, then optional TOF. Controller and
MainBoard are different targets; never flash one board's ELF onto the other.

Display, clocks, buttons, HAL and CMake are supplied. Controller ADC1 and MainBoard
ADC1/TIM2/I2C2 are initially disabled for you to configure and generate. MainBoard
SPI1 DMA is already configured for the TFT; do not remove it when keeping ADC or
timer DMA disabled. Install CubeMX 6.18.1 and the required FW_F1 V1.8.7 / FW_F4
V1.28.3 packages before class. Bundled sources alone do not replace generation's
firmware-package dependency.

## Build and flash: the usual Debug workflow

1. Open the individual project folder. Accept STM32 project setup if prompted,
   keeping the correct MCU and complete Arm toolchain.
2. Run **CMake: Build**, select **Debug**, and resolve errors before flashing.
3. Use **Run and Debug** / STLINK GDB Server. If absent, create its launch
   configuration using the installed STM32 extension, as in
   [Tutorial 1](https://github.com/UST-Robotics-Team/Software-Tutorial-2026-Notes/blob/main/tutorial-1-basic-io/00-introduction.md#5-generate-a-launchjson-to-flash-code).
4. Select `build/Debug/Controller.elf` or `build/Debug/MainBoard.elf` for the board
   actually connected, then start debugging to flash it.
5. Continue past the entry breakpoint and check the expected screen.

If the STM32 extension asks to set up the project, use its project setup action
in the STM32 sidebar, select the current project and **Debug**, and keep the
correct MCU and complete Arm toolchain. Command Palette wording can vary;
finding one exact setup-command name is not a prerequisite. A missing STLINK
GDB Server launch configuration is handled by step 3 above.

Use the **same working folder** in CubeMX and VS Code. The generated `adc.c`
must belong to the Controller folder you are building, rather than a second
extracted copy or the lecturer's temporary screenshot project. Check the opened
IOC's project location and the ELF path if generation or edits appear to have
no effect.

After application edits: **save → build Debug → Run and Debug → Continue**.
After IOC changes: **save IOC → Generate Code → inspect → build/flash/Continue**.
Initialization comes from IOC. Do not add a second MX init call or replace a
generated configuration body by hand. Put application calls within USER CODE
regions and the actual task bodies in the supplied independent files.

## Wire the MainBoard sensors

Power off before wiring and match actual labels. The earlier individual and
combined IR/ultrasonic tests used this map on the new board. V supplies were
reported as 3.3 V; confirm on your classroom board.

| Sensor | Header |
| --- | --- |
| IR VCC / D0 / A0 / GND | UART2 V / T(PA2) / R(PA3) / G |
| Ultrasonic VCC / Trig / Echo / GND | V / PA0 / PA1 / G |

USART2 remains disabled: the UART2-labelled connector carries GPIO/analog signals.
PA0/PA1 start as passive inputs until CW3 configuration; PA3 starts analog GPIO
until ADC1 is enabled. Optional TOF uses PB10/PB11 after I2C2 configuration, but
its supply, pull-ups and SHUT still require a lecturer's physical check. Keep
TOF_WIRING_CONFIRMED=0 meanwhile. See the [connection map](pin-mapping.md).

## First flash and progress messages

The untouched MainBoard starter shows:

```text
IR + ULTRASONIC
IR NOT READY
CHECK CW2 GPIO
UART2 A0:R D0:T
ULTRASONIC CW3
US NOT READY
CHECK CW3 TIMER
NEAR: ---
PA0:T PA1:E
RUN 3 s
```

| Your progress | Expected observation |
| --- | --- |
| CW2A digital function works | D0 changes; A0 is dashes with ADC TODO/ERROR |
| CW2B ADC function works | A0/D0 respond; SURFACE remains ? until classification |
| CW2C classifier works | BLACK/WHITE follow your measured threshold |
| CW3 timer start works | DO CW3 TODO until you implement the transaction |
| CW3 transaction works | Your distance/pulse width, or an error and no stale distance |
| Optional TOF enabled after checks | TOF status/result on rows 8/9; no automatic valid sample |

Controller initially shows CW1 NORMALIZED / ADC NOT READY / CHECK CW1A SETUP.
Follow the [detailed CW1 walkthrough](../notes/02-joystick.md#2-cw1a--configure-and-acquire)
for generation, startup calibration, one-axis polling and then four-axis polling.
Successful startup with acquisition still a TODO shows READ NOT READY. One-axis
mode deliberately shows dashes for unmeasured axes/PUSH; four-axis RAW VALID
does not imply normalization or measured calibration is complete.

## Where you write code

| File | Task |
| --- | --- |
| Controller IOC / `joystick.c` / `student_tasks.c` | CW1 configuration, acquisition, normalization |
| MainBoard IOC | CW2 ADC/GPIO, CW3 GPIO/TIM2, optional I2C2 |
| MainBoard `ir_sensor.c` | Digital input and ADC polling |
| MainBoard `student_tasks.c` | IR classification and complete ultrasonic transaction |
| MainBoard `ultrasonic_gpio_port.c` | Timer start/counter access and GPIO operations |
| MainBoard `ultrasonic.c` | Delay and shared-deadline edge capture |
| MainBoard `vl53l1_platform.c` / `tof_sensor.c` | I2C transfers, decoding, probe and valid result sequence |
| MainBoard `tutorial_config.h` | Measured threshold/polarity and checked TOF wiring flag |

Add generated peripheral headers to your independent C files after enabling
and generating that peripheral. Never declare another hadc1/htim2/hi2c2 or add
another main. Generation should preserve task files and root CMake user sources.

The app draws a complete frame and commits once. Do not add another tft_update
inside tasks. Keep labels within 16 characters. The TFT mini formatter supports
`%u` with `(unsigned)` values, but not `%lu` or floating-point formatting.

Both IR and ultrasonic are serviced even when the other reports an error, though
polling waits can delay the next screen update. Keep every sensor wait bounded.
The optional TOF app also checks validity; HAL_OK alone is not a valid range.

[IOC walkthrough](ioc-guide.md) | [CW2](../notes/03-ir.md) |
[CW3](../notes/04-ultrasonic.md) | [TOF](../notes/06-optional-tof.md)
