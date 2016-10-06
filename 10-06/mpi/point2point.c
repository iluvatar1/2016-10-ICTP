#include <stdlib.h>
#include <stdio.h>

#include <mpi.h>

int main(int argc, char **argv)
{
  MPI_Init( &argc, &argv );
  
  int my_rank = 0, size = 0;
  MPI_Status status;

  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int val = 10; 
  if (0 == my_rank) {
    val = 10;
    MPI_Send(&val, 1, MPI_INT, 1, 99, MPI_COMM_WORLD); 
    MPI_Recv(&val, 1, MPI_INT, 1, 98, MPI_COMM_WORLD, &status);     
  } else if (1 == my_rank) {
    MPI_Recv(&val, 1, MPI_INT, 0, 99, MPI_COMM_WORLD, &status);
    val += 10;
    MPI_Send(&val, 1, MPI_INT, 0, 98, MPI_COMM_WORLD);     
  }

  if (0 == my_rank) {
    printf("Val =  %d , at rank == 0\n", val);
  }

  MPI_Finalize();

  return 0;
}
