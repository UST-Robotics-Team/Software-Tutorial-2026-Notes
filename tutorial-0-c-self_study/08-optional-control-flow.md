[Back to Main](README.md) | [Previous Page](07-control-flow.md)

## Switch Statements

Switch statements allow a variable to be tested for each case. It contains **jump statements** and **labels**.

```c
switch (<expression>) { //some integral (non-floating point type)
    case <integer_expression_1>:  //if expression is equal to integer_expression_1, jump here
        <statement_1>
    case <integer_expression_2>: //if expression is equal to integer_expression_2, jump here
        <statement_2>
    ...
    default: //if expression is none of the above, jump here (optional)
        <statement_default>
}
```
Each case is compared against the expression in the switch parenthesis, if a match is found, the program **jumps** to that case and starts executing line by line, and only exits when encountering `break;` or when it reaches the bottom.

Basically, switch-statements are just if-statements when all their conditions are `x == case`.

Note that `integer_expression`s must be a constant, not a variable.

For example:

```c
int day = 7; //let 1 be Monday, 2 be Tuesday, ...

switch (day) {//value to compare against with the cases
    case 6: //jump here if day==6
    case 7: //jump here if day==7
        printf("There are no lectures today\n");
        break; //exit from the switch statemtent
    case 1: //jump here if day==1
    case 2: //jump here if day==2
    case 3: //jump here if day==3
        printf("We have robotics tutorial today\n");
    case 4: //jump here if day==4
    case 5: //jump here if day==5
        printf("We have lectures today\n");
        break;
    default: //jump here if matches none of the cases, optional
        printf("Invalid day\n");
}
```

If `day=7` then the program will output:
```
There are no lectures today
```
If `day=6` then the program will also output:
```
There are no lectures today
```
However, note that if `day=1` then the program will output:
```
We have robotics tutorial today
We have lectures today
```
Pay attention to where `break;`s are.

If `day=5` then the program will output:
```
We have lectures today
```
If `day=42` then the program will output:
```
Invalid day
```

## Ternary Operator

The **ternary operator** is also known as the **conditional operator**. It is similar to `if...else...`, but is faster to type and is considered a shortcut for `if`. 

Syntax:
```
<boolean_expression> ? <value_true> : <value_false>
```

If `boolean_expression` is non-zero, then the ternary operator evaluates into `value_true`, otherwise, it evaluates into `value_false`.

For example:
```c
printf("%d", 5 != 6 ? 42 : 56); //prints 56 because boolean_expression is zero
printf("%c", 42 > 41 ? 'A' : 'B'); //prints A because boolean_expression is non-zero

//Note that you can also nest it:
printf("%c", (42 ? 0 : 1) ? 'A' : 'B'); //prints B
```

### `do while` Loop
A variation of `while` loop, but instead of checking the expression first. It will run the statement first.

Syntax:
```c
do {
    <statement> 
} while (<expression>);
```

For example:
```c
int x = 0;
do{
    printf("x: %d\n", x);
    x++;
}while(x<5);
```

Let's analyze the trace:
```c
<statement>: printf("x: %d\n", x); x++; //Prints x: 0, then adds 1 to x, x=1
<expression>: x < 5 //1 < 5, true (non-zero)
<statement>: printf("x: %d\n", x); x++; //Prints x: 1, then adds 1 to x, x=2
<expression>: x < 5 //2 < 5, true (non-zero)
<statement>: printf("x: %d\n", x); x++; //Prints x: 2, then adds 1 to x, x=3
<expression>: x < 5 //3 < 5, true (non-zero)
<statement>: printf("x: %d\n", x); x++; //Prints x: 3, then adds 1 to x, x=4
<expression>: x < 5 //4 < 5, true (non-zero)
<statement>: printf("x: %d\n", x); x++; //Prints x: 4, then adds 1 to x, x=5
<expression>: x < 5 //5 < 5, false (zero)
```
Hence the output is:
```
x: 0
x: 1
x: 2
x: 3
x: 4
```

The difference is that the `statement` will be run at least once.

```c
do{
    printf("Hehe");
} while (false);
```
will output `Hehe`

## Scopes
Here we will explain about when you can declare a variable with the same name and when you cannot.

In the following case, you can declare two variables with the same name `i`.

This is because they are in a different scope. In general, a new scope is created when you write code inside the body of `if`, `for`, `while`, and `{}`. The body inside will have a different scope.

If there are more than one variables with the same name in the same scope, then it will cause a compiler error (both of them are at the same level, which one should be used?)

```c
#include <stdio>

int i=42; //the global scope
int j=42;
int k=42;

int main(){ //the main function scope
    int i=1; 
    int j=1;
    for(int i=0; i<3; i++){ //the for loop scope
    }
}
```
Hence, you can think of it as:
```
global scope: {
    i = 42;
    j = 42;
    k = 42;
    main function scope : {
        i = 1;
        j = 1;
        for loop scope : {
            i = 0;
        }
    }
}
```

When given a name, compile will try to find the variable with that name in the *innermost* scope.

Hence if we have:
```c
#include <stdio>

int i=42; //the global scope
int j=42;
int k=42;

int main(){ //the main function scope
    int i=1; 
    int j=1;
    for(int i=0; i<3; i++){ //the for loop scope
        printf("for loop: %d %d %d", i, j, k); 
        //i is defined in the for loop scope, it will follow the iterator value
        //j is not defined in the for loop scope, refer to the one in the main function scope (innermost)
        //k is not defined in both for loop scope nor the main function scope, use the value in the global scope
    }
    printf("main(): %d %d", j, k);
    //j is defined in the main function scope
    //k is not defined in the main function scope, but defined in the global scope
}
```

Hence, the output is:
```
for loop: 0 1 42
for loop: 1 1 42
for loop: 2 1 42
main(): 1 42
```

Note that after the program goes out of a scope, all static variables will be removed (e.g. the `i` in the for loop will be deleted when the program exits the loop). 

[Back to Main](README.md)