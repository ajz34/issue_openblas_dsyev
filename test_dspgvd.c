#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>

extern int dspgvd_(
    int *itype, char *jobz, char *uplo,
    int *n, double *ap, double *bp,
    double *w, double *z, int *ldz,
    double *work, int* lwork, int* iwork, int* liwork,
    int *info);

int main() {
    int itype = 1;
    char jobz = 'V';
    char uplo = 'U';
    int n = 2048;
    int np = n * (n + 1) / 2;
    int ldz = n;
    int lwork = -1;
    int liwork = -1;
    int info = 0;

    double* ap = (double*) malloc(sizeof(double) * np);
    double* bp = (double*) malloc(sizeof(double) * np);
    double* w = (double*) malloc(sizeof(double) * n);
    double* z = (double*) malloc(sizeof(double) * n * n);
    double* work = (double*) malloc(sizeof(double) * 1);
    int* iwork = (int*) malloc(sizeof(int) * 1);

    // https://math.stackexchange.com/a/358092
    // symm(b) + n * eye(n) where |b[*]| < 1
    int itp = 0;
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i <= j; ++i) {
            bp[itp] = (i + j) % 456 / 456;
            if (i == j) bp[itp] += n;
            itp += 1;
        }
    }

    for (int i = 0; i < np; ++i) {
        ap[i] = i % 123;
    }

    dspgvd_(&itype, &jobz, &uplo, &n, ap, bp, w, z, &ldz, work, &lwork, iwork, &liwork, &info);
    lwork = (int) work[0];
    liwork = (int) iwork[0];
    printf("test_dsyevd, lwork = %d\n", lwork);
    printf("test_dsyevd, liwork = %d\n", liwork);
    
    free(work); work = (double*) malloc(sizeof(double) * lwork);
    free(iwork); iwork = (int*) malloc(sizeof(int) * liwork);

    struct timeval t1, t2;
    clock_t c1, c2;
    double elapsed_time;
    double cpu_time;
    int repeat = 10;
    
    gettimeofday(&t1, NULL);
    c1 = clock();

    for (int i = 0; i < repeat; ++i) {
        dspgvd_(&itype, &jobz, &uplo, &n, ap, bp, w, z, &ldz, work, &lwork, iwork, &liwork, &info);
    }

    gettimeofday(&t2, NULL);
    c2 = clock();
    
    elapsed_time = (t2.tv_sec - t1.tv_sec) * 1000.0 / (double) repeat;
    elapsed_time += (t2.tv_usec - t1.tv_usec) / 1000.0 / (double) repeat;
    cpu_time = ((double) (c2 - c1)) / CLOCKS_PER_SEC * 1000.0 / (double) repeat;
    printf("test_dspgvd, elapsed time: %10.4f msec\n", elapsed_time);
    printf("test_dspgvd, CPU     time: %10.4f msec\n", cpu_time);
    printf("test_dspgvd, CPU    ratio: %10.4f\n", cpu_time / elapsed_time);
    printf("test_dspgvd, info = %d\n", info);
}
