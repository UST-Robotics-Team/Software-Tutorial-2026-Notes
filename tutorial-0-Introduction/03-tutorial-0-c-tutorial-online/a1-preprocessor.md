# Preprocessor

## Preprocessor

**Preprocessor**: An instruction that takes action before compilation. It may expand source code, include/exclude source code, or optimise code in a particular way.

**Preprocessor directives**: Lines which start with `#`, which will be processed by the preprocessor.

### 4 Types of Preprocessor Directives

1. **File Inclusion**\
   Tells the compiler to include a file using the `#include` directive.
   * **standard / header file**: files provided by the (standard) library. Contains pre-defined functions like `printf()`. These files are included with `<>`. Example: `#include <stdio.h>`
   * **user-defined file**: header files defined/written by the user. It's a good practice to divide up functions into separate files and include only when needed. These files are included with `""`. Example: `#include "mylibrary.h"`
2.  **Macro**\
    Associates a name with a piece of code. During preprocessing, the compiler will replace all encounters of the name with the corresponding code. Macros are defined with the `#define` directive.

    ```c
    #define SIZE 5

    //  All occurrences of `SIZE` will be replaced by `5`.
    int array[SIZE];
    for (int i = 0; i < SIZE; i++) {
    	scanf(" %d", &array[i]);
    }
    for (int i = 0; i < SIZE; i++) { 
        printf("%d \n", array[i]); 
    }
    ```

    Macros can take arguments and can be used like functions.

    **Sample Code**

    ```c
    #include <stdio.h>

    #define PI 3.14159265
    #define CIRCLE_AREA(r) (r*r*PI)

    int main() {
        float radius = 10.0, area;
        
        area = CIRCLE_AREA(radius);
        printf("Area of the circle : %ld", area);
        
        return 0;
    }
    ```
3.  **Conditional Compilation**\
    Tells C to compile a specific portion of the program or to skip compilation of some specific part of the program based on conditions, enclosed with `#ifdef`, and `#endif`.

    ```c
    #ifdef macro_name
        // code to be compiled if a macro named
        // `macro_name` is defined.
        // if it's not defined, compiler will just 
        // skip this chunk of code.
    #endif
    ```

    You can also use `#if`,`#elif` and `#else` for conditional compilation.

    ```c
    #if defined macro_name
        // code to be compiled if a macro named
        // `macro_name` is defined.
    #elif defined another_macro
        // code to be compiled if the macro 
        // above is not defined.
        // and a macro named `another_macro` is defined.
    #else
        // code to be compiled if above two macros
        // are not defined.
    #endif
    ```
4. **Others**

*   `#undef`: used to undefine existing macros.

    ```c
    #define X 10
    // after this, X will be replaced with 10
    #undef X
    // after this, X is not defined
    #define X 20
    // after this, X will be replaced with 20
    ```
*   `#pragma`: a subset of special commands for the compiler. Some pragma directives are unique to certain compilers. Examples:

    ```
    #pragma once
    #pragma GCC optimize ("O3")
    #pragma forceinline
    ```
