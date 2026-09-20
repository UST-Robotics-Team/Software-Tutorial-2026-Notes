# Draft

> Author: Ryan (<rcwku@connect.ust.hk>)  
> Feel free to email/discord dm me for any clarifications on the homework.

## Skeleton

The skeleton can be downloaded here: TBA

## Homework Format

There will be **3** main homework tasks, each focusing on a different topic.  
All tasks will be split into part A and part B: (so there's a 1A, 1B, 2A, 2B, 3A, and 3B)

- Part A \(**MANDATORY**\):
  - These questions will be marked, and will affect your eligibility of going to later phases.
- Part B \(**OPTIONAL/BONUS**</u>\):
  - These are extended tasks that are related to the topic.
  - As these tasks might be way too hard, they will only act as further reference. They will be marked if you attempt them, but will **NOT** give you any additional points or whatsoever.

For all 3 tasks, you will be given a bare-bones skeleton file (and some library/helper functions) to assist you in making the program.

## Ground rules

- You may **NOT** use functions that were not taught in the tutorial unless you were specifically instructed to do so. (no `malloc` etc)
- You cannot add any other external libraries. However, you may include your own helper functions within the files provided for you to edit.
- There will be some provided helper functions (in `given.c`) for Task 3 to assist you. You can use those functions as you please, but you cannot modify them.
  - The above rules are mainly here for fairness purposes, so that you won't have any external advantage over other trainees :D
- Have fun (?)

- AI tools are discouraged, as the aim of this assignment is to let you get used to coding and programming using C. Using any form of AI would defeat the purpose and for this specific homework, I highly encourage you to try to think and code yourself, without having to rely on external help.

## Tasks

Here are the following tasks and their respective topics:

- [Task 1](./Task-1/README.md):
  - Mathematical Models
- [Task 2](./Task-2/README.md):
  - Data Validation
- [Task 3](./Task-3/README.md):
  - Scrabble

## Compiling and Testing

----------------- WIP -----------------------

## Grading

>It is completely fine to not be able to complete this homework, as it is only here to help your C coding skills.  
>Just to get you used to coding in C with (somewhat, and hopefully) interesting assignments.

There will be 3 main portions of the grading:

>It will be graded out of 100 anyway so like 1% translate to 1 mark etc etc... Expect decimals in your marks I suppose?

- Functionality: 95%
  - Public test cases: 24%
    - These are provided along with the skeleton code. You can download these from the official GitHub repo.
    - They are mainly examples already provided in the README.md file, and will test the base-line functionality of the code.
  - Hidden test cases: 65%
    - These test cases will first be hidden from you.
    - They will only be released publicly after your homework has been graded.
    - The test cases will test the more complex functionality and edge cases of the code. (And prevents you from hard coding the entire program.)
  - Compiling: 1%
    - If your code successfully compiles, you get 1 freebie point :)
- Clarity: 5%
  - Based on your approach/documentation of the code.
  - Will be given sparingly (if done normally, you will be given the full 5%).
  
It is encouraged to create your own test cases to make sure that your code is accurate and functional.  
(Following the format in the test cases folder)

If the output came out as wrong during grading due to some trivial error (such as floating point errors possible in Task 1), depending on the severity of deviation, points may or may not be deducted.  
(For example, if the answer is `3.5` but for some reason, your program outputs as `3.4999999999999999999...` due to some floating-point error, we will not deduct points in this case.)
