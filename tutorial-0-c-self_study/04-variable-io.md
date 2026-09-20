[Back to Main](README.md) | [Previous Page](03-hello-world.md)

# Variables and Input-Output

> How to Make Computers Store Data and Print Things

Now, instead of the `Hello World` program before, consider the following:

```c
#include <stdio.h>

int main(){
    int x; //Declare a variable x
    x = 1; //Assign the value 1 to x
    printf("x: %d", x); //Format and print x
    int y; //Declare a variable y
    scanf("%d", &y); //Read a value and put the value into y
    x = x+2; //Add 2 to the variable x
    printf("x+y: %d", x+y); //Prints x+y
}
```

This may seem like a lot of new stuff at first. It may even be overwhelming if you have not known how to program before. It is fine, we will go through all the concepts here.

## Variables and Data Types

> Boxes to Store Value

In programming, variables are 'boxes' that you can use to store information. To **declare** a variable, in C, you use the following syntax.

```c
<data-type> <variable-name>;
```
For example (we will explain what is `int` soon):
```c
int x;
```
Data types explains what is being stored in a variable (is it an integer, numbers with decimal points, a word) etc.

> Note: In languages like python, you do not need to explicitly state a data type for a variable. However, you need to do it in C. This makes C fast.

We will first introduce you to some commonly used primitive data types:

<table>
<thead>
<tr>
    <th width="212" align="center">Type</th>
    <th width="276" align="center">Description</th>
    <th align="center">Example Literal</th>
</tr>
</thead>
<tbody>
    <tr>
        <td align="center"><code>char</code></td>
        <td align="center">8-bit integer* for storing an ASCII character</td>
        <td align="center"><code>'a'</code></td>
        </tr><tr>
        <td align="center"><code>int</code></td>
        <td align="center">16-bit/32-bit signed integer***</td>
        <td align="center"><code>1</code></td>
        </tr><tr>
        <td align="center"><code>float</code></td>
        <td align="center">32-bit, single-precision floating point value (i.e. dotted number)</td>
        <td align="center"><code>3.012f</code></td>
        </tr><tr>
        <td align="center"><code>double</code></td>
        <td align="center">64-bit, double-precision floating point value (i.e. a longer dotted number)</td>
        <td align="center"><code>5.012345</code></td>
    </tr>
</tbody>
</table>

* One bit is one `0` or `1` stored in the memory of the computer
* \*Whether `char` is signed or unsigned is machine-dependent.
* \*\*ASCII stands for American Standard Code for Information Interchange. Each number is mapped to a character: check the full table [here](https://www.ascii-code.com/).
* \*\*\*Size is compiler-dependent and machine-dependent.

Please pay attention to the syntax of the literal given on the last column.

In C, after declaring a variable, that variable will commonly contain garbage value (some random 0s and 1s that the computer is forced to read as the data type you declare). Hence you need to **assign** a value to it. To do so, use the following syntax.

```
<variable-name> = <literal-or-variables-of-that-type>;
```
So, for example
```c
int x;
x = 3;

int y;
x = y;

char y;
y = 'A';
```

Note that you need to **declare** a variable before you **assign** a value to it.

If you want to declare and assign a value immediately to a variable, you may also use the following syntax:
```
<data-type> <variable-name> = <literal-or-variables-of-that-type>;
```
For example:

```c
int x = 7;
```

To see what is inside a variable, you can print it as follow (we will explain in detail how this line works later):

> We covered the materials needed for your **Homework 1**! You can access it [here](homeworks/hw01-swap-variable.md). Give it a try, good luck!

## Input-Output: `printf` and `scanf`

> Boxes in the program is quite useless if you cannot see what is inside

However, so far, we only tell you how to make variables. To communicate, programs in C commonly uses the standard input and output. That is why we include:

```c
#include <stdio.h> //STanDard Input Output .h
```

> From here on, in this page, we will consider that the code blocks are written inside an `int main()` function.


### `printf`

To use `printf` you can use the following syntax:

```
printf("formatted_string", <arguments-list>);
```

This might get confusing at first, let's consider the simple case of the `Hello World` printing again:

To simply print a string (a collection of characters inside double quotes: e.g. `"Hello World"`), you can omit the `<argument-list>` part:

```c
printf("Hello World");
```
However, if you would like to print an instance of a data type such as `int`, then you need some way to convert it into string. Here is how format string can be useful.

In format string, you can put `%<some-characters>` to denote where and how you would like to print the instance of the data type. A simple example: `%d` means print the as an integer (the computer needs to convert the 0s and 1s stored to human-readable number).

```c
printf("%d", 7);
```

Will print `7` to the standard output. Note that this also works for variables.

```c
int x = 7;
printf("%d", x)
```
Note that the `%<some-characters>` is a works like a 'placeholder' to denote where data type is placed. So the following code:
```c
int x = 7;
printf("Print x at this location -> [%d]", x);
```
Will print: `Print x at this location -> [7]`

There are actually more placeholders and not only `%d`, please refer to the following link and the guide on cppreference.

> Because the character `%` is used for this purpose in `printf` to print an actual character `%` you need to write `%%` in the string.

| Specifier |          Explanation          |
| :-------: | :----------------------------: |
|   `%c`   |       Writes a character       |
|   `%d`   |       Writes an integer       |
|   `%x`   |  Writes an integer in base 16 (hex)  |
|   `%f`   | Writes a floating point number |
|   `%.3f` | Writes a floating point number up to 3 decimal points|

For more details: [https://en.cppreference.com/w/c/io/fprintf](https://en.cppreference.com/w/c/io/fprintf)

Note that it is `<argument-list>`. You may put more than one datatypes to be printed at once.

> However, note that the amount of placeholders in the format string must equal the amount of data types in the argument list.

```c
printf("Today is: %d%d/%c%c%c/%d%d", 0, 1, 'S', 'E', 'P', 2, 4);
```

This will output `Today is: 01/SEP/24`

### Special Character `\n` (Newline)

If you attempt to use `printf` as follow in C:
```c
printf("Hello");
printf("Hi");
```
Output:
```
HelloHi
```
To separate them into different lines, you will need to write an extra `\n` character at the end of Hello to press 'enter' before printing `Hi`
```c
printf("Hello");
printf("Hi");
```
Output:
```
Hello
Hi
```

> We covered the materials needed for your **Homework 2**! You can access it [here](homeworks/hw02-introduce-yourself.md). Give it a try, good luck! 


### `scanf`
Similarly, there is also a function to receive inputs from users. You will need to use format string again here.

To receive an input from user, you need to state how the input will look like and place the placeholder (`%<some-characters>`) where the program should expect it to be at. For example:

```c
int x; float y; char z;
scanf("%d %f %c", &x, &y, &z); //We will explain the & later
printf("%d, %f, %c", x, y, z);
```
When receiving the input `7 4.2 A` will store `7` to `x`, `4.2` to `y` and `A` to `z`.

However, commonly you might only want to receive one character. You can simply do the following:
```c
int x;
scanf("%d", &x);
```
Note that the first program can also be implemented as the following. In general, the program will ignore all whitespaces and newlines except for the case of `%c`:

```c
int x; float y; char z;
scanf("%d", &x);
scanf("%f", &y);
scanf(" %c", &z); //the leading space is necessary
printf("%d, %d, %c", x, y, z);
```
(Note that `%c` will not ignore the space given by the user before the character `A` in `7 4.2 A`)

> The `&` actually means *the address of*. Unlike printing, to store the value of the input, the program needs to know where is address of the 'box'. We will cover more about `&` in the advanced section of the notes. It will not be tested in our homeworks. 

## Self Test (For Concept Check)

Q1. Transpose a compound $3 \times 3$ matrix

You will be given an input with the following format:
```
L N N
N L N 
N N L
```
`N` represents numbers, while `L` represents letters. i.e. the diagonal elements are letters, while the others are numbers. You need to print the transpose of the matrix. For example, if you are given:

```
a 0 1
2 b 3
4 5 c
```
You should print the following:
```
a 2 4
0 b 5
1 3 c
```
The first row will become the first column, the second row ill become the second column, and it is also the case for the third row.

*Hint: note the importance of `\n`*

<details>

```c
#include <stdio.h>

int main(){
    char a; int b; int c;
    int d; char e; int f;
    int g; int h; char i;

    scanf("%c %d %d\n%d %c %d\n%d %d %c", &a, &b, &c, &d, &e, &f, &g, &h, &i);
    printf("%c %d %d\n%d %c %d\n%d %d %c", a, d, g, b, e, h, c, f, i);
}
```

<summary> Ans </summary>
</details>

Q2. Reformatting 

Starting from scratch, write a program such that, when given the input: 
```
Instructor ID: 21387312
Course code: PHYS2711
Rating: 4/5
```
It will output:
```
PHYS2711 (4/5) [2138-7312]
```
And when it is given the input:
```
Instructor ID: 03256721
Course code: COMP4895
Rating: 3/5
```
It will output:
```
COMP4895 (3/5) [0325-6721]
```
You can only include the library `stdio.h`. We guarantee that Course ID contains 8 digits (may start with 0). Course code starts with 4 letters followed by 4 digits (will not start with 0). and rating is an integer and always out of 5.

<details>

```c
#include <stdio.h>

int main(){

    char iid1; char iid2; char iid3; char iid4;
    char iid5; char iid6; char iid7; char iid8;
    //store instructor id, need to use char because it may start with 0

    char cc1; char cc2; char cc3; char cc4;
    //store course code letters

    int cc;
    //store course code number

    int rating;
    //rating

    /* please remember the & in scanf, but do not use it
    in printf */

    scanf("Instructor ID: %c%c%c%c%c%c%c%c\n", &iid1, &iid2, &iid3, &iid4, &iid5, &iid6, &iid7, &iid8);

    scanf("Course code: %c%c%c%c%d\n", &cc1, &cc2, &cc3, &cc4, &cc);

    scanf("Rating: %d/5", &rating);

    printf("%c%c%c%c%d (%d/5) [%c%c%c%c-%c%c%c%c]",
        cc1, cc2, cc3, cc4, cc,
        rating,
        iid1, iid2, iid3, iid4, iid5, iid6, iid7, iid8
    );


}

```

<summary>Ans</summary>
</details>

[Continue to The Next Page](05-operators.md)
