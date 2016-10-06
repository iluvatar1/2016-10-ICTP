#include <stdio.h>
#include <omp.h>

int main(void)
{
  printf("Starting off in the sequential world\n");

  //omp_set_num_threads(3);
  #pragma omp parallel
  {
    printf("Hello from thread number %d\n", omp_get_thread_num());
  }

  printf("Back to the sequential world\n");

  return 0;
}
