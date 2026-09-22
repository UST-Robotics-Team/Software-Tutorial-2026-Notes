#include <stdio.h>
#include <string.h>

#include "mean.h"
// TODO: more includes here

float numbers[300];
int count = 0;

int main(){
    printf("Enter a number to append to the number set.Enter \"\\\" to stop appending.\n");

    //TODO: read numbers from user input

    printf("Mean=%f\n", mean(numbers, count));

    //TODO: print median, min, max
}
