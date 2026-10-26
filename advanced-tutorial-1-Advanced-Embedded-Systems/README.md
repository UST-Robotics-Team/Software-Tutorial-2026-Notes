# Advanced Tutorial 1: ADC, GPIO Timing & I2C

<details>
<summary>Lecturers</summary>

Tony Li and Tom

</details>

In this tutorial, you will read joystick positions, detect black and white
surfaces, and measure distance using **analog voltages and timed digital pulses**.
The I2C lecture introduces **addressed data messages**, applied in the optional
after-class TOF experiment.

## Contents

0. [Quick map and terms](notes/00-getting-started.md) — acronym meanings and how sensor data reaches your code.
1. [ADC](notes/01-adc.md) — sampling, voltage codes, polling/DMA and calibration.
2. [Joysticks](notes/02-joystick.md) — **Classwork 1:** read four axes, implement normalization, calibrate and compare deadbands.
3. [IR sensor](notes/03-ir.md) — **Classwork 2:** sample A0, read D0 and choose a black/white threshold.
4. [Ultrasonic sensor](notes/04-ultrasonic.md) — **Classwork 3:** guided trigger timing, Echo width and distance conversion.

**I2C lecture and optional application**

5. [I2C](notes/05-i2c.md) — shared channel, reading through the driver and using updated data fields.
6. [TOF400C](notes/06-optional-tof.md) — compare optical and ultrasonic ranging, then read the TOF sensor.

Help: [Troubleshooting](notes/07-troubleshooting.md).

## How to follow the lesson

Each topic defines its terms, traces an example, then connects it to the
classwork. Predict before running; explain what you observe.

| Core stage | Question you should be able to answer |
| --- | --- |
| ADC and CW1 | Why can raw 2048 mean a centred stick, while signed position should be zero? |
| IR and CW2 | How can one sensor have an analog reading and a separate digital decision? |
| GPIO timing and CW3 | Why does Echo duration tell us more than its current HIGH/LOW level? |

The I2C lecture and optional TOF section add a fourth form: a sensor reports values as bytes.

## Before you start

You should be familiar with GPIO, the TFT display, C arrays and pointers, and the
STM32 build/flash workflow from Tutorials 1–3. Use VS Code with the STM32
extension pack and STM32CubeMX as before.

Download and extract the [student starter](releases/Advanced-Tutorial-1-Student-v1.zip).
It contains **two separate STM32 projects**:

| Project | Board | Used for |
| --- | --- | --- |
| [Controller](projects/Controller/README.md) | Blue Pill, STM32F103xB | CW1: joysticks |
| [MainBoard](projects/MainBoard/README.md) | STM32F405RGT6 | CW2: IR; CW3: ultrasonic; optional TOF |

Open one project folder at a time. Use the prepared Debug build and complete
`Core/Src/student_tasks.c`. Use the [setup guide](hardware/classwork-setup.md)
for build/flash commands and the [IOC walkthrough](hardware/ioc-guide.md) for
CubeMX settings and what they do.

> [!IMPORTANT]
> Have a senior check the Mainboard sensor and power connections before the
> hands-on work. The setup guide explains the combined screen and unfinished CW3 message.

## Classworks

There are three classworks. Show your working board and explain your results to
a senior during the tutorial.

| Classwork | What to demonstrate |
| --- | --- |
| CW1 | Four ADC axes, your own normalization code, calibration record and deadband comparison |
| CW2 | A0 and D0 readings, measured black/white samples and a working software threshold |
| CW3 | Distance at three target positions, pulse timing, and failure/recovery without a stale reading |

I2C core concepts are introduced in class. The TOF400C application and deeper
I2C examples are optional self-study; they are not submitted or marked.

## Equipment

RDC Controller, RDC Mainboard, ST-Link, computer, jumper wires, TCRT5000 module,
HC-SR04-compatible RCWL-9610 ultrasonic module, black/white paper, a ruler and a
flat target. The optional experiment also needs a TOF400C module with VL53L1X.
Use the power connections checked by the lecturers.

---

[Begin: Quick map and terms](notes/00-getting-started.md)

CW2 and CW3 share one prepared Mainboard Debug program and one screen. The
starter reads IR A0/D0 for sampling; ultrasonic waits for the completed CW3 task. CW2 uses A0 for a measured
software threshold; D0 is a separate comparison. CW3 supplies a marked template
for trigger/width/distance logic, with bounded waits and error handling provided.

IR uses UART2 V/T/R/G; ultrasonic uses V/PA0/PA1/G. Confirm supply and signal labels on your board before connecting the sensors. USART2 remains disabled; TOF wiring is still TBD.
