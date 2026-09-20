# Static/Extern

> Global variables, Local variables, Static variables, Extern variables, ...

## Statements

A statement is a fragment of code in C. All statement types are on [cppreference](https://en.cppreference.com/w/c/language/statements).

### Expression Statements

Expression statements are the lines of code that end in `;`. In other words: an expression statement is **a line of code**. Most statements are expression statements.

For example:

```c=
#include <stdio.h>

int main() {
    int some_integer = 0;
    printf("updated value: %d", some_integer = 100);
  
    return 0;
}
```

`some_integer = 100` is an expression. After execution, the expression statement returns 100. So eventually `updated value: 100` is printed. By making good use of this feature, you can minimize the lines of code.

### Compound Statements (Code Block)

Compound statements consist of one or more lines of code. It defines a **scope**. They are also called **code blocks**.

One in scope can access variables declared in itself, as well as variables in larger scopes, but not those in smaller scopes inside itself neighboring scopes nor any of its parents. Essentially, the access right to a variable is only at its level upwards.

For example:

```c=
#include <stdio.h>

int main() {
    int a = 10;
    int b = 20;
    printf("a: %d, b: %d\n", a, b);
    a = a + b;
    b = a - b;
    a = a - b;
    printf("a: %d, b: %d\n", a, b);
    return 0;
}
```

the code inside `{}` are compound statement.

### Global and Local Scope

TODO:

### Static/Extern/Inline

**`static`** : variables / functions with this keyword can only be accessed within the scope they're declared in.

```c
static int x = 0;
```

Their values will persist throughout the scope of a function or block.

**`extern`** : variables need to be declared with this keyword when they are accessed from external files.

#### Sample Code

```c
// library.c
int a = 100;
```

```c
// main.c
#include <stdio.h>

extern int a;

int main() {
    printf("a = ", a);
    return 0;
}
```

**`inline`** : functions defined with this keyword would expand to their definition within the code when they are called.

> #### What's good about inline functions?
>
> Inline functions expand their definition where called. This may help save cpu memory resources and time.

> Inline functions are cool, but if you inline a _huge_ function it could increase code size unnecessarily. So usually we only use this keyword on small and light functions.
