# Homework 2: Blackjack

[Back to Main](./README.md) | [Previous Page](./03-classwork.md)

Build a blackjack game with **one mainboard as the dealer** and **two RDC controllers as the players**. Connect the boards through UART using four HC-05 modules: two on mainboard and one on each controller.

Players use buttons to choose and confirm bets, then request **Draw, Double or Stop**. Mainboard deals the cards and sends updates so the controllers display each player's current status.

The game rules and card drawing are provided. Complete the TODOs in each board's `hw.c` to implement your UART commands, button actions and dealer short/long press controls.

For the skeleton code, detailed instructions and marking scheme, please refer to the [Homework 2 blackjack repository](https://github.com/UST-Robotics-Team/Software-Tutorial-2026-Homework2-skeleton).

[Back to Main](./README.md) | [Previous Page](./03-classwork.md)
