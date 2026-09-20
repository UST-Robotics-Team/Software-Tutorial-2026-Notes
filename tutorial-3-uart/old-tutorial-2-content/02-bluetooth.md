# Bluetooth

[Back to Main](./README.md) | [Previous Page](./01-uart.md)

> Author: Ken Law (cclawad@connect.ust.hk)

## Introduction

By now, you should have a good understanding of how to debug your program using UART. However, let’s be honest, debugging a moving robot with a long cable connected to your computer isn’t very practical (or elegant :p). It’s a bit like walking your dog with your computer. Here comes the need of wireless UART.

HC-05 is a bluetooth module that acts like a translator. It automatically translate between the UART data package and the bluetooth data package. Therefore you don't need to modify your written code and consider about the technical detail of bluetooth communication. You just need to hook up the module and enjoy the convenience of wireless debuging.

## Setting Up Your Bluetooth Module

The HC-05 Bluetooth module, like other Bluetooth devices, has a default device name and password. Since many identical HC-05 modules are used in the lab, it’s important to customize the name and password to easily identify your module.

To configure your HC-05 module, follow these steps:

1. Connect the HC-05 and the USB-TTL module together
   > USB-TTL <-> HC05 \
   >  RXD <-> TXD \
   >  TXD <-> RXD \
   >  GND <-> GND \
   >  3V3 <-> VCC \
   >  VCC <-> EN
2. Hold down the button on the HC-05 while plugging the USB-TTL adapter into your computer.
3. Release the button. The HC-05 should enter "AT" mode, indicated by a slowly flashing LED.
4. Set your serial monitor baud rate to 38400 and connect. If this doesn’t work, try 9600.
5. Type `AT` and press Enter. If you receive an `OK` response, you can proceed with the AT commands below. If not, repeat the steps above.

**Useful AT Commands:**

- `AT`: Test connection
- `AT+RESET`: Return to normal communication mode (does not reset configuration)
- `AT+NAME?`: Show current device name
- `AT+NAME=<Param>`: Set device name
- `AT+PSWD?`: Show current password
- `AT+PSWD=<Param>`: Set password
- `AT+UART=<baud>,<stop bit>,<parity>`: Set UART settings
  > stop bit: 0 -> 1 bit, 1 -> 2 bits \
  > Parity bit: 0 -> None, 1 -> Odd parity, 2 -> Even parity \
  > (Recommended: `AT+UART=115200,0,0`)
- `AT+UART?`: Show UART settings
- `AT+ROLE=<Param>`: Set role (0 = Slave, 1 = Master)
- `AT+ROLE?`: Show current role
- `AT+CMODE=<Param>`: Set connection mode (0 = Specified device, 1 = Any device)
- `AT+CMODE?`: Show connection mode
- `AT+ORGL`: Reset all settings to default

> AT commands are **case-sensitive**.

> **HC-05 AT Command Manual:** [PDF](https://s3-sa-east-1.amazonaws.com/robocore-lojavirtual/709/HC-05_ATCommandSet.pdf) \
> **HC-08 AT Command Manual (Reference):** [PDF](https://www.rhydolabz.com/documents/30/hc05_bluetooth.pdf)

### AT Command Configuration Steps

1. Check and set the module name.
2. Check and set the password.
3. Set the module role to be `Slave` (your computer acts as Master).
4. Set connection mode to be `Any device` (allows connection to any nearby device).
5. Set the UART setting using `AT+UART=115200,0,0`

After configuration, connect the HC-05 to the UART port of your STM32 board. Once powered, your computer should detect the device.

> If you’re using Windows 11 and cannot find the HC-05, see this [troubleshooting guide](./02a-bluetooth-problem-solving-win11.md).

After pairing, rescan the serial ports in CoolTerm. It may take some time to connect as your computer waits for the HC-05 to respond.

## MIT App Inventor (Bonus)

For future robotics projects (e.g. RDC), you may need to build your own robot controller. MIT App Inventor (https://appinventor.mit.edu/) is a free online tool for creating Android apps without coding experience. You can easily design controller interfaces (joysticks, buttons) and use the built-in Bluetooth Client library to communicate with your robot.

For more details, see the [Bluetooth Client documentation](http://ai2.appinventor.mit.edu/reference/components/connectivity.html#BluetoothClient).

> Youtube tutorial and genAI are your good friends :p

[Previous](./01-uart.md) | [Next Page](./03-classwork.md)
