#include <stdlib.h>

/* sum up absolute of "*num" integers in array "in", store result in address at "sum" */
void sum_abs_(int *in, int *num, int *sum) {
   int i,n,s;

   /* sanity check */
   if ((num == NULL) || (sum == NULL)) return;

   n = *num;
   for (i=0,s=0; i < n; ++i) { 
       s += abs(in[i]); 
   }
   *sum = s;
}
 
