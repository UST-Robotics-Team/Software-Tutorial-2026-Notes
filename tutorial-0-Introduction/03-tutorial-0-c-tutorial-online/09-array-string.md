[Back to Main](README.md)

# Array and String

> Array are just many boxes put together in a line.

> There are some topics that are less important, they will be marked with `*` in the title. But we may need a slight understanding of it for the next parts.

## Arrays

Variables are nice, but what if we need to store a hundred integers?

```c
int var_0;
int var_1;
int var_2;
int var_3;
.
.
.
int var_99;
```

Although this method is possible, it is not efficient or feasible. Hence, we use **Array**.

An array is another type of variable. It is a container for multiple values of the same type. Arrays carry type information and can only carry one type of value in one array. Think of arrays as cabinets, and each value belongs in one drawer in a cabinet.

An array must have a **constant length**, specified either at declaration or interpreted at initialization.

Refer to [cppreference](https://en.cppreference.com/c/language/array) for more details.

### Array Declaration

The following is the syntax for declaration 
```
<element_type> <array_name>[<size (optional for the first number)>];
```

The `[]` (square brackets) specifies an array.

The following is an example of declaring a float array with length 10;

```c
float numbers[10];
```

### Array Initialization

An array can be initialized alongside a declaration with values, by using the initializer expression, like so:

```c
int natural_numbers[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; //remaining spaces are filled with 0s
```

If you initialize using the initializer expression, you are not required to specify the array length. It will count the number of elements and set the length as that (the minimum size possible)

```c
int natural_numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; //will be an array of size 10 instead
```

Uninitialized arrays in functions store **garbage values** as initial values. If you want to initialize them as all `0`s do the following:

```c
int garbage[20]; //everything inside will be garbage value
int blank[20] = {}; //everything will be 0 filled
```

**Arrays cannot be re-assigned**, so you cannot use the initializer expression after the declaration statement, nor assign them to another array variable.

### Array Access

Array items do not have a name we can call, but they are arranged in an orderly fashion within an array. We can access items using an **index**. 

We count from `0` in programming, so we can call, e.g. the 0th item in array x. The index can be a variable containing an integer, or simply an integer literal. The following is the syntax of array access: 

```
<array_name>[<index>]
```

For example:

```c
int numbers[10]; //numbers = {3, <garbage>, <garbage>, ...}
numbers[0] = 3; //accessing to modify the value inside
int y = numbers[0]; //accessing to get the value; y is 3 now
```

> Please be aware about **Boundary Issue**: **Accessing an array out of bounds** (negative or any number $\geq \textsf{size}$ ) is **undefined behavior**, it may or may not generate error when accessed. ([Read more](https://www.geeksforgeeks.org/accessing-array-bounds-ccpp/)). Accessing outside of program memory will produce a "SIGSEGV Signal Segmentation Fault" runtime error.

Arrays are usually used for loops, to iterate over the length of the array for data manipulation.

This example populates the array with natural numbers:

```c
int n[100];

for (int i = 0; i < 100; i++) {
    n[i] = i+1;
}

//now n will be {1, 2, 3, 4, ..., 99, 100};
```

Another example, this program will find the mean (average value) of the values in an array.

```c
int data[10] = {1, 4, 5, 6, 3, 2, 4, 3, 2, 7};

int sum = 0;
for(int i=0; i<10; i++){
    sum += data[i];
}

double mean = sum/10.0; //please refer to the section about casting
printf("%.3f", mean); //prints 3.700, note %.3f is used instead of %d
```

### Multidimensional Arrays

Arrays can have multiple dimensions. The arrays we have explored above are called 1D arrays. 

To declare arrays with additional dimensions, just do as follows:

```c
int map[5][10];
```

The above declares a $5 \times 10$ array.

To access a cell, it can be done as:

```
map[<index>][<index>]
```

Alternatively, you can consider multidimensional arrays as matrices. For example:

```c
int map[4][3];
map[0][0] = 1;
map[0][1] = 5;
map[0][2] = 2;
map[1][0] = 3;
map[1][1] = 4;
map[1][2] = 9;
map[2][0] = 7;
map[2][1] = 6;
map[2][2] = 4;
map[3][0] = 5;
map[3][1] = 5;
map[3][2] = 3;
```

You can also initialize it as the following:
```c
int map[4][3] = {
    {1, 5, 2},
    {3, 4, 9},
    {7, 6, 4},
    {5, 5, 3}
};
```

`map[4][3]` can be written in the matrix as below:
```math
\textsf{map} = \begin{bmatrix}  1& 5 & 2 \\ 3 & 4 & 9 \\ 7 & 6 & 4 \\ 5 & 5 & 3\end{bmatrix}
```

When accessing the variable, think about like this:

Let's assume that we want to access `map[2][1]`, we see it like this:
```
{
    {1, 5, 2}, //0
    {3, 4, 9}, //1
    {7, 6, 4}, //2
    {5, 5, 3}  //3
}
```
We want to take the item at index `2`:
```
{7, 6, 4}
```
And then we proceed to take the item at index `1`, which is `6`

## Optional Exercise

> We covered the materials needed for your **Optional Exercise 1** (used to be a classwork). You can access it [here](Additional-Exercise/classwork-1-matrix-addition.md). We suggest that you can try it out on your own pace.

## String (Character Array)

> `"Hello World\n"` re-explored.

### Character Array

You may not realize, but we actually have used array in our `Hello World` program.

In C, there is no built-in `string` type. As an alternative, we use **character arrays** to represent a string:

```c
char name[] = "Danny";
```

Although the length of `Danny` is `5`, there is an invisible character `'\0'` at the end, which C uses to indicate the end of the character array. Hence, the size of `name` array is actually `6`.

Basically this is the same as:

```c
char name[] = {'D', 'a', 'n', 'n', 'y', '\0'}; //size is determined by compiler, which is the minimum possible: 6
```

Note that in the case, you need to explicitly write `\0`

This `\0` (null character) is needed for C to be able to print it properly (The print will stop upon finding this `\0` character).

```c
//this is a slightly more tedious way of printing "Danny"
int i = 0;
char name[] = "Danny";
while (name[i] != '\0') {
    // remember that i++ is post-increment,
    // that means it returns the original value of i,
    // before adding 1 to i
    printf("%c", name[i++]);
}

printf("\n");
```

### `printf` and `scanf` for Strings

There is a placeholder in format string for strings: `%s`

To receive the input of a string, you can use:

```c
char input[100]; //make a sufficiently big array
scanf("%s", input); //no need for the &, an array actually stores the address (more about it in advanced materials)
```
This method will take all characters until it detects a whitespace or newline. For example if you input `This is a loong string`, the array `input` will only contain `This`. It also automatically store your input with `\0` at the end.


```c
char hello[] = "Hello World!";
printf("My first program in C prints %s :)", hello);
```

It will print `My first program in C prints Hello World! :)` (null character is removed upon insertion to the format string)

## Optional Exercise

> We covered the materials needed for your **Optional Exercise 2** (used to be a classwork). You can access it [here](Additional-Exercise/classwork-2-first-word.md). Let's do it before moving on again.

## The `<string.h>` Library*

There is also a library that can help you in working with strings. You can use `#include <string.h>` to add it to your workspace.

### `strlen()`: Counts how long a string is (excluding null char)
```c
char name[] = "Danny";
int len = strlen(name);
printf("len: %d\n", len); //prints 5

//Under the hood, it works by counting the amount of characters before \0
char hello[] = {'H', 'e', 'l', 'l', 'o', '\0', 'w', 'o', 'r', 'l', 'd'};
len = strlen(hello);
printf("len: %d\n", len); //prints 5
printf(hello); //prints "Hello" only
```

### `strcpy()`: Copies all the contents of the second tring to the first one

```c
char from[] = "Danny";
char to[6]; //note that it must have sufficient size; more is fine but less may lead to errors

strcpy(to, from);
printf(to); //prints Danny

strcpy(to, "Robot"); //from can be literal string
printf(to); //prints Robot
```

### `strcmp()`: Compares the string. If they have the same length and content, it will evaluate to `0`. Otherwise, any non-zero number.

```c
char str1[] = "Hello";
char str2[] = "Hello";

int cmp = strcmp(str1, str2); 
printf("cmp: %d\n", cmp); //prints 0

strcpy(str2, "Robot"); //make str2 = Robot (use strcpy instead of assignment)
cmp = strcmp(str1, str2);
printf("cmp: %d\n", cmp); //prints -10 (non-zero)

char str3[6] = "Hello "; //notice the whitespace
cmp = strcmp(str1, str3);
printf("cmp: %d\n", cmp); //prints -32 (non-zero)
```

## Self-Test

Q1. Determine the output of the following program

```c
#include <stdio.h>

int main(){
    int A[] = {1,2,7,4,9,6,10,8,3,5};
    int i=0;
    while(A[i]!=10){
        printf("%d ", A[i]);
        i = A[i];
    }
}
```

<details>

```
1 2 7 8 3 4 9 5 6 
```

<summary>Ans</summary>

</details>

Q2. Imagine that you are shopping online for some robotics equipments. You list out all the price of the things you want to buy in an array. However, you do not want to buy the equipment with the lowest price as it might have bad quality. You would like to find the price of the second cheapest equipment.

For simplicity you may assume that no equipments will have the same price and prices are always in integers. You will not check for more than $50$ equipment prices.

The input format will be as follow:
```
N
<prices of those N equipments>
```

For example, given the input:
```
8
109 105 104 103 112 113 114 110
```
Then the code will output `104`

Edit the following code to do exactly that:
```c
#include <stdio.h>

int main(){
    
    int prices[50] = {};
    int N; scanf("%d", &N);
    for(int i=0; i<N; i++){
         scanf("%d", &prices[i]);
    }
    
    int minimum_price = prices[0]; //set temporarily to prices[0]
    int second_cheapest = prices[0];

    //Hint: assume that you knoe the minimum price, what can you do to get the second minimum price. 
    
    printf("%d", second_cheapest);
}
```

<details>
There are other more efficient methods, but this is one possible way:

```c
#include <stdio.h>

int main(){
    
    int prices[50] = {};
    int N; scanf("%d", &N);
    for(int i=0; i<N; i++){
         scanf("%d", &prices[i]);
    }
    
    int minimum_price = prices[0]; //set temporarily to prices[0]
    int second_cheapest = prices[0];

    //Hint: assume that you knoe the minimum price, what can you do to get the second minimum price. 
    for(int i=0; i<N; i++){
        if(prices[i] < minimum_price){
            minimum_price = prices[i];
        }
    }
    
    for(int i=0; i<N; i++){
        if(prices[i] < second_cheapest && prices[i]!= minimum_price){
            second_cheapest = prices[i];
        }
    }
    
    printf("%d", second_cheapest);
}
```
<summary>Ans</summary>

</details>

Q3. Find the mode (the elements that appears the most) of the array `A` given the following skeletion code. We guarantee that $0 \leq A_i<1000$ and $A_i$ are integers. If there are more than one modes, print the largest one.

```c
#include <stdio.h>

int main(){
    int A[] = {31, 31, 42, 31, 25, 33, 43, 42, 42, 42, 33, 25, 31, 31, 42, 42, 42, 33, 25, 41};
    int size = 20;
    int freq[1000] = {}; //create an array to how many times (frequency) the number i appears inside A[i]. e.g. 25 appears 3 times then A[25]=3

    //Your code here 
}
```
It is expected to print `42` because $42$ appears the most in `A`

Make sure that if `A` is given as the following instead:
```c
int A[10] = {31, 31, 31, 45, 42, 45, 45, 67, 68, 32};
int size = 10;
```
It will print `45`

<details>

```c
#include <stdio.h>

int main(){
    int A[] = {31, 31, 42, 31, 25, 33, 43, 42, 42, 42, 33, 25, 31, 31, 42, 42, 42, 33, 25, 41};
    int size = 20;
    int freq[1000] = {}; 
    
    for(int i=0; i<size; i++){
        freq[A[i]]+=1;
    }
    
    int mode = 0;
    for(int i=0; i<1000; i++){
        if(freq[i]>=freq[mode]){
            mode = i;
        }
    }
    
    printf("%d", mode);
}
```

<summary>Ans</summary>

</details>

Q4. Determinant of a $3 \times 3$ matrix

Given a matrix $M$:

```math
\begin{bmatrix} a & b & c \\ d & e & f \\ g & h & i\end{bmatrix}
```

Then the determinant $\det M = aei + bfg + cdh - ceg - afh - bdi$

By accessing the appropriate member of an array, evaluate the determinant of the following matrix:

```c
#include <stdio.h>

int main(){
    int M[3][3] = {
        {2, 3, 4},
        {2, 7, 9},
        {0, 4, 8}
    };

    //Your code here
}
```

<details>

```c
#include <stdio.h>

int main(){
    int M[3][3] = {
        {2, 3, 4},
        {2, 7, 9},
        {0, 4, 8}
    };

    printf("%d", M[0][0]*M[1][1]*M[2][2] + M[0][1]*M[1][2]*M[2][0] + M[0][2]*M[1][0]*M[2][1] - M[2][0]*M[1][1]*M[0][2] - M[2][1]*M[1][2]*M[0][0] - M[2][2]*M[1][0]*M[0][1]);
}
```

<summary>Ans</summary>

</details>

Q5. Palindrome String Checker

A palindrome string is a string that reads the same if you read it from the left to the right and from the right to the left, for example:

`uwu`, `racecar`, `aibohphobia`, `otto`, and `a` are palindrome strings

`uw`, `tracecar`, and `robotics` are not palindrome strings

Write a program to read a string from `scanf` and check if it is a palindrome string. If it is, reprint the string, otherwise, do nothing. For extra challenge, do not use `strlen`. The length of the string including `\0` is guaranteed to be less than $1000$.

*Hint: you may need to only iterate through half the array. Also remember to consider edge cases: is the letter at the center always shared?*

<details>

```c
#include <stdio.h>

int main(){
    char A[1000];
    scanf("%s", A);
    
    //check length
    int length = 0;
    while(1){
        if(A[length]!='\0'){
            length+=1;
        }else{
            break;
        }
    }
    
    int is_palindrome = 1;
    for(int i=0; i<length/2; i++){
        if(A[i]!=A[length-i-1]){
            is_palindrome = 0;    
        }
    }
    if(is_palindrome){
        printf("%s", A);
    }
    
}
```

<summary>Ans</summary>

</details>

[Continue to The Next Page](10-functions.md)
