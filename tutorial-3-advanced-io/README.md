# Tutorial 3: PWM & Servo Control

<details>
<summary>Author</summary>

NGO Tho Quang (tqngo@connect.ust.hk)

</details>

## Contents

1. [PWM](./01-pwm.md)

   - PWM principles and the timer registers (PSC / ARR / CCR)
   - The 50 Hz servo standard and the APB timer-clock trap (84 vs 42 MHz)
   - **Classwork 1** (calculate, generate, and measure PWM; test servo positions)

2. [Buttons + TFT](./02-buttons-tft.md)

   - STM32CubeMX timer setup and `HAL_TIM_PWM_Start`
   - Rising-edge button detection
   - **Demo** (button steering + commanded angle on the TFT)

3. [Wireless Control](./03-wireless.md)

   - Serial command protocol over Bluetooth
   - D-pad presets, hold-to-move, speed, and the 300 ms watchdog
   - **Classwork 2** (wireless servo control)

## Classworks (graded)

There are 2 classworks in this tutorial. Show your working numebers (classwork 1) and mainboard to our seniors (classwork 2) during the tutorial to get your score recorded. Since this is the last tutorial, please try to complete all classworks to get the full score.

## Homework

Since this is the last tutorial, there is no homework assignment.

---

Begin with the first lesson:

[PWM](./01-pwm.md)
