[Back to Main](README.md) | [Previous Page](02-where-to-write-code.md)

# Hello World!

> Everyone's first C Program!

Let us write the most basic program to illustrate the language that is C, a "Hello World!" program that outputs simply: `Hello world!`.

Create a file named `main.c` and you can begin writing in it.

```c
//main.c

#include <stdio.h>

int main() {
    // This is a comment.
  
    /* 
      This is a multi-lined comment.
      These gray lines are ignored by the program.
      It is only for the developer, to remember something,
      or to tell their peers how the program works.
    */
  
    printf("Hello, World!\n"); // \n means write a newline
    return 0;
  
    // Console:
    // Hello, World!
    // 
}
```

The program can be dissected as follows:

* `#include <stdio.h>` tells the program we are using features within a **library** named `stdio.h`. We need this line to get the function `printf()`, as it is defined within the `stdio.h` library.
* `int main() {}` This is a **function definition**. It is the entry point of the program, that means, the program will start right inside it. **`int main()` must exist in every C program.** We write the main code inside this function.
* You can use `//` to make a one line comment, anything to the right of it will be ignored by the compiler. For comments with more than one line, compiler will ignore anything from `/*` to `*/`.
* `printf("Hello, World!\n");` This is a **function call**, like using a mathematics function, we pass parameters within the parenthesis. The function `printf` can output whatever parameter we put into the **console**, so we want it to write out `Hello, World!`. **`'\n'` represents a "newline" character**, since we cannot actually store an 'enter' key in a single line.
* `return 0;` When we run a C program, it ends by giving us an **exit code** to indicate whether or not there is a problem. By returning `0`, we indicate that the program ended successfully.

The `main()` function is a specific case, in that you can only omit the `return` statement. The compiler will automatically add them `return 0;` for you. However, for other functions, you must return something, unless the return type is `void`.

Just in case that your workspace has no working run button (either VSCode on your machine or you are using Github Codespace). You can use the terminal and copy the following (we will explain it in detail later):

```
gcc -o a.exe main.c
./a.exe
```

## Common Fails of Printing Hello World in C

Some things to take note of:

* C is case-sensitive. Upper-case letters and lower-case letters are entirely different!

  ![](https://i.imgur.com/Hk5Z699.png)
* End each statement with a `;` like how you would end a sentence with a full stop in English.

  ![](https://i.imgur.com/0fPkaWg.png)
* Close as many `{` or `(` or `"` as there are with `}` or `)` or `"` and do not mess up the order. It is just like maths.

  ![](https://i.imgur.com/xfCwlsq.png)


## What's Next?

Otherwise, now you can already write your first program in C. There are more to this language other than printing `Hello World!`, of course. We will cover them right after.

## Self Test (For Concept Check)
Q1. Find problems in the following `Hello World` program:
```c
#include "stdio.h"

void Main(){
  printf("Hello World!\n")
```
<details>
  <summary>
    Ans
  </summary>

  This is the corrected version of the code:
  ```c
  #include <stdio.h> //should be <stdio.h>
  
  int main(){ //should be int main()
    printf("Hello World!\n"); //end with semicolon
  } //close the bracket
  ```
  
</details>

[Next Page](04-variable-io.md)
