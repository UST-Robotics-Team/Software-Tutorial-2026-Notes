# Bluetooth

[Back to Main](./README.md) | [Previous Page](./04-non-blocking-uart.md)

> Author: Ken Law (cclawad@connect.ust.hk) \
> Modified by Ken Yu (ksyuad@connect.ust.hk)

## Introduction

By now, you should have a good understanding of how to debug your program using UART. However, let’s be honest, debugging a moving robot with a long cable connected to your computer isn’t very practical (or elegant :p). It’s a bit like walking your dog with your computer. Here comes the need of wireless UART.

HC-05 is a bluetooth module that acts like a translator. It automatically translate between the UART data package and the bluetooth data package. Therefore you don't need to modify your written code and consider about the technical detail of bluetooth communication. You just need to hook up the module and enjoy the convenience of wireless debuging.

This year, we use two HC-05 modules: one configured as **Master** and one configured as **Slave**. The Master starts the connection, while the Slave waits for the Master to connect. After they are connected, UART data can travel in both directions, so "Master" and "Slave" do not mean transmit-only and receive-only.

## Setting Up Your Bluetooth Modules

The HC-05 Bluetooth modules, like other Bluetooth devices, have a default device name and password. Since many identical HC-05 modules are used in the lab, it’s important to customize the names and passwords to easily identify your modules. Label one module **Master** and the other **Slave** before configuration.

Configure each HC-05 module separately. For each module, follow these steps:

1. Connect the HC-05 and the USB-TTL module together
   > USB-TTL <-> HC05 \
   >  RXD <-> TXD \
   >  TXD <-> RXD \
   >  GND <-> GND \
   >  5V  <-> VCC \
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
- `AT+ADDR?`: Show the module's Bluetooth address
- `AT+BIND=<address>`: Bind the Master to a specified Slave address
- `AT+BIND?`: Show the address currently bound to the Master
- `AT+INIT`: Initialize the Bluetooth connection profile
- `AT+PAIR=<address>,<timeout>`: Pair with a specified module
- `AT+LINK=<address>`: Connect to a specified module
- `AT+ORGL`: Reset all settings to default

> AT commands are **case-sensitive**.

> **HC-05 AT Command Manual:** [PDF](https://s3-sa-east-1.amazonaws.com/robocore-lojavirtual/709/HC-05_ATCommandSet.pdf) \
> **HC-08 AT Command Manual (Reference):** [PDF](https://www.rhydolabz.com/documents/30/hc05_bluetooth.pdf)

### AT Command Configuration Steps

> **Reminder:** End every AT command with **CRLF (`\r\n`)**. So, you may need to press a enter to add new line manally before sending out the command if you are using raw mode.

Configure the **Slave first**, because you need its Bluetooth address when configuring the Master.

#### Slave Module

1. Check the connection using `AT`.
2. Give the module a recognizable name using `AT+NAME=<Slave_Name>`.
3. Set a password using `AT+PSWD=<Same_Password>`. Use the same password for both modules.
4. Set the UART setting using `AT+UART=115200,0,0`.
5. Set the role to Slave using `AT+ROLE=0`.
6. Check the Slave address using `AT+ADDR?` and write it down.
7. Check the settings using `AT+NAME?`, `AT+PSWD?`, `AT+UART?`, and `AT+ROLE?`.

For example, if `AT+ADDR?` returns:

```text
+ADDR:1234:56:ABCDEF
```

The address used in the Master commands will be `1234,56,ABCDEF`.

#### Master Module

1. Check the connection using `AT`.
2. Give the module a recognizable name using `AT+NAME=<Master_Name>`.
3. Set the same password as the Slave using `AT+PSWD=<Same_Password>`.
4. Set the UART setting using `AT+UART=115200,0,0`.
5. Set the role to Master using `AT+ROLE=1`.
6. Set the connection mode to a specified device using `AT+CMODE=0`.
7. Bind the Master to the Slave using `AT+BIND=<Slave_Address>`.
8. Check the settings using `AT+NAME?`, `AT+PSWD?`, `AT+UART?`, `AT+ROLE?`, `AT+CMODE?`, and `AT+BIND?`.

Using the example Slave address above, the binding command is:

```text
AT+BIND=1234,56,ABCDEF
```

If the modules do not connect automatically, keep both modules powered and try the following commands on the Master:

```text
AT+INIT
AT+PAIR=1234,56,ABCDEF,20
AT+LINK=1234,56,ABCDEF
```

Replace `1234,56,ABCDEF` with the actual address of your Slave module.

> Both modules must use the same UART setting. The recommended setting is `115200` baud, 1 stop bit, and no parity.

After configuration, exit AT mode and connect each HC-05 to the UART port of its STM32 board or device. Remember to cross the UART wires: HC-05 `TXD` connects to STM32 `RX`, and HC-05 `RXD` connects to STM32 `TX`. Both modules must share `GND` with their connected boards.

Power both modules. The Master will search for and connect to the bound Slave. When the LED flashing pattern changes, the Bluetooth link is established. Data sent to the UART of either module will then appear at the UART of the other module.

[Previous](./04-non-blocking-uart.md) | [Next Page](./06-homework.md)
