
[Back to Tutorial 1](./) | [Previous: GPIO](01-gpio.md) | [Next: TFT](03-tft.md)

**This section contains Classwork 2**

# 2. HAL Clock

While knowledge of GPIO allows for immediate input response in a robot, it is not sufficient on its own. In embedded systems, time management is crucial for tasks such as scheduling, generating PWM signals, and managing delays. The STM32 microcontroller utilizes the Hardware Abstraction Layer (HAL) to handle clock functions efficiently. This section will focus on the system clock and setting up timers for various tasks.

> **Hardware Abstraction Layer (HAL)**: A software layer that provides an interface for hardware components, allowing developers to write code without needing to understand the underlying hardware details.

The system clock in STM32 is a critical component that drives the operation of the microcontroller. It provides the timing needed for executing instructions and managing peripheral operations. The HAL library offers convenient functions to interact with the system clock.

**Outline**
- `HAL_GetTick()`
- Non-blocking delay
- **Classwork 2**

---

### Current time in milliseconds

The `HAL_GetTick` functions returns the number of milliseconds that have passed since the program began execution. Effectively, it can serve as a timer in the lifespan of the program execution.

```c
uint32_t HAL_GetTick(void);
uint32_t ticks = HAL_GetTick();
// Return how many ms have pass though since the MCU start running
```

- In STM32, the MCU has introduced an application time base that increments every 1 ms. Using `HAL_GetTick()` returns the time base (in ms) since the mainboard was powered on.
- You can think of the MCU as holding a stopwatch that starts when the MCU begins running, and `HAL_GetTick()` is ask the stopwatch what is the counting right now

```c
void HAL_Delay(uint32_t Delay);
```

- This function pauses program execution for a specified number of milliseconds.
- While straightforward, using `HAL_Delay()` can halt all operations, which is often undesirable in real-time applications. Instead, consider using non-blocking techniques to achieve delays.

### Demo: Non-blocking delay with `HAL_GetTick()`

- An LED that toggles every 200ms:
  ```c
  while (1) {
      static uint32_t last_ticks = 0;
      // Static attribute keep the value across every
      // iterations while it will not be re-initized
      //
      // Everything inside this if-statements gets called
      // every 200ms.
      if((HAL_GetTick() - last_ticks) >= 200){
          gpio_toggle(LED1);
          last_ticks = HAL_GetTick();
          //Store the tick of last time
      }
  }
  ```

- An LED that turns on for 100ms after you press some button `BTN1` for the first time:
  ```c
  while (1) {
      static uint32_t last_ticks = 0;
      static uint8_t btn_pressed = 0;
      if (!btn_pressed && btn_read(BTN1)){ //Only when never pressed
          btn_pressed = 1;
          last_ticks = HAL_GetTick();
      }
      if (btn_pressed){
        if ((HAL_GetTick() - last_ticks) <= 100){
            led_on(LED1);
        }
        else {
            led_off(LED1);
        }
      }
  }
  ``` 

## Classwork 2: GPIO and HAL

For your second graded classwork, your task is to create a program that will flash LEDs based on button presses.

- While `Button5` is held, `LED1` should blink every **100ms**, and `LED2` should be off **@1**
- While `Button1` is held, `LED1` and `LED2` should blink **alternately** every **500ms**. **@2**

Ask for a senior to mark your work when you're done.

**Reminder: Please save your code for Classwork 2 in a separate file somewhere before heading to the next part of the tutorial!**

---

[Back to Tutorial 1](./) | [Previous: GPIO](01-gpio.md) | [Next: TFT](03-tft.md)