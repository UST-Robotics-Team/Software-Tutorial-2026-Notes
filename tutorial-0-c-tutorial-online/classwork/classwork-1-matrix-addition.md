[Back to Main](../README.md)

# Classwork 1 : Matrix Addition

> What do mathematicians sleep on? Matrices!!

A matrix is a rectangular arrangement of numbers into rows and columns. Each number in a matrix refers to a matrix element.

To perform matrix addition, you need to have two matrices of the same size. Then you can sum up the entries respectively.

Example:

```math
A=\begin{bmatrix} a_1 & a_2 \\ a_3 & a_4 \\ a_5 & a_6 \end{bmatrix}
```

We call the matrix above a $3\times2$ matrix with entries $a_1$ to $a_6$

Now, given another $3\times2$ matrix $B$

```math
B=\begin{bmatrix} b_1 & b_2 \\ b_3 & b_4 \\ b_5 & b_6 \end{bmatrix}
```

Since the size of $A$ and
$B$ are the same, we can perform matrix addition:

```math
A+B=\begin{bmatrix} a_1+b_1 & a_2+b_2 \\ a_3+b_3 & a_4+b_4 \\ a_5+b_5 & a_6+b_6 \end{bmatrix}
```

## Task

Implement the code to perform matrix addition.

```c
#include <stdio.h>

void display_matrix(int matrix[][2], int num_row) {
  for (int r = 0; r < num_row; r++) {
    for (int c = 0; c < 2; c++) {
      printf("\t%d", matrix[r][c]);
    }
    printf("\n");
  }
}

int main() {
  int matrix_A[3][2] = {
    {0, 1},
    {2, 3},
    {4, 5}
  };
  
  int matrix_B[3][2] = {
    {0, 1},
    {2, 3},
    {4, 5}
  };
  
  int result[3][2] = {0};
  
  // your code starts here
  
  // your code ends here
  
  printf("A = \n");
  display_matrix(matrix_A, 3);
  printf("\nB = \n");
  display_matrix(matrix_B, 3);
  printf("\nA + B = \n");
  display_matrix(result, 3);
  return 0;
}
```