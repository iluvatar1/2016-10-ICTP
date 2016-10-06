#include <stdlib.h>
#include <stdio.h>

#include <mpi.h>

int main(int argc, char **argv)
{
  MPI_Init( &argc, &argv );
  
  int my_rank = 0, size = 0;
  int err;

  err = MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  err = MPI_Comm_size(MPI_COMM_WORLD, &size);

  printf("I am %d out of %d processess!!\n", my_rank, size);

  MPI_Finalize();

  return 0;
}
