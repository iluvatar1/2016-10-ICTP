
#include <iostream>
#include <iomanip>

using namespace std;

/* prototypes for fortran 77 interface to BLAS */
extern "C" double ddot_(int *, double *, int *, double *, int *);
extern "C" void   dgemv_(char *, int *, int *, double *, double *, int *,
                         double *, int *, double *, double *, int *);


static void printvec(double *vector, int length)
{
    for (int i=0; i < length; ++i)
        cout << setw(4) << i+1 << "   " << setw(6) << vector[i] << endl;
}

int main(int, char *[])
{
    int i;
    double avec[4], bvec[4], cvec[4], amat[4][4];
    double a, b;
    
    avec[0] = 1.0;
    avec[1] = 2.0;
    avec[2] = 3.0;
    avec[3] = 4.0;

    bvec[3] = 1.0;
    bvec[2] = 2.0;
    bvec[1] = 3.0;
    bvec[0] = 4.0;

    cvec[0] = 1.0;
    cvec[1] = 1.0;
    cvec[2] = 1.0;
    cvec[3] = 1.0;

    for (i=0; i<4; ++i) {
        amat[i][0] = avec[i];
        amat[i][1] = bvec[i];
        amat[i][2] = cvec[i];
        amat[i][3] = avec[i];
    }

    printvec(amat[0],16);
    
    cout << "---" << endl;

    for (i=0; i<4; ++i) {
        amat[0][i] = avec[i];
        amat[1][i] = bvec[i];
        amat[2][i] = cvec[i];
        amat[3][i] = avec[i];
    }

    printvec(amat[0],16);

    for (i=0; i<4; ++i) {
        amat[i][0] = avec[i];
        amat[i][1] = bvec[i];
        amat[i][2] = cvec[i];
        amat[i][3] = avec[i];
    }

    cout << "---" << endl;

    int m,n,o;
    m = 4;
    n = 1;
    o = 1;

    a = ddot_(&m,avec,&n,bvec,&o);
    
    cout << a << endl;
    cout << "---" << endl;

    a = 1.0;
    b = 0.0;
    char trans = 'T';
    
    dgemv_(&trans,&m,&m,&a,amat[0],&m,bvec,&n,&b,cvec,&n);

    printvec(cvec,4);

    return 0;    
}
