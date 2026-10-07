# Classwork

[Back to Main](./README.md) | [Previous Page](./02-serial-monitor.md)

## Classwork #1: Monitor the controller data using UART-to-TTL

You do not need the bluetooth module for this classwork.

Task (total: 2 marks):
- Connect the controller's UART port to the TTL module and use the serial monitor to receive the message
- There are 8 buttons on the controller, when any button is pressed (**rising edge**), send a message to the serial monitor in the following format: `button x pressed` (**@2**)


## Useful functions

In addition to the `HAL` library functions for working with UART, you may find these function(s) useful:

- `snprintf()` — Format values into a string, with a buffer-size limit. Useful for creating "button 3 pressed".


[Previous](./02-serial-monitor.md) | [Next Page](./04-non-blocking-uart.md)
