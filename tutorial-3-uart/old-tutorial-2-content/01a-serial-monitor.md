# Serial Monitor Setup

[Back to Main](./README.md) | [Previous Page](./01-uart.md)

> Author: Ken Law (cclawad@connect.ust.hk)

## Introduction

To communicate with your STM32 board via UART, you need a serial monitor program on your computer. This tool lets you send and receive data easily. Below are instructions for installing and configuring a serial monitor.

## Installation

- **CoolTerm (Mac):** [https://freeware.the-meiers.org/](https://freeware.the-meiers.org/)
- **Serial Debug Assistant (Windows via Microsoft Store):** [https://apps.microsoft.com/store/detail/serial-debug-assistant/9NBLGGH43HDM](https://apps.microsoft.com/store/detail/serial-debug-assistant/9NBLGGH43HDM)
- **Baud Dance Serial Monitor (Webpage, only with Simplified Chinese):** [https://serial.baud-dance.com](https://serial.baud-dance.com)
  > Not recommanded using unless you are really unable to download either of the above

## Coolterm

### Configuring

1. Open CoolTerm.
2. Set the following options:

```
Options -> Serial Port
-> Port: Select the port connected to your TTL adapter
-> Baud Rate: 115200
-> Data Bits: 8
-> Parity: None
-> Stop Bits: 1

Options -> Terminal
-> Terminal Mode: Raw mode
-> Local Echo: Unchecked
```

> - **Raw mode:** Data is sent immediately when you press a key.
> - **Line mode:** You can type a full string and send it at once. This is useful for Bluetooth configuration.
> - **Local echo** only affects display—it shows what you type but does not change the data

Press **Connect** and run your board. Messages should appear in the terminal.

### Sending string under raw mode

Go to top nevigation bar, the click `Connection -> send string`.

## Serial Debug Assistant

![](./image/serial%20debug%20mon.jpeg)

Basically needs to set nothing :p

> If nothing shows up on the `Port` tab, you may need to install a USB to TTL Ch34x driver ([Windows](https://www.wch-ic.com/downloads/CH341SER_ZIP.html) / [Mac](https://www.wch-ic.com/downloads/CH34XSER_MAC_ZIP.html) / [Linus](https://www.wch-ic.com/downloads/CH341SER_LINUX_ZIP.html))

[Back to Main](./README.md) | [Previous Page](./01-uart.md)
