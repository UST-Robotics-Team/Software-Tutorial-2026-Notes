# IOC Guide: Settings and Their Purpose

[Tutorial](../README.md) | [Setup](classwork-setup.md) |
[Terms](../notes/00-getting-started.md)

The **`.ioc` file** stores STM32CubeMX pin/peripheral configuration. Generation
creates initialization code; application code still starts operations.
For example, `MX_ADC1_Init()` configures ADC, while `Joystick_Start()` calibrates
and starts acquisition.

This guide matches the supplied IOC and source files. Open the IOC inside the
extracted project. Keep the skeleton's display, UART, debug and clock setup;
menu labels may vary by CubeMX version. Pin settings do not confirm physical
sensor connections.

## 1. Controller: ADC and DMA for CW1

ADC = **Analog-to-Digital Converter**; DMA = **Direct Memory Access**.

Open `projects/Controller/Controller.ioc` (STM32F103C8T6).
In **Pinout & Configuration → Analog → ADC1**, enable IN0–IN3 on PA0–PA3.
Under **Parameter Settings**:

| Setting | Value | Purpose |
| --- | --- | --- |
| Scan | Enabled | Sequence of inputs |
| Continuous | Enabled | Repeat after starting |
| Discontinuous | Disabled | Do not split across triggers |
| Trigger | Software start | Started by `Joystick_Start()` |
| Alignment | Right | Ordinary integer code |
| Regular conversions | 4 | Four axes |
| Ranks 1/2/3/4 | Channels 0/1/2/3 | J1X/J1Y/J2X/J2Y order |
| Sampling, all ranks | 71.5 cycles | Prepared sampling duration |

The F103 ADC is 12-bit; its controls differ from the F405.
In **Clock Configuration**, keep HCLK/APB2 = 72 MHz and ADC prescaler `/6`
→ **12 MHz ADC clock**. HCLK is the core/bus clock; APB means **Advanced
Peripheral Bus**. ADC clock is not sample rate: each scan needs four sampling
and conversion operations.

In **ADC1 → DMA Settings**, add/check ADC1:

| Setting | Value | Purpose |
| --- | --- | --- |
| DMA route | DMA1 Channel1 | ADC1's assigned route |
| Direction | Peripheral to memory | ADC result → RAM |
| Peripheral increment | Disabled | Same ADC data register |
| Memory increment | Enabled | Successive array elements |
| Peripheral/memory width | Half-word / half-word | 16-bit storage for 12-bit code |
| Mode | Circular | Refill the buffer repeatedly |
| Priority | High | Match starter |

The app starts a four-element buffer once. It reads the latest data rather than
using callbacks; the supplied start routine disables transfer interrupts while
DMA continues. Without memory increment, results overwrite one slot; Normal
mode stops at the end of its configured transfer.

## 2. Mainboard: single ADC conversion for CW2

Open `projects/MainBoard/MainBoard.ioc` (STM32F405RGT6).
The tested connector map is in [connections](pin-mapping.md).
Confirm supply and labels on your classroom board; USART2 is disabled.

Select **Analog → ADC1**, enable IN3 on PA3, then use:

ADC1 must be enabled and IN3 must stay selected after saving and reopening the
IOC. Continuous conversion stays disabled because `IR_Read()` starts each
conversion in software; disabled continuous mode does not mean disabled ADC1.

| Setting | Value | Purpose |
| --- | --- | --- |
| ADC prescaler | PCLK2 / 4 | Peripheral clock 84 MHz / 4 = 21 MHz |
| Resolution | 12 bits | Codes 0–4095 |
| Scan / Continuous / Discontinuous | Disabled | One requested conversion |
| Trigger edge / source | None / software start | Driver requests conversion |
| Alignment | Right | Integer raw code |
| Number / Rank 1 | 1 / Channel 3 | A0 |
| Sampling time | 144 cycles | Prepared input sampling |
| DMA continuous requests | Disabled | Use polling |
| End of conversion | Single conversion | Wait for this result |

Set PA2 to **GPIO_Input, No pull** for D0 on UART2 T. A0 is on UART2 R/PA3.
GPIO = **General-Purpose Input/Output**: D0 is digital; A0 is Analog.
`IR_Read()` starts, polls, reads and stops ADC. Selecting a pin does not
automatically fill your task's variable.

## 3. Mainboard: runtime GPIO/TIM2 for CW3

The IOC lists PA0 as Trig output, PA1 as Echo input, and TIM2 with prescaler 83
and period `0xFFFFFFFF`. The supplied `Ultrasonic_GPIO_Init()` owns actual
runtime GPIO/TIM2 setup; do not add another timer initialization.

| Setting | Value |
| --- | --- |
| Trig / Echo | PA0 push-pull idle LOW / PA1 input, no pull |
| APB1 timer clock | 84 MHz |
| TIM2 prescaler | 83: 84 MHz / (83+1) = 1 MHz |
| Counter period | `0xFFFFFFFF`, free-running 32-bit |
| Time reading | `Ultrasonic_Micros()` reads CNT |

CW3 fills the trigger sequence and pulse/distance calculation. The helpers supply
edge waits with a shared deadline. PB10/PB11 remain I2C2; they are not repurposed
for ultrasonic. The task's early return shows DO CW3 TODO without measuring;
it does not alter peripheral or build settings.

## 4. Mainboard: optional I2C2

I2C = **Inter-Integrated Circuit**. In **Connectivity → I2C2**, select I2C mode;
PB10 = SCL (**Serial Clock**), PB11 = SDA (**Serial Data**).

| Setting | Value | Purpose |
| --- | --- | --- |
| Speed | Standard mode, 100 kHz | Starter bus rate |
| Address mode | 7-bit | Device addressing |
| Own Address 1 | 0 | STM32 target address, not sensor address |
| Dual Address / General Call | Disabled | Unused here |
| GPIO | Alternate function open-drain, AF4 | Peripheral drives/releases lines |
| Internal pull | No pull | Check compatible external pull-ups |

Software passes sensor address `TOF_ADDRESS_HAL=0x52`, derived from 7-bit
`0x29`. Do not put the sensor address in **Own Address**.
Bus initialization does not initialize the sensor's ranging engine.

Check supply, SHUT handling and pull-ups against the actual breakout.
An open-drain setting does not create external pull-up resistors.

## 5. Save/generate without losing the starter

Inspection is enough for these classworks. For regeneration practice, use a
**copy of the complete project**: the shared sensor additions have not had a
full CubeMX regeneration round trip checked.

1. **Project Manager → Project:** retain the CMake target/toolchain.
2. **Code Generator:** retain user code and separate peripheral `.c/.h` files.
3. Save IOC → **Generate Code** → review the diff.
4. Preserve `TutorialApp_Init()/Update()`, custom sources/includes and Controller
   normalization source in the build.
5. Preserve the IR conversion guard, USART2 disable, PA2/PA3 passive inputs,
   fixed PA0/PA1 timing port and independent I2C2 setup.
6. Reconfigure/build and check the expected starter screen before sensors.

Read `adc.c`, `dma.c`, `i2c.c`, `main.c` and `ultrasonic_gpio_port.c`
to connect settings with runtime behavior. A valid IOC/build does not confirm wiring.

UART = **Universal Asynchronous Receiver/Transmitter**; TFT =
**Thin-Film Transistor** display; SWD = **Serial Wire Debug**.
Their existing board settings remain in the skeleton.
