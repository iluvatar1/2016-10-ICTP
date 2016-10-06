
#include <stdio.h>

#define NUM 200

extern void sum_abs_(int *, int *, int *);

int main(int argc, char **argv)
{
    int data[NUM], sum, num, i;

    num = NUM;
    for (i=0; i < num; i++) {
        data[i] = i - 100 + 1;  /* NOTE: difference in array numbering */  
    }

    sum_abs_(data, &num, &sum);
    printf("sum=%d\n", sum);
    return 0;
}
