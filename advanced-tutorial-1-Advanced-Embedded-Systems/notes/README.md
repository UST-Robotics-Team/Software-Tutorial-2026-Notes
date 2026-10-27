# Advanced Tutorial 1: Lesson Index

[Tutorial overview and starter download](../README.md)

| Lesson | What you will learn |
| --- | --- |
| [0. Quick map and terms](00-getting-started.md) | Acronym meanings; voltage, logic level, pulse duration and messages |
| [1. ADC](01-adc.md) | Voltage codes, ADC configuration, polling and calibration |
| [2. CW1: Joysticks](02-joystick.md) | Configure/read ADC, implement normalization, calibrate and compare deadbands |
| [3. CW2: IR sensor](03-ir.md) | Configure/read GPIO and ADC; measure and choose a threshold |
| [4. CW3: Ultrasonic sensor](04-ultrasonic.md) | Configure GPIO/TIM2; implement bounded pulse timing and distance |
| [5. I2C](05-i2c.md) | Addressed transfers, registers, byte order and validity |
| [6. Optional: TOF400C](06-optional-tof.md) | Configure I2C, implement transfers and obtain a valid range |
| [7. Troubleshooting](07-troubleshooting.md) | Diagnose build, display and sensor problems |

Work through the lessons in order. Ask a senior to check each completed
classwork before moving on.
Lessons 0–5 cover the class concepts and three CWs. Lesson 6 and the deeper
I2C examples are optional after-class study.

Use [project/build setup](../hardware/classwork-setup.md) during hands-on work,
and the [IOC walkthrough](../hardware/ioc-guide.md) to inspect or learn the
configuration. Each lesson follows: understand → predict → trace code → try → explain.

For progress messages and the Debug workflow, open
[Classwork setup](../hardware/classwork-setup.md). One MainBoard program covers
CW2/CW3 and optional TOF. Initialization is generated from IOC; students write
the key GPIO/ADC/timing/I2C acquisition code in independent application files.
