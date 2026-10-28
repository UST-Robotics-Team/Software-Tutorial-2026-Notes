# RDC Controller

#### Original Author: Hedy

![](/images/controller.jpeg)

In tutorials, you have worked with almost all the features of the controllers
that may be helpful for RDC. This document should provide you some additional
information and tips for working with it during RDC, and using the controller in
your final RDC D-Day.

Aka, how not to destroy your controller and have to spend credits in getting
another one...

The hardware schematic, some further resources, and the design principles are
published in a separate [project repository
here](https://github.com/HKUST-Intelligent-Racing/2026-RDC-Controller).

> [!Note]
>
> Although the usage should be pretty intuitive (hopefully...), it is still
> **highly recommended** that you carefully read through this document to know
> about some of the features and tips not mentioned in SW Tutorials as it will
> be helpful for your RDC!

## (!!!) Basic reminders

- Keep your batteries charged!
- Turn off the switch when not in use
- Do NOT let the the PCB get in contact with metal surfaces -- something may
be shorted, and if you're unlucky, something disastrous may happen...
- Do NOT try to charge the battery using the USB-C port on the STM Bluepill (at
the back side). Use the custom USB-C port at the bottom left instead

## Powering, and managing the battery

The controller can be powered in two ways:
- With a single rechargeable battery (18650), or
- Using a Type-C USB cable

> [!Tip]
>
> It can also be used while the battery is charging with the USB-C cable plugged
> in.

The controller comes with two battery slots -- intended for backup storage,
weight distribution, and also ergonomics benefits. Please read the silkscreen
labels and ensure you plug in the battery you want to use at the correct slot.

## Flashing code

Connect ST-Link wires to the four pins on the bluepill at the back. **Don't try
to use the USB-to-TTL module to flash code!!**

> [!Note]
>
> It is highly recommended to turn off the switch when flashing code.

## Buttons

All buttons and limit switches should be set to **pull up** -- read a GPIO LOW
when pressed, and a GPIO HIGH when released.

The 8 D-Pad buttons are labelled at the center of the D-Pads, where the number
indicates the label of the GPIO Input pins in the IOC configuration.

## Bluetooth / HC-05

The HC-05 bluetooth module is powered by **5V**, however, ST-Link only provides
**3V3**. To enable the HC-05 module, you must either power the controller with
USB-C, or turn on the battery. **Remember to unplug the ST-Link when powering
the controller with battery**.

The UART and the HC-05 headers on the controller share the **same UART** in
STM32 configuration -- both are **USART1**. Connecting the HC-05 using rainbow
wires to the UART port is the same as simply plugging in the HC-05 into its
slot.

## Debugging features

There are UART indicators under the UART header that automatically light up
during UART RX/TX transmission.

Joysticks are also equipped with buttons, the LEDs right next to each joystick
are hardware-level LED indicators that changed based on the joystick button
state.

## Backup ADCs (toggle with `0R` resistors)

In the situation where the joystick ADC channels are not receiving the correct
data for whatever reason (and have been confirmed it's not a software issue),
ask your hardware teammate to desolder and resolder one of the `0R` resistors at
the back side of the board for the corresponding joystick.

There are four `0R` slots for each joystick, two for X-axis ADCs and two for
Y-axis -- one that enables the original ADC, another that enables the backup
ADC.

## Display screen

The space on the controller supports either an **ST7735 1.8″ 128x160** TFT, or a
**LongQiu ST7789 2.0″ 240x320** TFT. The first one was taught and used in
tutorials, while the second one provides you more space for more debugging
information or supplementary UI for your controller.

To select the TFT screen mode:

1. Open `Core/Inc/lcd/lcd.h` in the controller firmware project.
2. Change the existing `TFT_SCREEN_MODE` definition to match your display. Use
   **only one** of the following options:

   **ST7735 1.8″ 128x160:**

   ```c
   #define TFT_SCREEN_MODE TFT_SCREEN_ST7735_1_8_INCH_128X160
   ```

   **LongQiu ST7789 2.0″ 240x320:**

   ```c
   #define TFT_SCREEN_MODE TFT_SCREEN_ST7789_2_0_INCH_240X320
   ```

3. Save the file, and recompile.

