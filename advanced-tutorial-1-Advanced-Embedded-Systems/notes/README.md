# Advanced Tutorial 1: Lesson Index

[Tutorial overview and starter download](../README.md)

| Lesson | What you will learn |
| --- | --- |
| [0. Quick map and terms](00-getting-started.md) | Acronym meanings; voltage, logic level, pulse duration and messages |
| [1. ADC](01-adc.md) | Sampling, voltage codes, polling/DMA and different kinds of calibration |
| [2. CW1: Joysticks](02-joystick.md) | Implement normalization, calibrate four axes and compare deadbands |
| [3. CW2: IR sensor](03-ir.md) | Compare analog and digital outputs; measure and choose a threshold |
| [4. CW3: Ultrasonic sensor](04-ultrasonic.md) | Measure an Echo pulse with a microsecond timer |
| [5. I2C](05-i2c.md) | Shared channel; call the driver, get updated fields and check validity |
| [6. Optional: TOF400C](06-optional-tof.md) | Compare sound/light ranging, use the driver and check validity |
| [7. Troubleshooting](07-troubleshooting.md) | Diagnose build, display and sensor problems |

Work through the lessons in order. Ask a senior to check each completed
classwork before moving on.
Lessons 0–5 cover the class concepts and three CWs. Lesson 6 and the deeper
I2C examples are optional after-class study.

Use [project/build setup](../hardware/classwork-setup.md) during hands-on work,
and the [IOC walkthrough](../hardware/ioc-guide.md) to inspect or learn the
configuration. Each lesson follows: understand → predict → trace code → try → explain.

For the initial IR readout, unfinished CW3 screen and normal Debug workflow, open
[Classwork setup](../hardware/classwork-setup.md). One Mainboard program covers
CW2 and CW3. GPIO/TIM2 configuration, bounded waits and errors are supplied;
students retain A0 threshold selection and the ultrasonic measurement's key steps.
