# Robotics Software Tutorial: C Programming Assignment

> Author: Ryan (<rcwku@connect.ust.hk>)  
> Feel free to email/discord dm me for any clarifications on the homework.

## Homework Format

There will be **3** main homework tasks, each focusing on a different topic.  
All tasks will be split into part A and part B: (so there's a 1A, 1B, 2A, 2B, 3A, and 3B)

- Part A \(**MANDATORY**\):
  - These questions will be marked, and will affect your eligibility of going to later phases.
- Part B \(**OPTIONAL/BONUS**</u>\):
  - These are extended tasks that are related to the topic.
  - As these tasks might be way too hard, they will only act as further reference. They will be marked if you attempt them, but will **NOT** give you any additional points or whatsoever.

For all 3 tasks, you will be given a bare-bones skeleton file (and some library/helper functions) to assist you in making the program.

## Ground Rules

- You may **NOT** use any C library functions that were not mentioned in the tutorial unless you were specifically instructed to do so. (no `malloc` etc)
- You cannot add any other external libraries. However, you may include your own helper functions within the files provided for you to edit.
- There will be some provided helper functions (in `given.c`) for Task 3 to assist you. You can use those functions as you please, but you cannot modify them.
  - The above rules are mainly here for fairness purposes, so that you won't have any external advantage over other trainees :D
- Have fun (?)

- AI tools are discouraged, as the aim of this assignment is to let you get used to coding and programming using C. Using any form of AI would defeat the purpose and for this specific homework, I highly encourage you to try to think and code yourself, without having to rely on external help.
- Obvious use of AI will negatively affect your chances of proceeding. (We have ways to tell)

## Tasks

Here are the following tasks and their respective topics:

- [Task 1](./Task-1/README.md):
  - Arrays and more Arrays
- [Task 2](./Task-2/README.md):
  - Data Validation
- [Task 3](./Task-3/README.md):
  - Scrabble

## File Structure

```text
skeleton/
├── run_tests.ps1                # test runner - Windows
├── run_tests.sh                 # test runner - macOS / Linux (I only tested on Linus as I do not have a Mac device .-.)
│
├── Task-1/
│   ├── Task1.c                  # <- Task 1A and 1B
│   ├── Task1.h                  # <- Task 1A(ii)
│   ├── main.c                   
│   └── testcases/
│       ├── testcase1/
│       │   ├── input.txt        # the scripted stdin
│       │   └── output.txt       # the expected output
│       └── testcaseB1/          # one folder per test ('B' = Part B)
│
├── Task-2/
│   ├── Task2.c                  # <- Task 2A and 2B
│   ├── Task2.h
│   ├── main.c
│   └── testcases/
│       └── testcase1/
│           ├── input.txt
│           └── output.txt
│
└── Task-3/
    ├── Task3.c                  # <- Task 3A and 3B
    ├── Task3.h
    ├── main.c
    ├── given.c                  # given helper functions (do not modify)
    ├── lib/                     # additional helper functions (do not modify)
    └── testcases/
        └── testcase1/
            ├── state.txt        # board position to import (Task-3 only)
            ├── input.txt
            └── output.txt
```

## Compiling and Testing

The test runners compile each task with its required source files, run all
matching test cases, and report missing or unexpected output. Run them from the
repository root, or provide the path to the root script when running from
another directory:

```text
powershell -ExecutionPolicy Bypass -File .\run_tests.ps1 -Task 1 # Windows
bash ./run_tests.sh 1                                           # macOS / Linux
```

Use `-Task 2` or `-Task 3` for an individual task, or `-Task all` / `all` to
run every task.

| Flag | PowerShell | bash | Effect |
| ------ | ------------ | ------ | -------- |
| Task | `-Task 1`, `-t 1` | `1`, `-t 1` | Which task to grade (1, 2, 3, or all) |
| Bonus | `-Bonus`, `-b`, `-bonus` | `-b`, `-bonus` | Grades bonus task |
| No dump | `-NoDump`, `-n` | `--no-dump`, `-n` | Does not output results to /dump |

Every run also dumps the raw output of each graded test case to
`<task>/dump/<testcase>.txt`, so you can check it and compare it against
`testcases/<testcase>/output.txt`.

### Creating test cases

You can add your own testcases by following the format of the testcases in the folders.

- `testcase[number]` for normal testcases
- `testcaseB[number]` for bonus testcases

You will need to include your own `input.txt` and the expected `output.txt` (and the `state.txt` if you use the state import function in Task 3).

Once they are added, the test_run scripts should automatically pick them up as valid testcases and run them for you.

If there are any bugs with the tester please inform me at once :P

## Grading

>It is completely fine to not be able to complete this homework, as it is only here to help  

There will be 3 main portions of the grading:

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
(Follow the format in the test cases folder)

If the output came out as wrong during grading due to some trivial error (such as floating point errors possible in Task 1), depending on the severity of deviation, points may or may not be deducted.  
(For example, if the answer is `3.5` but for some reason, your program outputs as `3.4999999999999999999...` due to some floating-point error, we will not deduct points in this case.)
