[Back to Main](README.md) | [Previous Page](10-functions.md)

# Struct

> At times, the data types provided by C might not be enough...


## Struct

`struct` (for structure) is a user-defined data type for combining data items with different types into one.

Syntax:
```
struct <struct_name> {
    <data_type1> <data_name1>;
    <data_type2> <data_name2>;
    <data_type3> <data_name3>;
    ...
};
```
To declare a variable with the struct as the data type:

```
struct <struct_name> <variable_name>;
```

To assign values to the data inside of the struct (can only do this on the declaration):
```
struct <struct_name> <variable_name> = {data1, data2, ...};
```

For example, if we would like to make a struct to contain the information of UST members.

```c
#include <stdio.h>

int main(){
    struct USTMember {
        char name[20];
        int ID;
        int age;
    };

    //declaration of a variable of type UST Member
    /*
        here, name = "Mark", ID = 29823163, age = 17
    */
    struct USTMember student1 = {"Mark", 29823163, 17};
    //structs can be partially initialized, however uninitalized data will contain garbage value
    struct USTMember student2 = {"Sam", 23478912};
    //It is also OK to not initialize anything
    struct USTMember student3; 


    //If you would like to declare a variable right after declaring the structure of the struct, you may use the following shorthand syntax (put the variable name before the semicolon):

    struct USTProfessor {
        char name[20];
        int ID;
        char department[5];
    } professor1 = {"Tyler", 12362133, "COMP"};
}
```

You can access members of the structure using the dot operator `.`. For example: `Student.ID` or `Student.age`.

More things to note and some examples:

```c
#include <stdio.h>
#include <string.h>

struct USTMember {
    char name[20];
    int ID;
    int age;
};    

int main() {
    struct USTMember student1;

    /*if you need to change the values after initialization, you need to edit it for each member*/
    strcpy(student1.name, "John");
    student1.ID = 1010;
    student1.age = 18;
    
    printf("Student Name : %s\n", student.name); //accessing data members
    printf("Student ID : %d\n", student.ID);
    printf("Student Age : %d\n", student.age);   

    print_info(student1);

    struct USTMember student2;

    /* However, you can also do the following, in this case all contents of student1 (including the content of the arrays) will be copied memberwise. In other words, student2.name = "John", student2.ID=1010, student2.age = 18*/
    student2 = student1; 

    struct USTMember student_array[5] = {
        {"Colin", 21378931, 17}, 
        {"Edward", 21346758}
    }; //You can also declare array of structs. As usual, members that are not stated explicitly will be garbage values.

    return 0;
}
```

However, at times, it might be too long to write `struct X`. You can actually shorten this by using `typedef`.

```c
typedef struct{
    int R; int G; int B;
} Color;

Color violet = {255, 0, 255}; //no longer requires typedef
```

## Typedef

In general, however, `typedef` also can rename any other type. 

Syntax:
```
typedef <what-to-rename> <new-name>
```

For example:

```c
#include <stdint.h>

int main(){
    typedef int32_t i32;
    typedef uint32_t u32;
    i32 x = -7; u32 y = 9;
}
```

## Enums (Optional)

Do you still remember about this example in the control flow notes:

```c
int day = 7; //let 1 be Monday, 2 be Tuesday, ...

switch (day) {
    case 6: 
    case 7: 
        printf("There are no lectures today\n");
        break; 
    case 1: 
    case 2: 
    case 3: 
        printf("We have robotics tutorial today\n");
    case 4: 
    case 5: 
        printf("We have lectures today\n");
        break;
    default:
        printf("Invalid day\n");
}
```

Could it be nicer if we can write `MONDAY` instead of `1` or `SUNDAY` instead of `7`? Turns out, you can do it with `enum`:

Declaration syntax:
```
enum <Group-Name> {<constant1>, <constant2>, ...};
```

This is another way of creating your own type in C, the type will be named `<Group-Name>`

For example:
```c
enum Days {MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY};

Days day = SUNDAY; //notice that int is changed to Days

switch (day) {
    case SATURDAY: 
    case SUNDAY: 
        printf("There are no lectures today\n");
        break; 
    case MONDAY: 
    case TUESDAY: 
    case WEDNESDAY: 
        printf("We have robotics tutorial today\n");
    case THURSDAY: 
    case FRIDAY: 
        printf("We have lectures today\n");
        break;
    default:
        printf("Invalid day\n");
}
```

This will give your code better readability. It gives meaningless constant a better name.

Here, what's happening is that the first constant `MONDAY` will be assigned to `0`, `TUESDAY` will be assigned to `1` (`+1` of the previous value), and so on until `SUNDAY` is assigned to `6`

```c
enum Days {MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY};
printf("%d %d %d %d %d %d %d", MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY)
```

Output:
```
0 1 2 3 4 5 6 
```

You may make some changes to the numbers assigned. The next constants will have the value `+1` of it.

```c
enum HTTP_Errors {NONE, UNAUTHORIZED=401, PAYMENT_REQUIRED, FORBIDDEN, NOT_FOUND, INTERNAL_SERVER_ERROR=500, NOT_IMPLEMENTED=501};

printf("%d %d %d %d %d %d %d", NONE, UNAUTHORIZED, PAYMENT_REQUIRED, FORBIDDEN, NOT_FOUND, INTERNAL_SERVER_ERROR, NOT_IMPLEMENTED);
```
Output:
```
0 401 402 403 404 500 501
```

Otherwise, by default the start value will be `0` and the values following it will be `+1` the previous. Note that values can be negatives, but it cannot be floating point numbers.

## Self-Tests

Q1. Determine the output of the following program:
```c
#include <stdio.h>

typedef struct {
    int buf[100];
    int ptr;
} Stack;

Stack createEmptyStack(){
    Stack s;
    s.ptr = -1;
    return s;
}

int isEmpty(Stack stack){
    return stack.ptr == -1;
}

void print_stack(Stack stack){
    printf("The stack object looks like the following:\n");
    if(isEmpty(stack)) {
        printf("<Empty Stack>\n");
        return;
    }
    printf("-----\n");
    for(int i=stack.ptr; i>=0; i--){
        printf("  %d  \n-----\n", stack.buf[i]); 
    }
}

Stack stack(Stack stack, int value){
    stack.ptr++;
    stack.buf[stack.ptr] = value; 
    return stack;
}

Stack pop(Stack stack){
    if(isEmpty(stack)) return stack;
    stack.ptr--;
    return stack;
}

int main(){
    Stack haha = createEmptyStack();
    print_stack(haha);
    haha = stack(haha, 7);
    haha = stack(haha, 1);
    haha = stack(haha, 9);
    haha = stack(haha, 8);
    print_stack(haha);
    haha = pop(haha);
    print_stack(haha);
    haha = stack(haha, 7);
    haha = stack(haha, 7);
    print_stack(haha);
    return 0;
}

```

<details>

<summary>Ans</summary>

```
The stack object looks like the following:
<Empty Stack>
The stack object looks like the following:
-----
  8  
-----
  9  
-----
  1  
-----
  7  
-----
The stack object looks like the following:
-----
  9  
-----
  1  
-----
  7  
-----
The stack object looks like the following:
-----
  7  
-----
  7  
-----
  9  
-----
  1  
-----
  7  
-----
```

</details>



## Optional Exercise

> We covered the materials needed for your **Optional Exercise 4**! You can access it [here](classwork/classwork-4-greyscale-image.md) (Used to be a classwork). Feel free to give it a try to check your understanding.



</details>


[Continue to The Next Page](12-multi-file-programming.md)

