# Union

> a box with multiple names

## Union

**union**: Data-type which stores data items with different types in the same memory location.

```c
union Data {
   int i;
   float f;
   char s[15];
} data;
/**
 *  `Data` is an optional union tag.
 *  `data` is a variable of type `union Data`.
 *  Declaring variables after the union is optional.
 * /
```

#### Sample Code

```c
#include <stdio.h>
#include <string.h>
 
union Data {
   int i;
   float f;
   char s[15];
};
 
int main() {
   union Data data; /* variable `data` of type Data */ 

   data.i = 1;
   data.f = 3.14;
   strcpy(data.s, "Robotics team");

   printf("data.i : %d\n", data.i);
   printf("data.f : %f\n", data.f);
   printf("data.str : %s\n", data.s);

   return 0;
}
```

Output:

```
data.i : 1868722002
data.f : 70078190219652804681100427264.000000
data.str : Robotics team
```

Note that prior to printing the data members, the final value set is `"Robotics team"` to the `char s[15]` member.

The result would be chaotic because all data members are stored in the same memory. The printed values will correspond to "Robotics team" in their own data type.
