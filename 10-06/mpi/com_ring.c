#include <stdlib.h>
#include <stdio.h>

#include <mpi.h>

int main(int argc, char **argv)
{
  MPI_Init( &argc, &argv );
  
  int my_rank = -1, size = -1;
  MPI_Request request;
  MPI_Status status;

  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int sum = 0, send_val = my_rank, recv_val = -1;
  
  while (my_rank != recv_val) {
    MPI_Isend(&send_val, 1, MPI_INT, (my_rank + size - 1)%size, 99, MPI_COMM_WORLD, &request);     
    MPI_Recv(&recv_val, 1, MPI_INT, (my_rank + 1)%size, 99, MPI_COMM_WORLD, &status);     
    sum += recv_val;
    send_val = recv_val;
    //printf("recv =  %d , at rank == %d\n", recv_val, my_rank);
  }
  printf("sum =  %d , at rank == %d\n", sum, my_rank);

  MPI_Finalize();

  return 0;
}
