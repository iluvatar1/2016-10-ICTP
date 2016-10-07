#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define SIZE 8

void initialize(double * M, int sizea, int sizeb, int rank);
void print(double * M, int size);
void check(int size);

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);

  int my_rank = 0, np = 0;
  MPI_Status status;
  MPI_Request request;
  
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  // every process will have its own horizontal slice
  int size_x = SIZE/np; // fix this for non multiples
  int size_y = SIZE;
  double * A = malloc(size_x*size_y*sizeof(double)); 
  
  // initialize matrix - per process
  initialize(A, size_x, size_y, my_rank);
  
  // checking
  //check(SIZE);

  // print matrix
  //print(A, SIZE);

  MPI_Finalize();

  return 0;
}

void initialize(double * M, int sizea, int sizeb, int rank)
{
  int offset = (rank + 1)*sizea*sizeb;
  int ii, jj;
  for (ii = 0; ii < sizea; ++ii) {
    for (jj = 0; jj < sizeb; ++jj) {
      M[ii*sizeb + jj] = 0.0;
      if (ii + rank*sizea == jj) M[ii*sizeb + jj] = 1.0;
    }
  }

#ifdef DEBUG  
  printf("rank = %d\n", rank);
  for (ii = 0; ii < sizea; ++ii) {
    for (jj = 0; jj < sizeb; ++jj) {
      printf("%.3le  ", M[ii*sizeb + jj]);
    }
    printf("\n");
  }
  printf("\n");
#endif
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
