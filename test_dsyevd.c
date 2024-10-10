#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

extern int dsyevd_(char *jobz, char *uplo, int *n, double *a,
    int *lda, double *w, double *work, int *lwork, 
    int *iwork, int *liwork, int *info);

int main() {
    char jobz = 'V';
    char uplo = 'U';
    int n = 2048;
    int lda = n;
    int lwork = -1;
    int liwork = -1;
    int info = 0;

    double* a = (double*) malloc(sizeof(double) * n * n);
    double* w = (double*) malloc(sizeof(double) * n);
    double* work = (double*) malloc(sizeof(double) * 1);
    int* iwork = (int*) malloc(sizeof(int) * 1);

    dsyevd_(&jobz, &uplo, &n, a, &lda, w, work, &lwork, iwork, &liwork, &info);
    lwork = (int) work[0];
    liwork = (int) iwork[0];
    printf("test_dsyevd, lwork = %d\n", lwork);
    printf("test_dsyevd, liwork = %d\n", liwork);
    
    free(work); work = (double*) malloc(sizeof(double) * lwork);
    free(iwork); iwork = (int*) malloc(sizeof(int) * liwork);
    
    // srand(0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // a[i * n + j] = (double) rand() / (double) RAND_MAX;
            a[i * n + j] = i * n + j;
        }
    }

    struct timeval t1, t2;
    clock_t c1, c2;
    double elapsed_time;
    double cpu_time;
    int repeat = 3;
    
    gettimeofday(&t1, NULL);
    c1 = clock();

    for (int i = 0; i < repeat; ++i) {
        dsyevd_(&jobz, &uplo, &n, a, &lda, w, work, &lwork, iwork, &liwork, &info);
    }

    gettimeofday(&t2, NULL);
    c2 = clock();
    
    elapsed_time = (t2.tv_sec - t1.tv_sec) * 1000.0 / (double) repeat;
    elapsed_time += (t2.tv_usec - t1.tv_usec) / 1000.0 / (double) repeat;
    cpu_time = ((double) (c2 - c1)) / CLOCKS_PER_SEC * 1000.0 / (double) repeat;
    printf("test_dsyevd, elapsed time: %10.4f msec\n", elapsed_time);
    printf("test_dsyevd, CPU     time: %10.4f msec\n", cpu_time);
    printf("test_dsyevd, CPU    ratio: %10.4f\n", cpu_time / elapsed_time);
    printf("test_dsyevd, info = %d\n", info);
}
