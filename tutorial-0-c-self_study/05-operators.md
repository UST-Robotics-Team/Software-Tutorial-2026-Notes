[Back to Main](README.md) | [Previous Page](04-variable-io.md)

# Operators
> Everyone knows math, right?

After understanding how to make variables, what can we do with them other than storing variables? Operate them!

Operators help us to perform the most fundamental mathematical or logical operations on variables.

**Operators** can accept different numbers of **operands**. Their names are as follows:

* **Unary** Operators: (operators that work with only 1 "variable")

  Takes a single operand `+x` `-x` `&x` `*x` `++x` `--x` `x++` `x--` `!x` `~x`
* **Binary** Operators:  (operators that work with 2 "variables")

  Takes two operands `x + y` `x - y` `x * y` `x / y` `x % y` `x && y` `x || y`
* **Ternary** Operator: (operators that work with 3 "variables")

  Takes three operands `x ? y : z`

## Arithmetic Operators

These are your typical mathematical operators:

* `+` addition 
* `-` subtraction
* `*` multiplication
* `/` division 
* `%` modulo (a%b means the remainder of a divided by b)
* `+` unary plus (no effect, just for symmetry)
* `-` unary minus
* ...

**Beware that different operators carry different precedences**, meaning values are evaluated from the operator with the highest precedence down to the lowest, like how multiplication comes first before addition in maths. In general: `unary operator` > `*`, `/`, and `%` > `+` and `-` (addition and subtraction)

You may learn these different operator precedence on the way as you learn programming. But in general, when in doubt, it is best to put `()` to guarantee that a certain operation must be run first.

```c
#include <stdio.h>

int main() {
    printf("addition: %d\n", 2 + 3); // prints 5
    printf("subtraction: %d\n", 20 - 8); // prints 12
    printf("multiplication: %d\n", 500 * 4); // prints 2000
    printf("division (int): %d\n", 5 / 2); // prints 2
    printf("division (float): %f\n", 5.0f / 2.0f); // prints 2.5
    printf("modulo: %d\n", 13 % 5); // prints 3

    printf("test: %d", 25+5*5) //prints 50, multiplication comes before addition
    printf("test: %d", (25+5)*5) //prints 150
  
    return 0;
}
```

> **Warning:** Note the two different divisions in the example above. In math, 5 / 2 = 2.5. However, in C, both `5` and `2` are integers, so integer division is performed. This means the decimal part is discarded giving `2` as its result. In contrast to this, `5.0f` and `2.0f` are floats, so floating-point division is performed and the decimal part is retained, giving (about) `2.5` as its result.


## Compound Assignment Operators

Shortcuts to merge arithmetic and assignment into one operation. For example:

* `+=`: Adds right operand to left operand, and assigns the resultant value to left operand.

```c
int a = 1;
int b = 2;

a += b; // equivalent to a = a + b, a = 1 + 2 = 3
```

There are more assignment operators (e.g. `-=`, `/=`, `%=`). Read [this](https://www.tutorialspoint.com/cprogramming/c\_assignment\_operators.htm) for more details.

## Relational Operators

A relational operator compares the value of two expressions, most of which are self-explanatory. These operators take two operators and return `true`/`1` or `false`/`0`.

* `==` equal to
* `!=` not equal to
* `>` greater than
* `>=` greater than or equal to
* `<` less than
* `<=` less than or equal to

The precedence of relational operators are after arithmetic operators

## Logical Operators

* `||`: Logical "or". Returns `true` if left or right operands are non-zero.
* `&&`: Logical "and". Returns `true` if left and right operands are non-zero
* `!` Logical "not". Reverses the truthness of its operand.

These operators accept **boolean-represented** values on both siesidess and perform logical operations on them to return a boolean value.

> **Warning:** `!` has a higher precedence than `||` and `&&`. Additionally, `&&` has a higher precedence than `||`

The precedence of logical operators are after relational operators.

### Truth Table


|    P    |    Q    | P \|\| Q | P && Q |  !P  |
| :-----: | :-----: | :-----: | :-----: | :-----: |
| `false` | `false` | `false` | `false` | `true` |
| `false` | `true` | `true` | `false` | `true` |
| `true` | `false` | `true` | `false` | `false` |
| `true` | `true` | `true` | `true` | `false` |

Read [Operators in C and C++ on Wikipedia](https://en.wikipedia.org/wiki/Operators\_in\_C\_and\_C%2B%2B) for more information, including **Bitwise operators**, **compound assignment operators**, **member and pointer operators**, etc.

> **TIPS**: Conditions can be chained by logical operators. For example:
>
> `int_a != int_b || !(int_c > int_d)`

## Self Test

Q1. Determine the output of the following program:
```c
#include <stdio.h>

int main(){
  int a = 7;
  int b = 5;
  a += 2;
  b += a;
  printf("a: %d\n", a);
  printf("b: %d\n", b);
  int c = (a < b) + (b <= 7) + (a==9) + !(a==9);
  printf("c: %d\n", c);
  int d = a==8 || a==9 && a==10;
  printf("d: %d\n", d);
  printf("e: %d\n", 4 + 1<3);
}
```

<details>
  <summary>Ans</summary>
  The program will output
  
  <pre>
  a: 9
  Reason: the line a += 2; is equivalent to a = a + 2 -> a = 7+2 = 9

  b: 14
  Reason: the line b += a; is equivalent to b = b + a -> b = 5 + 9 (the value of a is 9 now) = 14

  c: 2
  Reason: 
  - (a < b) is (9 < 14), which is true (1)
  - (b <= 7) is (14 <= 7), which is false (0)
  - (a == 9) is (9 == 9), which is true (1)
  - !(a == 9) is !(true), which is false (0)
  1 + 0 + 1 + 0 = 2

  d: 0
  Reason:
  - (a==8) is false (0)
  - (a==9) is true (1)
  - (a==10) is false (0)
  But the precedence of && is higher than ||, so:
  0 || 1 && 0 -> 0 || (1 && 0) -> 0 || 0 -> 0

  e: 0
  Reason: Arithmetic operators are done before relational operators.
  4+1 < 3 -> 5 < 3 -> false (0)
  </pre>
</details>

If you have more time, you can try out different things and find their reasons:

- Is it possible to do `2 += 3`?
- Is it possible to do `42 && 7`?
- What will be the output of `int a = 3; printf("%d", a+=4);`? 
- etc.

You may consult this [full list for precedence](https://en.cppreference.com/w/c/language/operator_precedence).

However, these cases are quite rare, those explained in the self-test should be sufficient.

## Increments and Decrements*

`++` and `--` are unary operators that can only work on non-literals. They are operators that can be used to increase and decrease value by 1 respectively.

```c
#include <stdio.h>

int main(){
  int a = 5;
  a++;
  int b = 6;
  --b;
  printf("a: %d", a); //prints 6
  printf("b: %d", b); //prints 5
}
```
However, do note that putting it in front or at the back of the variable might matter.

Writing `++a`, will modify the variable `a` and pass the modified variable

Writing `a++`, will pass the variable value first, then modify the variable `a`

```c
#include <stdio.h>

int main(){
  int a = 7;
  int b = 7;
  printf("a: %d", ++a); //prints 8 (the modified value is passed)
  printf("b: %d", b++); //prints 7 (the unmodified value is passed, the modification performed later)
  printf("b (again): %d", b); //prints 8
}
```

[Continue to The Next Page](06-variables-more.md)
