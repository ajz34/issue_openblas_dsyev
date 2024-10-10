#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

extern void dspgvx_(
    int* itype, char* jobz, char* range, char* uplo,
    int* n, double* ap, double* bp,
    double* vl, double* vu, int* il, int* iu,
    double* abstol,
    int* m, double* w, double* z, int* ldz,
    double* work, int* iwork,
    int* ifail, int* info);

int main() {
    int itype = 1;
    char jobz = 'V';
    char range = 'I';
    char uplo = 'U';
    int n = 2048;
    int np = n * (n + 1) / 2;
    double vl = -1;
    double vu = -1;
    int il = 1;
    int iu = 256;
    double abstol = 1e-16;
    int m = -1;
    int ldz = n;
    int info = 0;

    double* ap = (double*) malloc(sizeof(double) * np);
    double* bp = (double*) malloc(sizeof(double) * np);
    double* w = (double*) malloc(sizeof(double) * n);
    double* z = (double*) malloc(sizeof(double) * n * n);
    int* isuppz = (int*) malloc(sizeof(int) * 2 * n);
    double* work = (double*) malloc(sizeof(double) * 8 * n);
    int* iwork = (int*) malloc(sizeof(int) * 5 * n);
    int* ifail = (int*) malloc(sizeof(int) * n);

    printf("test_dspgvx\n");

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

    struct timeval t1, t2;
    clock_t c1, c2;
    double elapsed_time;
    double cpu_time;
    int repeat = 3;
    
    gettimeofday(&t1, NULL);
    c1 = clock();

    for (int i = 0; i < repeat; ++i) {
        dspgvx_(
            &itype, &jobz, &range, &uplo,
            &n, ap, bp,
            &vl, &vu, &il, &iu,
            &abstol,
            &m, w, z, &ldz,
            work, iwork, ifail, &info);
    }

    gettimeofday(&t2, NULL);
    c2 = clock();
    
    elapsed_time = (t2.tv_sec - t1.tv_sec) * 1000.0 / (double) repeat;
    elapsed_time += (t2.tv_usec - t1.tv_usec) / 1000.0 / (double) repeat;
    cpu_time = ((double) (c2 - c1)) / CLOCKS_PER_SEC * 1000.0 / (double) repeat;
    printf("test_dspgvx, elapsed time: %10.4f msec\n", elapsed_time);
    printf("test_dspgvx, CPU     time: %10.4f msec\n", cpu_time);
    printf("test_dspgvx, CPU    ratio: %10.4f\n", cpu_time / elapsed_time);
    printf("test_dspgvx, info = %d\n", info);
}
