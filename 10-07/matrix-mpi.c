#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 4

void initialize(double * M, int size);
void print(double * M, int size);
void check(int size);

int main(int argc, char **argv)
{
  double * A = malloc(SIZE*SIZE*sizeof(double)); // does not scale for large matrices
  
  // initialize matrix
  initialize(A, SIZE);

  // checking
  check(SIZE);

  // print matrix
  print(A, SIZE);

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

void print(double * M, int size)
{
  FILE *fp;
  fp = fopen( "matrix.out", "w+b" );
  fwrite( M, sizeof(double), size*size, fp); 
  fclose( fp );
}

void check(int size)
{
  // does not scale for large matrices
  double * M = malloc(size*size*sizeof(double));
  
  // read matrix
  FILE *fp;
  fp = fopen( "matrix.out", "r+b" );
  fread( M, sizeof(double), size*size, fp); 
  fclose( fp );
  

  // compare with unit matrix
  int ii, jj;
  double sum = 0.0;
  for (ii = 0; ii < size; ++ii){
    for (jj = 0; jj < size; ++jj){
      sum += abs(M[ii*size + jj] - ((ii == jj) ? 1.0 : 0.0) ); 
    }
  }
  printf("------------- diff = %.12le -------------\n", sum);
}
