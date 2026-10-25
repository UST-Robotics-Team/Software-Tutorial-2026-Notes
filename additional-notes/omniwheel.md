# Omniwheel

<details>

<summary>Authors</summary>

Joyce Li, Dicaprio Cheung

</details>

## Table of Content

[#what-is-an-omniwheel](omniwheel.md#what-is-an-omniwheel "mention")

[#how-does-it-work](omniwheel.md#how-does-it-work "mention")

[#things-to-work-on](omniwheel.md#things-to-work-on "mention")

## What is an omniwheel?

![](https://i.imgur.com/AlYSzcP.png)

Omniwheels are wheels with small discs (called rollers) around the circumference which are perpendicular to the turning direction. The effect is that the wheel can be driven with full force, as well as sliding laterally. &#x20;

<figure><img src="https://i.imgur.com/jEEtTZ9.png" alt="" width="375"><figcaption></figcaption></figure>

Robots built with omni wheels are able to move in any direction without steering the robot itself.

## How does it work?

### Simplest Case: wheelbase moving forward

Suppose you want a three wheel omni wheelbase to move forward with speed 1m/s, how much force should each wheel give?

<figure><img src="../images/image (1) (1) (1) (1).png" alt="" width="375"><figcaption></figcaption></figure>

> To people who don't know what vectors are: you may just treat it as decomposing a diagonal line to get its x and y respectively (but with directions).
>

<figure><img src="../images/image (1) (1) (1) (1) (1).png" alt="" width="375"><figcaption></figcaption></figure>

#### Decomposing the magnitude of each wheel in x and y direction

<figure><img src="../images/image (2) (1) (1).png" alt="" width="375"><figcaption></figcaption></figure>

**X-direction**

$$
F_x = 0\\A_x = A\\B_x = B \cdot \cos60 ^{\circ}\\C_x = C \cdot \cos60 ^{\circ}
$$

**Y-direction**

$$
F_y = F = 1\\ A_y = 0\\ B_y = B \cdot \cos30^{\circ}\\ C_y = C \cdot \cos30^{\circ}
$$

$$
F_x = A_x - B_x - C_x \\A - B \cdot \cos60^{\circ} - C \cdot \cos60^{\circ} = 0
$$

$$
F_y = C_y - B_y\\C \cdot \cos30^{\circ} - B \cdot \cos30^{\circ} = 1
$$

**Torque (Rotational force)**

Moreover, the robot is not spinning, therefore the torque = 0. So,

$$
F_\theta = A+B+C \\A+B+C= 0
$$

Solving the simultaneous equations:

$$
1.\; A - B \cdot \cos60^{\circ} - C \cdot \cos60^{\circ} = 0\\2.\; C \cdot \cos30^{\circ} - B \cdot \cos30^{\circ} = 1\\3.\; A + B + C = 0
$$

$$
A = 0\\B = -\frac{1}{\sqrt{3}} = -0.577\\C = \frac{1}{\sqrt{3}} = 0.577
$$

## Things to work on

We have shown you how to calculate the speed of each wheel in order to move the wheelbase forward. Could you find out the general equation for $F$ in any direction and magnitude? (i.e. speed of wheel $A$, $B$, $C$ in relation to $F_x$ and $F_y$)

&#x20;

<figure><img src="../images/image (3) (1) (1) (1).png" alt="" width="375"><figcaption></figcaption></figure>

[Suggested answer](https://physics.stackexchange.com/questions/57401/omni-directional-motion-resolving-three-or-more-vectors): [https://physics.stackexchange.com/questions/57401/omni-directional-motion-resolving-three-or-more-vectors](https://physics.stackexchange.com/questions/57401/omni-directional-motion-resolving-three-or-more-vectors)&#x20;

##
