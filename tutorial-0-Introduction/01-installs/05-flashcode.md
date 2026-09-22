# Flashing Code

<details>

<summary>Authors</summary>

Ng Hau Yi Chloe (hycng@connect.ust.hk)

</details>

## System Overview
Below shows the whole system:
![alt text](images/flashcode2.jpeg)

**Note:** Bring a USB to Type C adpater if needed

## Connection with ST-Link
Here is the specific wiring between the STM32 Board the ST Link:

| Name   | Number on ST Link | Letter on Board |
|--------|-------------------|-----------------|
| 5V/VCC | 1                 | a               |
| GND    | 4                 | b               |
| SWCLK  | 2                 | d               |
| SWDIO  | 3                 | c               |

![alt text](images/flashcode1.png)

![alt text](images/flashcode3.jpeg)
**Note:** The rainbow wires are connected to the bottom row of the ST Link (bottom relative to the side of the logo and text)
## Flashing Code into the board
1. Connect the ST-Link to your computer's USB Port
2. Open VS Code and open the STM32 project folder