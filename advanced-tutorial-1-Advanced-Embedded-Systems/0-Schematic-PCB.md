# How to Read Schematics and PCBs?

[Back to home](../README.md) | [Next chapter](./1-Advanced_GPIO.md)

---

## Software ⇔ Hardware

<img src="./images/0-image-1.png" alt="STM32 Pinout and Layout" width="100%" />

<p align="center">
  <em><strong>LEFT:</strong> .ioc file in STM32CubeMX</em>
  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;
  <em><strong>RIGHT:</strong> PCB layout (top) &amp; schematic (bottom)</em>
</p>

### Core Concepts

* **Schematic**: Mindmap of the MCU pins (Hardware team).
* **PCB**: Physical layout routing tracks from the MCU (Hardware team).
* **.ioc File**: Configuration blueprint mapping pin functions (Software team).

### Workflow & Configuration

* **The Goal**: Software configures the `.ioc` first so hardware can draw the schematic/PCB.
* **Default Pins**: Every pin has multiple default internal functions set by STMicroelectronics.
* **How to Change**: Open STM32CubeMX, click a pin, and select its function.

---

## Common Interfaces

<img src="./images/0-image-2.png" alt="Common Interfaces Diagram" width="1050" />

| Interface | Configure the pins in `.ioc` to |
| :--- | :--- |
| **GPIO** | `GPIO_Input`, `GPIO_Output` |
| **ADC** | `ADCx_INx` |
| **PWM** | `TIMx_CHx` |
| **UART** | `USARTx_TX`, `USARTx_RX` |
| **I2C** | `I2Cx_SDA`, `I2Cx_SCL` |
| **SPI** | `SPIx_SCK`, `SPIx_MOSI`, `SPIx_MISO`, GPIO for CS |
| **CAN** | `CANx_TX`, `CANx_RX` |