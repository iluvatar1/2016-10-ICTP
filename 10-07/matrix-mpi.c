#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 4

void initialize(double * M, int size);

int main(int argc, char **argv)
{
  double * A = malloc(SIZE*SIZE*sizeof(double));
  
  // initialize matrix
  initialize(A, SIZE);

  // checking
  
  // print matrix


  return 0;
}

void initialize(double * M, int size)
{
  int ii, jj;
  for (ii = 0; ii < size; ++ii){
    for (jj = 0; jj < size; ++jj){
      if (ii == jj) M[ii*size + jj] = 1.0; 
      else M[ii*size + jj] = 0.0;
    }
  }
}
