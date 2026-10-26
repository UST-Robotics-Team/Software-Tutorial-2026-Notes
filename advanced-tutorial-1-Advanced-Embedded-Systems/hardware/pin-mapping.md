# Mainboard Sensor Connections

Match the actual header labels, not wire colours or the module's pad order.
Power off before wiring. The two sensor paths below and the earlier combined
preview were functionally checked on the new RDC Mainboard. The operator reports
both V pins as 3.3 V; confirm the supply on your classroom board.

## IR — all four wires on UART2

| Module pin | UART2 header | MCU function |
| --- | --- | --- |
| VCC | V | Reported 3.3 V |
| D0 | T | PA2 GPIO input, no internal pull |
| A0 | R | PA3 ADC1 Channel 3 |
| GND | G | Common ground |

USART2 serial communication stays disabled: PA2 must not drive UART TX while
D0 is connected. A0 supplies the varying ADC code; D0 is a separate comparator
decision. CW2 uses the ADC code for its software threshold.

## Ultrasonic — V/PA0/PA1/G

| Module pin | Mainboard header | MCU function |
| --- | --- | --- |
| VCC | V | Reported 3.3 V |
| Trig | PA0 | Push-pull output, idle LOW |
| Echo | PA1 | Digital input, no internal pull |
| GND | G | Common ground |

The supplied module uses its tested GPIO mode. Roles are fixed; no probe or
automatic swap is performed. IR remains attached to UART2 for both CWs.
The supplied port uses TIM2 at 1 MHz, with a prescaler of 83 for the 84 MHz
timer clock. The student task changes the measurement logic, not this setup.

## Optional TOF — I2C2 remains independent

| Header | Bus signal / status |
| --- | --- |
| C | PB10 SCL |
| D | PB11 SDA |
| G | Ground |
| V | Voltage TBD for this connector |

The actual TOF breakout supply, pull-up voltage/presence and SHUT handling are
TBD on this board. Check them with a lecturer before setting its wiring flag.
Bus configuration alone does not verify a sensor transaction.

## Prepared defaults

IR_WIRING_CONFIRMED=1; ULTRASONIC_WIRING_CONFIRMED=1; TOF_WIRING_CONFIRMED=0.
These flags acknowledge the prepared wiring; they do not measure voltage or
detect a misplaced wire. No flag or build selector is changed between CW2/CW3.

The hardware baseline is Quang's STM32F405RGT6 profile, 168 MHz HCLK.
LED D5/D6/D7/D8: PC14/PC15/PC0/PC1. Buttons: PB1/PA4.
TFT SCK/MOSI/RESET/DC/CS/BL: PA5/PA7/PA6/PC4/PC5/PB0.
USART1 PA9/PA10 and SWD PA13/PA14 remain configured.

[Setup](classwork-setup.md) | [IOC guide](ioc-guide.md)
