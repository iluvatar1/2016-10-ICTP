/*
 * Copyright (C) 2001-2013 The Abdus Salam, International Centre of Theoretical Physics (ICTP)
 *
 * This file is distributed under the terms of the GNU General Public License. 
 * See http://www.gnu.org/copyleft/gpl.txt 
 *
 * The code was developed for the hands-on session of the M1.2 - HPC Master SISSA/ICTP
 * 
 * Example of code for Matrix transpose with static allocation 
 *
 * Author: Ivan Girotto
 * Last update: Nov-2013
 * 
 */

#include <stdlib.h>
#include <stdio.h>

#include <time.h>
#include <math.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/time.h>

#define MATRIXDIM 8192

double second()
/* Returns elepsed seconds past from the last call to timer rest */
{
  
  struct timeval tmp;
  double sec;
  gettimeofday( &tmp, (struct timezone *)0 );
  sec = tmp.tv_sec + ((double)tmp.tv_usec)/1000000.0;
  return sec;
}

int get_idx(int i, int j, int SIZE) {  return i*SIZE + j; }
int get_i(int idx, int SIZE) { return idx/SIZE; }
int get_j(int idx, int SIZE) { return idx%SIZE; }

void print(double * M, int SIZE);

void check(double * M, double * MT, int SIZE);

int main( int argc, char * argv[] ) {
  
  // define the blocksize
  int BLOCKSIZE = atoi(argv[1]);
  printf("BLOCK SIZE = %d\n", BLOCKSIZE);
  
  double t1, t2;
  double *A, *AT;
  int i, j;
  int ib, jb;
  
  #ifdef DEBUG
  FILE *fp;
  #endif
  
  A = (double* ) malloc( MATRIXDIM * MATRIXDIM * sizeof(double) ); 
  AT = (double* ) malloc( MATRIXDIM * MATRIXDIM * sizeof(double) ); 
  
  for( i = 0; i < MATRIXDIM; i++ ){
    for( j = 0; j < MATRIXDIM; j++ ){
      A[ (i * MATRIXDIM) + j] = (double) ( ( i * MATRIXDIM ) + j );
    }
  }
  
  //compute the number of block
  int nb = MATRIXDIM / BLOCKSIZE;

  // block buffer
  double *buffer = (double * ) malloc(BLOCKSIZE*BLOCKSIZE*sizeof(double));

  
  t1 = second();
  
  /* Implement loops over the blocks of the main Matrices while transposing internally to the cache block */
  // for each block
  //#pragma omp parallel for private(ib, jb, i, j)
  for (ib = 0; ib < MATRIXDIM; ib += BLOCKSIZE){
    for (jb = 0; jb < MATRIXDIM; jb += BLOCKSIZE){
      // copy data from A to buffer
      for (i = ib; i < ib + BLOCKSIZE; ++i) {
	for (j = jb; j < jb + BLOCKSIZE; ++j) {
	  buffer[(i-ib)*BLOCKSIZE + (j - jb)] = A[i*MATRIXDIM + j];
	}
      }
      // transpose buffer naively
      double tmp; 
      for (i = 0; i < BLOCKSIZE; ++i) {
	for (j = 0; j < BLOCKSIZE; ++j) {
	  tmp = buffer[i*BLOCKSIZE + j];
	  buffer[i*BLOCKSIZE + j] = buffer[j*BLOCKSIZE + i];
	  buffer[j*BLOCKSIZE + i] = tmp;
	}
      }
      // copy data from buffer to AT
      for (i = ib; i < ib + BLOCKSIZE; ++i) {
	for (j = jb; j < jb + BLOCKSIZE; ++j) {
	  AT[j*MATRIXDIM + i] =  buffer[(i-ib)*BLOCKSIZE + (j - jb)];
	}
      }
    }
  }

  t2 = second();
  check(A, AT, MATRIXDIM);
  
  #ifdef DEBUG
  fp = fopen( "transpose-V1.out", "w+b" );
  fwrite( AT, sizeof(double), MATRIXDIM * MATRIXDIM, fp); 
  fclose( fp );
  #endif  
  
  fprintf( stdout, "\n\nMatrix transpose time block V1: %0.3g\n", t2 - t1 );
  //fprintf( stdout, "%0.3g\n", t2 - t1 );

    t1 = second();
  
  /* Implement loops over the blocks of the main Matrices while transposing internally to the cache block */
  // for each block
  //#pragma omp parallel for private(ib, jb, i, j)
  for (ib = 0; ib < MATRIXDIM; ib += BLOCKSIZE){
    for (jb = 0; jb < MATRIXDIM; jb += BLOCKSIZE){
      for (i = ib; i < ib + BLOCKSIZE; ++i) {
	for (j = jb; j < jb + BLOCKSIZE; ++j) {
	  AT[i + j*MATRIXDIM] = A[j + i*MATRIXDIM];
	}
      }
    }
  }

  t2 = second();
  check(A, AT, MATRIXDIM);
  
  #ifdef DEBUG
  fp = fopen( "transpose.out", "w+b" );
  fwrite( AT, sizeof(double), MATRIXDIM * MATRIXDIM, fp); 
  fclose( fp );
  #endif  
  
  fprintf( stdout, "\n\nMatrix transpose time block V2: %0.3g\n", t2 - t1 );
  //fprintf( stdout, "%0.3g\n", t2 - t1 );

  //print(A, MATRIXDIM);
  //print(AT, MATRIXDIM);

  free( A );
  free( AT );
  
  return 0;
}
  
void print(double *M, int SIZE) {
  int ii, jj;
  printf("-----------------------------\n");
  for (ii = 0; ii < SIZE; ++ii){
    for (jj = 0; jj < SIZE; ++jj){
      printf("%g ", M[get_idx(ii, jj, SIZE)]);
    }
    printf("\n");
  }
  printf("-----------------------------\n");
}

void check(double * M, double * MT, int SIZE) {
  int ii, jj;
  double diff = 0.0;
  for (ii = 0; ii < SIZE; ++ii){
    for (jj = 0; jj < SIZE; ++jj){
      diff += fabs(M[ii*SIZE + jj] - MT[jj*SIZE + ii]);
    }
  }
  printf("---------   diff = %.5le   --------------------\n", diff);
}

 
