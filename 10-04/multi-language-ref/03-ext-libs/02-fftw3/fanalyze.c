
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fftw3.h>

#define LBUF 256

int main(int argc, char **argv)
{
    fftw_complex *signal, *freq;
    fftw_plan plan;
    double delta, norm, fnorm;
    int fnum, i;
    char line[LBUF];

    printf("# fourier analysis\n");
    fgets(line,LBUF,stdin);
    fnum = atoi(line+2);
    printf("# data set has %d elements\n", fnum);

    signal = (fftw_complex *)fftw_malloc(fnum*sizeof(fftw_complex));
    freq = (fftw_complex *)fftw_malloc(fnum*sizeof(fftw_complex));

    for (i = 0; i < fnum; ++i) {
        double a, b, c;
        if (fgets(line,LBUF,stdin) == NULL) {
            printf("short datafile\n");
            return 1;
        }
        sscanf(line,"%lf%lf",&a,&b);
        signal[i][0]=b;
        signal[i][1]=0.0;
        delta = a - c;
        c = a;
    }

    fnorm = 1.0/(delta*fnum);
    norm = 2.0/fnum;
    printf("# total time: %8.4f\n",delta*fnum);

    plan = fftw_plan_dft_1d(fnum,signal,freq,FFTW_FORWARD,FFTW_ESTIMATE);
    fftw_execute(plan);

    printf("# frequency intensity  phase\n");
    for (i = 0; i < fnum/2; ++i) {
        double a, b;

        /* magnitude */
        a = norm*sqrt(freq[i][0]*freq[i][0]+freq[i][1]*freq[i][1]);
        /* our definition of phase is shifted vs. what atan2() computes */
        b = 0.5*(atan2(freq[i][1],freq[i][0])/M_PI+0.5);
        if (b < 0.0) b += 1.0;
        if (a > 0.001) printf("%8.4f %8.4f %8.4f\n",i*fnorm,a,b); 
    }

    /* cleanup */
    fftw_destroy_plan(plan);
    fftw_free(signal);
    fftw_free(freq);
    return 0;
}

    
    
    
    


    
