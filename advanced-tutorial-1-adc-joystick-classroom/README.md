# ADC and Joystick: Classroom Lab v2

This is the new, ungraded classroom exercise. The earlier Controller project
and the complete released reference remain available to both teaching groups.
You do not need to run that reference before starting this lab.

Download the [classroom starter ZIP](releases/ADC-Joystick-Classroom-v2.zip).

**Open only `projects/Controller-ADC-Lab` in VS Code.** Its output is
`build/Debug/Controller_ADC_Lab.elf`, for the Blue Pill Controller, not the Mainboard.
Read [setup](hardware/setup.md) before the first build.

## Work through three experiments

| Experiment | Your work | Evidence to keep |
| --- | --- | --- |
| A: one ADC input | Prepare the ADC, acquire a valid sample using polling, estimate millivolts | Predictions, raw/voltage readings, explanation of error handling |
| B: four inputs | Configure scan/DMA, start a persistent buffer once, identify its entries | Axis map, rank-change prediction, Normal/Circular comparison |
| C: useful positions | Measure calibration, implement signed positions/deadband, retest | Four-axis measurements, boundary predictions, before/after observations |

Use the [ADC lab](notes/01-adc-lab.md), [joystick lab](notes/02-joystick-lab.md)
and [worksheet](notes/worksheet.md). Keep predictions written before each test.
There are no extra marks or a separate submission deadline for this exercise.

## What is supplied

The display, clock, SWD, startup, HAL, build files and a single-channel ADC
configuration are supplied. The display owns a persistent, aligned DMA buffer
and reports unfinished tasks or HAL errors. It never fills in an unfinished
acquisition or calculation for you.

Write in `Core/Src/lab_tasks.c`. Change `Core/Inc/lab_config.h` for the experiment
stage, reference assumption, buffer mapping and measured calibration. For B,
change the IOC and regenerate the same project. The acquisition/voltage/
normalization/extent functions are intentionally unfinished.

Reference material and AI suggestions may be consulted. Be ready to explain
the code you use, compare it with the HAL documentation and show what changes
when the mentor changes one input or setting. A working screen alone is not the
learning record.

The complete earlier reference is kept in the repository's
[reference/Controller](https://github.com/UST-Robotics-Team/Software-Tutorial-2026-Notes/tree/main/reference/Controller)
directory. It is a separate project, not a dependency of this classroom starter.

## Resources

- [HAL API index](hardware/api-index.md): purpose, status and source locations.
- STM32F103x8/xB datasheet: ADC input limits and characteristics.
- ST RM0008: ADC regular conversions and DMA transfer operation.
- The bundled HAL source and header files retain their original licenses.

The project retains a conservative STM32F103C8 profile: 64 KB Flash and 20 KB RAM.
Calibration defaults are starting values, not measurements of your Controller.
