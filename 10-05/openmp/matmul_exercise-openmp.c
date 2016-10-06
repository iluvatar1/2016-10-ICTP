/*
 * This code is created for teaching purpose at the ICTP SMR2877 activity 
 * "Introductory School on Parallel Programming and Parallel Architecture for High-Performance Computing"
 *
 * Author: Ivan Girotto (igirotto@ictp.it)
 * Last Revision: October 2016
 *
 */

/*
 *                              *** EXERCISE ***
 *
 * a) Implement the missing part of this code which aims to execute C = A x B 
 *    where A,B,C are matrixes in double precision of size = SIZE x SIZE
 *
 * b) compile the code using different levels of compiler optimization (0, 1, 2, 3), 
 *    run the executable and analize the performance results. 
 *
 *    1) gcc -o exec_matmul.x -c matmul_exercise.c -lblas
 *    2) gcc -o -O0 exec_matmul.x -c matmul_exercise.c -lblas
 *    3) gcc -o -O1 exec_matmul.x -c matmul_exercise.c -lblas
 *    4) gcc -o -O2 exec_matmul.x -c matmul_exercise.c -lblas
 *    5) gcc -o -O3 exec_matmul.x -c matmul_exercise.c -lblas
 *
 * c) compile the code adding the option for compiler vectorization, -mavx, 
 *    suitable for the computer architectures available at the info-lab  
 *
 * d) answer to the following question:
 *    What is the default level of optimization used by the GNU compiler?!
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/time.h>
#include <cblas.h>

#include <omp.h>

/* Define the Matrix size */
#define SIZE 1024

void compare(double *M, double *M_BLAS);
void print(double *M);

/* Return the second elapsed since Epoch (00:00:00 UTC, January 1, 1970) */
double seconds()
{
  struct timeval tmp;
  double sec;
  gettimeofday( &tmp, (struct timezone *)0 );
  sec = tmp.tv_sec + ((double)tmp.tv_usec)/1000000.0;
  return sec;
}

int get_idx(int i, int j) { return i*SIZE + j; }
int get_i(int idx) { return idx/SIZE; }
int get_j(int idx) { return idx%SIZE; }

int main(int argc, char * argv[]){
  
  /* Variables Declaration */
  double *A, *B, *C, *C_BLAS;
  int i = 0, j = 0, k = 0;
  double t_start, t_end;
  
  /* Dynamic Memory Allocation */
  A = (double *) malloc(SIZE*SIZE*sizeof(double)); if (NULL == A) printf("ERROR getting memory for matrix A \n");
  B = (double *) malloc(SIZE*SIZE*sizeof(double)); if (NULL == B) printf("ERROR getting memory for matrix B \n");
  C = (double *) malloc(SIZE*SIZE*sizeof(double)); if (NULL == C) printf("ERROR getting memory for matrix C \n");
  C_BLAS = (double *) malloc(SIZE*SIZE*sizeof(double)); if (NULL == C_BLAS) printf("ERROR getting memory for matrix C_BLAS \n");

  /* Initialization to 0.0 for the output matrixes */
  memset( C, 0, SIZE * SIZE * sizeof(double) );
  memset( C_BLAS, 0, SIZE * SIZE * sizeof(double) );
  
  /* Initialization (random values) for the input matrixes */
  srand48(0); // the seed
  for( i = 0; i < SIZE; i++ ){
    for( j = 0; j < SIZE; j++ ){
      A[get_idx(i, j)] = drand48();
    }
  }
  for( i = 0; i < SIZE; i++ ){
    for( j = 0; j < SIZE; j++ ){
      B[get_idx(i, j)] = drand48();
    }
  }

  /* Naive implementation of a matrix multiplication */
  /* Start the timer */
  t_start = seconds();
  // perform the operation
  for( i = 0; i < SIZE; i++ ){
    for( j = 0; j < SIZE; j++ ){
      C[get_idx(i, j)] = 0.0;
      for (k = 0; k < SIZE; ++k) {
	C[get_idx(i, j)] += A[get_idx(i, k)]*B[get_idx(k, j)];
      }
    }
  }  
  /* Stop the timer */
  t_end = seconds();
  /* Print on standard output the obtained time to solution using "naive" implementation */ 
  fprintf( stdout, "\n\tMatrix Multiplication completed. Time to solution of \"naive\" version = %.3g seconds\n\n", t_end - t_start );
  
  /* openmp implementation of a matrix multiplication */
  /* Start the timer */
  t_start = seconds();
  // perform the operation
  #pragma omp parallel for private(i, j, k)
  for( i = 0; i < SIZE; i++ ){
    for( j = 0; j < SIZE; j++ ){
      C[get_idx(i, j)] = 0.0;
      for (k = 0; k < SIZE; ++k) {
	C[get_idx(i, j)] += A[get_idx(i, k)]*B[get_idx(k, j)];
      }
    }
  }  
  /* Stop the timer */
  t_end = seconds();
  /* Print on standard output the obtained time to solution using "naive" implementation */ 
  fprintf( stdout, "\n\tMatrix Multiplication completed. Time to solution of \"openmp\" version = %.3g seconds\n\n", t_end - t_start );
  
  
  /* execution of a Matrix Multiplication C = A x B, using Linux internal BLAS library */
  t_start = seconds();
  
  /* Execution of DGEMM operation using standard BLAS interface */
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, SIZE, SIZE, SIZE, 1.0, A, SIZE, B, SIZE, 0.0, C_BLAS, SIZE);
  
  t_end = seconds();
  
  /* Print on standard output the obtained time to solution using "DGEMM" standard BLAS interface */  
  fprintf( stdout, "\n\tMatrix Multiplication completed. Time to solution of Linux internal BLAS version = %.3g seconds\n\n", t_end - t_start );
  
  // comparison
  compare(C, C_BLAS);

  /* Memory deallocation */
  free(A);
  free(B);
  free(C);
  free(C_BLAS);
  
  return 0;
}
  
void print(double *M) {
  int ii, jj;
  for (ii = 0; ii < SIZE; ++ii){
    for (jj = 0; jj < SIZE; ++jj){
      printf("%g ", M[get_idx(ii, jj)]);
    }
    printf("\n");
  }
}

void compare(double *M, double *M_BLAS) {
  int ii, jj;
  double diff = 0;
  for (ii = 0; ii < SIZE; ++ii){
    for (jj = 0; jj < SIZE; ++jj){
      diff = abs(M[get_idx(ii, jj)] - M_BLAS[get_idx(ii, jj)]);
    }
  }
  printf("The difference is %.5le\n", diff);
}
  
