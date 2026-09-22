[Back to Main](../README.md)

# Classwork 2 : First Word

In the tutorial, we mentioned that `\0` is a special character that indicates the end of a char array. In this question, you are required to print the first word found in the char array. That is, you should only print up to the first (space character). You should remove / not display the characters afterwards.

## Example

Input: `Danny is lonely.` Output: `Danny`

Input: `Chalex is handsome.` Output: `Chalex`

## Skeleton Code

```c
#include <stdio.h>

int main() {
  char input[] = "Welcome to HKUST Robotics Team Software Tutorial";
  printf("Before trimming: %s\n", input);

  // your code starts here
  
  // your code ends here
  
  printf("After trimming: %s\n", input);
  return 0;
}
```
