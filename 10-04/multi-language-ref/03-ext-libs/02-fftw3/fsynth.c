/* fourier synthesis code example in C */

#include <stdio.h>
#include <math.h>

#include "utilities.h"

static const double TWOPI=6.28318530717958647688;

static void write_fsynth(char *fname, double *freq, double *phase,
                         double *intens, int fnum, int tnum, double tmax)
{
    int i,j;
    double tdelta,t,val;
    FILE *fp;

    tdelta = tmax / (double)tnum;

    fp = fopen(fname,"w");
    fprintf(fp,"# %d\n", tnum);

    for (i=0; i < tnum; ++i) {
        t = ((double) i) * tdelta;
        val = 0.0;

        for (j=0; j < fnum; ++j) {
            val += intens[j]*sin(TWOPI*(freq[j]*t+phase[j]));
        }
        fprintf(fp,"%lg %lg\n", t, val);
    }
    fclose(fp);
}

#define FMAX 20

int main(int argc, char **argv)
{
    int fnum, tnum, i;
    double freq[FMAX],phase[FMAX],intens[FMAX],tmax;
    char line[256],fname[81];

    printf("fourier synthesis\n");
    printf("give number of frequencies\n");
    fgets(line,255,stdin);
    sscanf(line,"%d",&fnum);
    printf("got: %d\n",fnum);

    if ((fnum < 1) || (fnum > FMAX)) {
        printf("only 1-%d fequencies are supported\n",FMAX);
        return 1;
    }

    for (i=0; i < fnum; ++i) {
        printf("frequency number: %d\n",i);
        printf("give frequency, intensity and phase:\n");
        fgets(line,255,stdin);
        sscanf(line,"%lg%lg%lg",&freq[i],&intens[i],&phase[i]);
        printf("got: %lg %lg %lg\n",freq[i],intens[i],phase[i]);
    }
       
    printf("give total time\n");
    fgets(line,255,stdin);
    sscanf(line,"%lg",&tmax);
    printf("got: %lg\n",tmax);

    printf("give number of intervals\n");
    fgets(line,255,stdin);
    sscanf(line,"%d",&tnum);
    printf("got: %d\n",tnum);

    printf("give filename\n");
    fgets(line,255,stdin);
    sscanf(line,"%s",fname);
    printf("got: %s\n",fname);

    printf("generating output\n");
    start_timer();
    write_fsynth(fname,freq,phase,intens,fnum,tnum,tmax);
    printf("time for generating output: %g seconds\n",
	   get_timer());

#if 0
    init_random(123455);
    for (i=0; i < 20; ++i)
      printf("%d: %12.8f\n", i, get_random());
#endif

    return 0;
}


