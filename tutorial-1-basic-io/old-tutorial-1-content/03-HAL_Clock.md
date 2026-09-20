[Previous Page](02-GPIO.md)

# HAL

Hardware Abstraction Layer (HAL) is a software layer that provides a standardised interface between application code and hardware components. Allowing developers to write code without having to fully understand the hardware details.

## HAL library

>As mentioned before, `HAL_GPIO_ReadPin` and `HAL_GPIO_WritePin` are both from the HAL library. 

In addition to pin reading and writing, accessing the system clock is also very important. 

```c
uint32_t HAL_GetTick(void);
uint32_t ticks = HAL_GetTick();
// Return how many ms (1/1000th of a second) have pass though since the MCU start running
```

The MCU starts counting time starting from when it receives power. Using `HAL_GetTick()` allows for timing manipulation for different utilities and functions. 

### Examples

- LED1 toggles every 200ms:

  ```c
  while (1) {
      static uint32_t last_ticks = 0;
      //Static attribute keep the value across every iterations while it will not be re-initized
      //Everything inside this if-statements gets called every 200ms
      if((HAL_GetTick() - last_ticks) >= 200){
          gpio_toggle(LED1);
          last_ticks = HAL_GetTick();
          //Store the tick of last time
      }
  }
  ```

- LED1 turns on for 100ms after BTN1 is pressed for the first time:
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

### Demo: Writing Code in a function 
While you might only need to write tens of code to finish different classwork and homework, in real life you would write thousands line of code , and so it is important for you to write your code in different functions.

In today tutorial, you should put all your code in the four function we give to you in `gpio_classwork.c`, here I would provide you an example of how it works

1. Write what you want it to do every loop:
   1. During the 1 - 2 second: `LED3` is flashing (toggle every 100 ms)
   2. During the 3 - 4 second: Only turn on `LED4` 
    ```c
    /* tutorial2_hw.c*/
    void gpio_classwork(void) {
    /* Your code start here */
        // You should use static uint32_t here, as any variable that defined in main.c cannot call here unless you extern it
        static uint32_t last_ticks_btn = 0;
        static uint32_t last_ticks_led = 0;
        if (HAL_GetTick() - last_ticks_btn <= 2000){ 
            // Inside the Flashing Cycle
            led_off(LED4);
            if (HAL_GetTick() - last_ticks_led > 100){
                led_toggle(LED3);
                last_ticks_led = HAL_GetTick();
            }
        }
        else if ((HAL_GetTick() - last_ticks_btn > 2000) && (HAL_GetTick() - last_ticks_btn < 4000)) {
            led_off(LED3);
            led_on(LED4);
        }
        else {
            last_ticks_btn = HAL_GetTick();
        }        
    /* Your code end here */
    }
    ```

2. After you have written your program in `gpio_classwork.c`, you would like to call it in your main loop.
   - Before calling it, you need to have declared this function before the `main` function. 
   - Normally we will do by include a corrsponding `.h` of that `.c`, but as we forogr to give you this.
   - So you can directly put the function prototype (function declaration) in the top of your `main.c`
        ```c
        /* main.c */
        /* USER CODE BEGIN PFP */
        void gpio_classwork(void);
        /* USER CODE END PFP */
        ```
3. After you have done all these, you can directly call the function in your `main.c`:
   ```c 
    /* main.c::int main() */

    /* USER CODE BEGIN WHILE */
    while(1){
        gpio_classwork();
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
   ```

### Bad Example 
What's wrong with the code below?
> ```c
>/*This is the while(1) inside main.c*/
>while(1){
>    if (btn_read(BTN1)){
>        gpio_toggle(LED1);
>    }
>    if (btn_read(BTN2)){
>        static uint32_t last_ticks_BTN = 0;
>        last_ticks_BTN = HAL_GetTick();
>        while (HAL_GetTick - last_ticks_BTN < 1000){
>            gpio_toggle(LED2);
>        }
>    }
>}
> ```

- Don't use loops inside the main loop, it will block other tasks from happening at the same time. When the bottom while loop is looping, the robot will focus on flashing LED2, ignoring any input from BTN1 for the 1000ms that the loop is ongoing for.
- This is also the reason why `HAL_Delay()` isn't used.

# Classwork 1: .ioc, GPIO & HAL
<!--
* When `BTN1` is held, `LED1` should be on. **(@1)**
* When `BTN2` is held, `LED2` should be flashing (toggle in 50ms).**(@1)**
* When both `BTN1` and `BTN2` are held, the following sequence is conducted:**(@2)**
  * `LED1` and `LED3` are on while `LED2` are flashing.
  * After 1 second, `LED1` and `LED3` are flashing while `LED2` are on.
  * After 1 second, repeat from step 1.
* Keyword: Finite State Machine
-->
- Make your code, such that BTN1 does all of the following at the same time:
  - When BTN1 is pressed, toggle LED1 **once** **(@1)**
  - After BTN1 is held longer than 1s (and <10s), toggle LED1 every 500ms **(@1)**
  - After BTN is held longer than 10s, toggle LED1 every 200ms for 4s, and change the interval from 200ms to 1000ms for 10s, then back to 200ms for 4s, and continue until the button is released. **(@1)**

[Next Page](04-TFT.md)
