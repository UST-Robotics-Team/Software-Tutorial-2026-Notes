[Back to Main](README.md) | [Previous Page](12-multi-file-programming.md)


# Recursion

> a function calling itself, calling itself, calling itself, ...

> This topic is slightly less important in our actual work in robot programming. However, do take the time to learn it as we may include a part of it as your homework (to test your ability to understand programming concepts).

Now, let's say that you have a function `int f()`, can you do the following?

```c
void f(){
    print("Spam\n");
    f();
}
```
Yes, in fact, you can! The code will print `Spam` indefinitely. This is called a recursive function: a function that calls itself to repeat something.

The example above may seem quite useless, consider the following program instead:


Usually, to compute factorial $n!$, the product of all numbers in $[1, n]$ (For example: $6! = 6 \cdot 5 \cdot 4 \cdot 3 \cdot 2 \cdot 1 =720$). Usually we will use `for` loop to compute it. However, if you think about it:

```math
n! = \left\{ \begin{array}{ll} 1  & n = 1 ~~\textsf{(base case)}\\ n \cdot (n-1)! & n \gt 1 ~~\textsf{(recursive case)}  \end{array} \right.
```

Let's say that we have $6!$:

```math
6! = 6 \cdot 5! = 6 \cdot 5 \cdot 4! = 6 \cdot 5 \cdot 4 \cdot 3! = 6\cdot 5 \cdot 4 \cdot 3 \cdot 2! = 6 \cdot 5 \cdot 4 \cdot 3 \cdot 2 \cdot 1! = 6 \cdot 5 \cdot 4 \cdot 3 \cdot 2 \cdot 1 = 720
```
</br>

```c
int factorial(int x){
    if(x==0) {return 1;} //base case
    return x * factorial(x-1); //recursive case
}
```



To make a recursive function, usually we will think about how the state the value of the function given an argument in terms of the value of the function given another argument (recursive case). Moreover, to guarantee that the function will stop calling itself, you need to implement a base case for the function.

Additionally you may also consider the following example (you can call more than one instance of the function):


```math
\textsf{fibonacci}(n) = \left\{ \begin{array}{ll} 0 & n = 0 ~~\textsf{(base case)} \\ 1  & n = 1 ~~\textsf{(base case)}\\ \textsf{fibonacci}(n-1) + \textsf{fibonacci}(n-2) & n \gt 1 ~~\textsf{(recursive case)}  \end{array} \right.
```

</br>

```c
int fibonacci(int n) {
    if (n <= 1) {
        return n;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}
```

> By using recursion, it may increase time complexity and space complexity. However, there is a more efficient way to compute recursive functions in some cases using something called *dynamic programming*.


## Self-Test

Q1. Mountain

Determine the output of the following program:
```c
#include <stdio.h>

void mountain(int x){
    if(x==0){
        return;
    }
    mountain(x-1);
    for(int i=0; i<x; i++){
        printf("*");
    }
    printf("\n");
    mountain(x-1);
}

int main(){
    mountain(3);
}
```

<details>

<summary>Ans</summary>

```
*
**
*
***
*
**
*
```

</details>

Q2. Write a program to evaluate the value of an integer $a$ given the power of another integer $b$, i.e. $a^b$. You must use recursion to do this problem.

~~Iterative solution will receive zero marks, COMP2011 flashback :)~~

Hint: You may consider the following

if $b$ is even, then $b = 2m$ for some integer $m$. Hence $a^b = a^{2m} = a^m \cdot a^m$

However, if $b$ is odd, then $b = 2m + 1$ for some integer $m$. Hence $a^b = a^{2m+1} = a^m \cdot a^m \cdot a$

Note that the value of $a^b$ depends on $a^m$. Figure out what exactly $m$ is.

<details>

```c
#include <stdio.h>

int power(int a, int b){
    if(b==0){
        return 1;
    }
    if(b==1){
        return a;
    }
    int x = power(a, b/2);
    if(b%2==0){
        return x*x;
    }else{
        return x*x*a;
    }
}

int main(){
    //For testing, I would like to compute:
    printf("%d", power(2, 17));
    //prints 131072, which is correct
}
```

<summary>Ans</summary>

</details>


Q3. Determine the output of the following program

*Hint: Draw the matrix on a paper, on the side, draw the branches of the function call*
```c
#include <stdio.h>

char A[4][5] = {
    {'.', '.', '.', '*', '.'},
    {'.', '*', '*', '*', '.'},
    {'.', '.', '*', '*', '.'},
    {'.', '.', '*', '.', '.'}
};

void touch(int x, int y){
    if(x<0 || y<0 || x>=4 || y>=5){
        return;
    }
    if(A[x][y]=='.'){
        return;
    }
    A[x][y]='.';
    printf("%d %d\n", x, y);
    touch(x-1, y);
    touch(x+1, y);
    touch(x, y-1);
    touch(x, y+1);
}

int main(){
    touch(1, 2);
}
```

<details>

```
1 2
2 2
3 2
2 3
1 3
0 3
1 1
```

<summary>Ans</summary>

</details>

---

That's all for Tutorial 1, Goodluck with your Homeworks! :)

[Back to Main](README.md#homeworks)
