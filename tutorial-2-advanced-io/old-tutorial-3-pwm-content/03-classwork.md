# Classwork
[Back to Main](README.md)

## Classwork 1

There are many combinations of prescaler value and auto reload register that can generate the same frequency output.

Find 3 possible combinations of prescaler value and auto-reload values for a PWM with 50Hz frequency.

> Yes, this is just a MATH question.

> Hint: *** Remember they are `uint16_t` . So, they can only be 0 to 65535***

[Back to notes](01-pwm.md#tim-psc--arr)

## Classwork 2

Choose 1 of your combination of prescaler value and auto reload register from classwork 1.

Calculate the CCR value for the 50Hz PWM to have 2 ms on-time

> Yes, this is another MATH question.

[Back to notes](01-pwm.md#on-time-channels--ccr)

## Classwork 3

Try to move the motor 
- in both directions, and for each direction, 
- 2 different speeds (1 slow, 1 fast as long as visibly different).

e.g. PWM duty cycle = 50% (0.5), dir = CW (Clockwise)

> Remember to use GPIO for direction
> [GPIO Recap](tutorial-1-basic-io\02-GPIO.md)

> It is suggested to at least try this out yourself since you will be using this motor in the RDC later.

[Back to notes](02-sami_motor.md)