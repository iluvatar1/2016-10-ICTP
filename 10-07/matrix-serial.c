#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  if (2 != argc) {
    printf("ERROR: Call this as : ./program matrix_column_size\n ");
    fflush(stdout);
    exit(1);
  }
  const int SIZE = atoi(argv[1]);
  
  FILE *fp = fopen("matrix-serial.out", "w+b");
  
  int ii, jj;
  double * vals = malloc(SIZE*sizeof(double));
  for (jj = 0; jj < SIZE; ++jj) {
    vals[jj] = 0.0;
  }
  for (jj = 0; jj < SIZE; ++jj) {
    vals[jj] = 1.0;
    fwrite( vals, sizeof(double), SIZE, fp ); 
    vals[jj] = 0.0;
  }
  fclose(fp);
  
  printf("DONE. Check file matrix-serial.out \n ");

  return 0;
}

