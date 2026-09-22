[Back to Main](README.md) | [Previous Page](05-operators.md)

# More on Variables

> There are some topics that are less important, they will be marked with `*` in the title. But we may need a slight understanding of it for the next parts.

## Rules on Variable Naming and Conventions

Please note that the name of variables have some rules:

Must only contain the characters: `A-Z`, `0-9`, and `_` (underscore)
```c
int i_love_tim_woo_520; //valid
```
First character cannot be numbers (`0-9`)
```c
int 520_i_love_tim_woo; //NOT valid
```
Some reserved words `int`,`float`, `switch`, `if`, ... cannot be used because they already have another meaning in C.
```c
int float; //NOT valid
```

With this rule only, there are many possibilities of variable such as `motor_speed`, `abc`, `m`, `k1k2k3`, `_` (underscore only is allowed).

However, please try to always give meaningful names to variables.

Moreover, for capitalization and spacing you may want to follow the following conventions:

There are several ways people name their variables, as illustrated in the names:

For variables (please follow your team/organization's preference):
* `PascalCase` (No space, capitalize the  first letter of words)
* `camelCase` (Same as above, except for the first word)
* `snake_case` (Use `_` instead of spaces)

For constants:

* `UPPER_SNAKE_CASE` 

Additionally:

* `kebab-case` (Cannot be used in C, but may be used for files)

## More Data Types 

Other than the common primitive data types, C also have:

### Booleans (`true` or `false`)

Following the standard of C99, it is possible to declare a boolean (true/false) variable as such:

```c
_Bool x = 0; //for false
_Bool y = 1; //for true
```
However to be able to write the data type as `bool` instead of `_Bool`, `false` instead of `0`, and `true` instead of `1`. You need to include the the library `stdbool.h` by using `#include <stdbool.h>`

> If you have learned python before: note that in C it is `true` instead of `True`

### Standard Integer Types

Sometimes, because memory may be limited in embedded systems. While types like `int` may have different size in different systems. You may want to have more control on the size of variables.

To include standard integer types, use `#include <stdint.h>`

|    Short Form    |    Full Name    | Meaning | Range |  
| :-----: | :-----: | :-----: | :-----: |
| `uint8_t` | unsigned char | unsigned 8 bits integer | $[0, 2^8-1]$|
|`uint16_t` | unsigned short | unsigned 16 bits integer | $[0, 2^{16}-1]$
|`uint32_t` | unsigned long | unsigned 16 bits integer | $[0, 2^{32}-1]$
|`uint64_t` | unsigned long long | unsigned 16 bits integer | $[0, 2^{64}-1]$
| `int8_t` | signed char | unsigned 8 bits integer | $[-2^7, 2^7 - 1]$|
|`int16_t` | signed short | unsigned 16 bits integer | $[- 2^{15}, 2^{15} - 1]$
|`int32_t` | signed long | unsigned 16 bits integer | $[- 2^{31}, 2^{31} - 1]$
|`int64_t` | signed long long | unsigned 16 bits integer | $[ - 2^{63}, 2^{63}-1]$

Note that it is common to see these types in our robot codes.

## Casting
Assigning a variable or literal in another type to a variable is possible through **casting**. Saving a lower-bit value to a higher-bit container is often safe, but the converse is always unsafe because information is lost by losing bits

Putting things from a small box to a big box is safe as we can put everything inside the big box

But putting things from a big box to a small box is unsafe because the small box might not have enough space to hold everything and the remaining things might be lost

Below are some examples:

```c
#include <stdbool.h>
#include <stdint.h>

int main(){
    bool b = true;
    int n = b; // compiler casts a boolean to an integer, n would be 1 because true -> 1; false -> 0

    char c = 'c';
    n = c; // compiler casts a character to an integer, by using ASCII conversion, n is now 99

    float f = 0.55f;
    n = f; // compiler casts a float to an integer, by truncating the floating point value, n is now 0, same goes with double

    uint8_t p = 6;
    uint16_t q = p; // compiler casts a 8-bit to a 16-bit, since 16-bit can hold larger values, q is also 6

    q = 678;
    p = q; // compiler casts a 16-bit to a 8-bit, since 8-bit cannot store a number this large, it will overflow.

    //Note: uint8_t can only store [0, 2^8=256]
    //678 in binary: 10 1010 0110
    //only the last 8 bit fits: 1010 0110, this is the number = 166

    int16_t j = -5;
    uint16_t k = j; // compiler casts a signed to unsigned, since it cannot store a negative number, it underflows and goes to 65531. Please refer to 2's complement integer representation to know more.

    return 0;
}
```

The type conversion above is an **implicit casting**, i.e. the compiler itself figures out the converted type. Usually, instead, we would prefer a safer approach, that we specify the converted type in our codes.

```c
float f = 2.5f;
int n = (int)f; //n is now 2
```

Just saying the one thing above **static_casing**, which we use it almost everyday. Static_cast is just directly tell the compiler to change the data-type without caring anything. If it fails, it will just return an error.

```c
float f = 2.5f;
int n = static_cast<int>f; //n is now 2
```

## `const`
 `const` is a type of qualifier in C. A variable with such a qualifier in front is not allowed to be reassigned.

```c
const double PI = 3.141592654;

PI = 2.718281828; //attempts to modify constant variables will cause a compiler error
```

[Continue to The Next Page](07-control-flow.md)
