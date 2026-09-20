# Servo Motor

>The servo of this data sheet is not the servo you are using in the tutorial. We are using MG996R Servo Motor

![data sheet reference](https://i.imgur.com/kcznbWB.png)

### What is servo motor?

Servo motor is a special type of motor that can only rotate from -90 degree to 90 degree (or -135 to 135 degree for some other servos). It is DIFFERENT from the other motors you see before so you cannot make it spin like a wheel.

### How to control a servo motor?

To control a servo motor to move to a specific angle, we need to use send a PWM signal to the servo (and of course we also need to give it enough power to move).
So first, we will learn about PWM and come back later.

[PWM](01-pwm.md)

---

### Controlling servo with PWM
#### Connections
> WARNING: DO NOT MOVE THE SERVO MOTOR SHAFT BY HAND!\
It may burnt your board when connected.

Connect the servo motor to the correct pins of your mainboard

- Orange PWM wire of servo connect to the pin you chose (PC7(TIM3\_CH2) for the example above)
- Red 5V wire of servo connect to Vcc(Voltage) of GPIO port
- Brown GND wire of servo connect to GND(Ground) of GPIO port

<details>

<summary>My servo may have different color wires!</summary>


Servos of different models have different colored wires.

For servos with White, Red, Black wires, their color code is:
- White PWM wire of servo connect to the pin you chose (PC7(TIM3\_CH2) for the example above)
- Red 5V wire of servo connect to Vcc(Voltage) of GPIO port
- Black GND wire of servo connect to GND(Ground) of GPIO port

</details>

![](images/Servo-wires.png)![](images/GPIO_pins.png)
After connecting, feel free to try to control the motor by generating PWM with different on-times.\
It may be helpful to write a function to help control the motor by mapping desired angle -> on-time.

**ClassWork (Optional)**

Try to control servo motor to turn to -90 degrees-> 0 degrees -> 90 degrees (with a short pause at 0 degrees)

> Note: for the servo motor we are using, the on-time at -90 degrees should be 0.5ms, and the on-time at 90 degrees should be 2.5ms. Calculate the on-time for 0 degrees on your own.
>
> Bonus: control the angle of the motor with a button

> Note: We are using TIM5 and channel 1
