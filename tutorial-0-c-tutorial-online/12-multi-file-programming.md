[Back to Main](README.md) | [Previous Page](11-struct.md)


# Multi-file Programming

> Please don't write more than 1000 lines of code in 1 file

> There are some topics that are less important, they will be marked with `*` in the title. But we may need a slight understanding of it for the next parts.


## File Types

C programs are stored as plain text in, often, 2 file types, with their conventional usages. Do follow the conventions, as there are practical and real differences you will see later on.

* `.c` **Source files** - These files contain function implementations.

  For example: the Hello World program is stored within `main.c` in my case in some arbitrary project folder that I have created for the tutorial.
* `.h` **Header files** - These files contain functions, structs, global variables, and macro declarations. _Basically, anything declared that can be accessed globally._

  For example: `stdio.h` is an actual header file stored in your computer, and is installed along with your choice of **C toolchain**. The path of different people would likely be different.

  The reason your IDE is able to detect where the libraries are because the installation of the toolchain also appended the source directories within your `PATH` (system environment variable), or the installation path is manually selected in your IDE settings.

  To include **compiler-defined** libraries, use `<>`. For example:

  ```c
  #include <stdio.h>
  #include <math.h>
  ```

  To include **user-defined** libraries, use `""`. For example:

  ```c
  #include "my_header_file.h"
  #include "your_header_file.h"
  ```

## Multi-file Programming

### Creating your own `.h` files

You can create an `<file_name>.h` file to include the declarations of variables in `<file_name>.c`.

For example if you created a file named `utility.c` that looks like:

```c
#include "utility.h"

int some_important_variable = 3;

int f(int x, int y){
  return x*y;
}
```

You can make a file `utility.h`
```h
int some_important_variable;
int f(int, int);
```

By doing this, you can access the function and variables in `utility.h`, say `main.c`

```c
int some_important_variable;
int f(int, int);

#include <stdio.h>

int main(){
  int a = 2; int b = 3;
  printf("%d + %d = %d", a, b, f(a,b));
}
```

`#include <some_file>` means writing the whole content of the file there, in this case:

The `extern` keyword is needed, otherwise, the program 

```c
#include "utility.h" //remember to use double quotes instead
#include <stdio.h>

extern int c; //for variables you need to do this

int main(){
  int a = 2; int b = 3;
  printf("%d + %d = %d", a, b, f(a,b));
}
```

Using this method, you can put parts of your code to different files.

You can also define `struct`s in the header file to be used in the `.c` files. For example:

In `color.h`
```h
struct Color{
  int R; int G; int B;
};

typedef struct Color Color;
```

Then in `main.c` you can use this struct without rewriting it.
```c
#include "color.h"

int main(){
  Color white = {255, 255, 255};
}
```

## Separate Compilation
Now that we are able to separate our code to multiple files, to compile it we can do the following:

```
gcc <file1>.c <file2>.c ... <header1.h> <header2.h> ...
```

For example if our project consists of `utility.h`, `utility.c` and `main.c`, then we can run the command:

```
gcc utility.h utility.c main.c
```


However, this might be quite inefficient, for example, if we only change `<file1>.c` we may need to recompile all files again (which may take long in a large project).

Instead, we may just recompile `<file1>.c` and files that depends on it. Hence, usually we will create object (`.o`) files that will store the compiled version of the `.c` file.

To make `.o` files, we use:

```
gcc -c utility.c main.c utility.h ... (all .c and .h files)
```
It will create the `utility.o` and `main.o`. 

Then we can use:
```
gcc utility.o main.o
```
To compile everything into a `.exe` file

Let's assume that we modify parts of `main.c`, instead of recompiling `utility.c` we can just:

```
gcc -c main.c
```
and rerun the command to make the `.exe`. You just need to regenerate `.o` file for edited files.

However, if we modify `utility.c`, then we need to recompile both files. Because `main.c` is dependent to `utility.c` and we need to do the usual:
```
gcc -c main.c utility.c utility.h
```

This shows how we can save compilation time in a large project. The dependency issue may sound troublesome, that is why we usually have something called `Makefile` to handle it. However, in the case of an STM32CubeIDE project, you will be provided with a `Makefile` so you do not need to worry about writing one yourself (but we encourage you to learn more about it if you have time). We hope that through this explanation, you get more idea on how to break up your code to files.

> Note that for your homework we will use the provided the inefficient compiling method of generating the `.o` files then combining them together. However, feel free to try this concept out yourself (separate compile some small file and its dependency to get a better idea about this part)

## Optional Exercise 5

> We covered the materials needed for your **Optional Exercise 5**! You can access it [here](https://github.com/UST-Robotics-Team/Software-Tutorial-2024-Notes/tree/main/tutorial-1-c-and-cubeide-setup/classwork/classwork-5-mean-median-min-max). Let's do it before moving on again.

The next topic is about recusion, but this is a very optional topic.

[Continue to the Next Page](12-recursion.md)
