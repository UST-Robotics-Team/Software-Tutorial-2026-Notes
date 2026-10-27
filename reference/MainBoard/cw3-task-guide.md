# Complete Ultrasonic Reference

[Project and validation limits](README.md)

This is the completed earlier measurement implementation, not a task sheet.
The current classroom exercise is in the tutorial directory's MainBoard project.

GPIO/ADC/I2C/TIM2 configuration is generated from MainBoard.ioc. The historical
function name Ultrasonic_GPIO_Init is retained here, but its body now only starts
the already initialized TIM2 with HAL. It does not configure GPIO or timer registers.

Ultrasonic_Begin clears current outputs/diagnostics and checks idle Echo.
Ultrasonic_WaitEdges contains the complete shared-deadline rise/fall capture.
CW3_MeasureUltrasonic contains the complete trigger and round-trip calculation.
Ultrasonic_Complete validates plausibility and publishes the result. Read their
Core/Src implementations for the earlier complete logic and status handling.

After migration to generated initialization, software generation/build was
checked; a fresh board test is still needed. TOF software is included, with its
new-board supply, pull-ups and SHUT checks still pending.
