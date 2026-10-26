[Contents](README.md) | [Next: ADC](01-adc.md)

# 0. Quick Map and Terms

**Follow the information:** physical quantity → sensor output → STM32 reading →
meaning in your program. A sensor supplies a signal; your code interprets it.

## Terms used in these notes

| Short name | Full name | Job here |
| --- | --- | --- |
| MCU | Microcontroller Unit | The STM32 chip running your program |
| ADC | Analog-to-Digital Converter | Convert an input voltage into an integer |
| DMA | Direct Memory Access | Move peripheral data into memory without CPU copying each result |
| GPIO | General-Purpose Input/Output | Read or drive a digital pin |
| HAL | Hardware Abstraction Layer | ST's functions for operating STM32 peripherals |
| IR | Infrared | Light used by the reflection sensor |
| UART | Universal Asynchronous Receiver/Transmitter | Transfer bytes without a separate clock signal |
| I2C | Inter-Integrated Circuit | Addressed communication using clock and data lines |
| TOF | Time of Flight | Estimate distance from signal travel time |
| CW | Classwork | The hands-on exercises |

CPU means **Central Processing Unit**; RAM is **Random Access Memory**.
TFT means **Thin-Film Transistor**, the display technology used by the screen.
The **`.ioc` file** stores CubeMX configuration; it is not a communication protocol.

## What information reaches the STM32?

| Sensor output | STM32 operation | Exercise |
| --- | --- | --- |
| Voltage level | ADC conversion → raw code | CW1 joystick; CW2 IR A0 |
| HIGH/LOW decision | GPIO read | CW2 IR D0 |
| HIGH pulse duration | GPIO edges + timer timestamps | CW3 ultrasonic Echo |
| Data bytes | I2C transaction + byte decoding | Optional TOF |

**Digital does not always mean bytes.** D0 carries one decision; Echo carries a
duration. ADC/GPIO acquire signals; UART/I2C define communication rules.
The GPIO ultrasonic exercise has no I2C address or packet.

For example:

```text
Move stick → voltage changes → ADC gives 3132 → normalize to about +0.50
```

Like the earlier UART command `LEFT\n`, received information still needs
interpretation. Neither ADC nor UART knows your intended application meaning.

## Who does which job?

| Layer | IR example |
| --- | --- |
| Peripheral / HAL | Start ADC, wait and obtain a code |
| Supplied driver | `IR_Read(sample)` obtains A0 and D0 |
| Your task | Compare A0 with a measured threshold |
| Display app | Show readings/classification, or an error |

Read the diagram → predict an example → find the function → complete one stage
→ **save/build/flash/run** → explain the observation.

Core order: **ADC → CW1 → IR/CW2 → GPIO timing/CW3**.
Optional: **I2C → TOF**. Communication success and measurement validity are
separate checks.

Use the [setup guide](../hardware/classwork-setup.md) for projects, connections
and build/flash steps; use the [IOC guide](../hardware/ioc-guide.md) for settings.
IR uses UART2 and ultrasonic uses PA0/PA1 in the prepared combined Debug app.
The [setup guide](../hardware/classwork-setup.md) shows the tested connection map
and explains the unfinished CW3 message and the completed measurement. Check supply and labels on your board.
The explanations and paper exercises need no connected hardware.

**Check:** why is one GPIO read enough for D0 but insufficient for distance?

<details>
<summary>Answer</summary>

D0's level is the decision. Echo needs two edges and the elapsed time between them.

</details>
