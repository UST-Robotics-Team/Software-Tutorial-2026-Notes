# Classwork

[Back to Main](./README.md) | [Previous Page](./02-bluetooth.md)

## Classwork #1: Monitor the controller data

Task:
- Connect the controller's uart to the ttl and use the serial monitor to look at the msg
- There are 8 button on the controller, when the button being pressed, send the msg to the serial monitor in the following format " button x pressed "
- And send msg from the serial monitor to the controller in the following format " button x count " to ask the controller send the specific button count to the serial monitor in the following format " button x count: y "

## Classwork #2: Wireless Communication between two device

Task
- Config one set hc05 (Master and slave) then Master hc05 plug to controller and the slave hc05 plug to mainboard
- Create a controller panel on the mainboard's tft, showing 8 button (you may use 0/1 or colored square) , so when you press the button on the controller, the corresponding button on the mainboard's tft will indicate the button being pressed

## Useful function

- snprintf() — Format values into a string, with a buffer-size limit. Useful for creating "button 3 count: 5".
- sscanf() — Read values from a string. Useful for extracting 3 from "button 3 count".
- strcmp() — Compare two strings. Returns 0 when they are exactly the same.



[Previous](./02-bluetooth.md) | [Next Page](./04-homework.md)
