The homework for Tutorial 2 (called "Homework 2") is split into two independent parts, part A (3 marks) and part B (7 marks), for a total of 10 marks. Both are graded!

[Back to Main](./README.md) | [Previous Page](./03-classwork.md)

# Part A: Button query (3 marks)

In your classwork, you have made a simple monitoring program that sends UART data to your laptop's serial monitor to detect button presses. In Part A of your homework, you will write a program that allows you to query the number of presses of a specific button using your serial monitor.

Requirements (total: 3 marks)
- The user sends a command FROM the serial monitor TO the controller in the following format:
  ```
  button x count
  ```
- The controller should respond the number of presses of that specific button `x`, in the following format:
  ```
  button x count: y
  ```
  (**@3**)

Example sequence of behaviour:
  1. user: presses no buttons and sends via serial monitor `button 1 count`
  2. controller: responds `button 1 count: 0`
  3. user: presses button `1` twice
  4. user: sends `button 1 count`
  5. controller: responds `button 1 count: 2`
  6. user: presses button `5` once, and presses button `1` once again
  7. user: sends `button 5 count`
  8. controller: responds `button 5 count: 1`
  9. user: sends `button 1 count`
  10. controller: responds `button 1 count: 3`

# Part B: Bluetooth Controller Panel (7 marks)

In the Robot Design Contest, you will use all of the buttons and functions on the controller. Sometimes, as software members we need to build a good user interface for other teammates to work with. It's helpful to have a Panel UI to monitor the status of buttons and verify all the hardware components on the controller are working, before making it work for your robot.

In this homework, you will build a monitoring panel that allows you to receive controller data via **Bluetooth** from the controller to the **mainboard**'s TFT screen.

---

Tasks (total: 7 marks):

- Configure a pair of HC-05 modules (Master and slave) according to the Bluetooth lecture materials.
- Plug in the Master HC-05 to controller and the slave HC-05 to mainboard, and make sure the two HC-05's can connect. (**@1**)
- Create a controller panel on the mainboard's TFT. The TFT should show the button pressing status of all 8 buttons and 2 limit switches (you may use `0`/`1` or colored squares), so when you press the button on the controller, the corresponding button on the mainboard's tft will indicate the button being pressed.
- The panel UI should include:
  - 8 buttons (**@2**)
  - 2 limit switches (**@1**)
  - connection status of bluetooth (e.g., a message indicating whether bluetooth is connected between mainboard and controller) (**@1**)
  - the indications on the panel should work as expected when multiple buttons are pressed simultaneously (**@2**)

> [!tip]
>
> You will need to work on two STM32 projects (opened in SEPARATE VS Code windows) for this task, and you will also need to flash the code to each PCB (Controller, Mainboard) separately.

## Useful functions

- snprintf() — Format values into a string, with a buffer-size limit. Useful for creating "button 3 count: 5".
- sscanf() — Read values from a string. Useful for extracting 3 from "button 3 count".
- strcmp() — Compare two strings. Returns 0 when they are exactly the same.


## Additional exercise project: Bluetooth Blackjack

The blackjack project is **OPTIONAL** and only serves as a demonstration (and additional practice) for UART and Bluetooth. In this project, you can build a blackjack game with **one mainboard as the dealer** and **two RDC controllers as the players**. Connect the boards through UART using four HC-05 modules: two on mainboard and one on each controller.

[Blackjack project skeleton](https://github.com/UST-Robotics-Team/Software-Tutorial-2026-Blackjack-Skeleton)

You can choose to attempt this project after you have completed the homework.

**NOTE: the blackjack project is optional and will not be counted towards your tutorial score**.

[Back to Main](./README.md) | [Previous Page](./03-classwork.md)
