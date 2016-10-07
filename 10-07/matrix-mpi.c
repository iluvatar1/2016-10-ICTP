#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

//#define SIZE 8192

void initialize(double * M, int sizea, int sizeb, int rank);
void print(double * M, int sizea, int sizeb, int rank, FILE * fp);
void check(int size);

int main(int argc, char **argv)
{
  int SIZE = -1;
  if (argc != 2) {
    printf("ERROR.\nProgram must be called as ./program matrix_col_length \n");
    exit(1);
  }
  SIZE = atoi(argv[1]);

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
  FILE * fp;

  // initialize matrix - per process
  initialize(A, size_x, size_y, my_rank);
  
  // sending / receiving matrix and printing
  if (0 == my_rank) {
    // open file stream
    fp = fopen("matrix-parallel.out", "w+b"); 
    // print my data
    print(A, size_x, size_y , my_rank, fp);
    // receive from others and print at the correct position
    int src;
    for (src = 1; src < np; ++src) {
      MPI_Recv(A, size_x*size_y, MPI_DOUBLE, src, 99, MPI_COMM_WORLD, &status);
      print(A, size_x, size_y , src, fp);
    }
    // close file stream
    fclose(fp);
    // checking
    //check(SIZE);
  }
  else {
    int des = 0;
    MPI_Send(A, size_x*size_y, MPI_DOUBLE, des, 99, MPI_COMM_WORLD);
  }

  MPI_Finalize();

  return 0;
}

void initialize(double * M, int sizea, int sizeb, int rank)
{
  int offset = rank*sizea;
  int ii, jj;
  for (ii = 0; ii < sizea; ++ii) {
    for (jj = 0; jj < sizeb; ++jj) {
      M[ii*sizeb + jj] = 0.0;
      if (ii + offset == jj) M[ii*sizeb + jj] = 1.0;
    }
  }

/* #ifdef DEBUG   */
/*   printf("rank = %d\n", rank); */
/*   for (ii = 0; ii < sizea; ++ii) { */
/*     for (jj = 0; jj < sizeb; ++jj) { */
/*       printf("%.3le  ", M[ii*sizeb + jj]); */
/*     } */
/*     printf("\n"); */
/*   } */
/*   printf("\n"); */
/* #endif */
}

void print(double * M, int sizea, int sizeb, int rank, FILE * fp)
{
  // set the right position to write
  //fseek(fp, rank*sizea*sizeb*sizeof(double) , SEEK_SET); 
  fwrite( M, sizeof(double), sizea*sizeb, fp); 
  fflush( fp ); 
}

// DOES NOT SCALE FOR LARGE MATRICES
// DOES NOT SCALE FOR LARGE MATRICES
// DOES NOT SCALE FOR LARGE MATRICES
// DOES NOT SCALE FOR LARGE MATRICES
// DOES NOT SCALE FOR LARGE MATRICES
void check(int size)
{
  double * M = malloc(size*size*sizeof(double));
  
  // read matrix
  FILE *fp;
  fp = fopen( "matrix-parallel.out", "r+b" );
  fread( M, sizeof(double), size*size, fp); 
  fclose( fp );
  

  // compare with unit matrix
  int ii, jj;
  double sum = 0.0;
  for (ii = 0; ii < size; ++ii){
    for (jj = 0; jj < size; ++jj){
      #ifdef DEBUG
      printf("%.3lf  ", M[ii*size + jj]);
      #endif
      sum += fabs(M[ii*size + jj] - ((ii == jj) ? 1.0 : 0.0) ); 
    }
    #ifdef DEBUG
    printf("\n");
    #endif
  }
  printf("------------- diff = %.12le -------------\n", sum);
}
