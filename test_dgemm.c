#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

extern int dgemm_(
    char* transa, char* transb,
    int* m, int* n, int* k,
    double* alpha, double* a, int* lda,
    double* b, int* ldb,
    double* beta, double* c, int* ldc);

int main() {
    char transa = 'N';
    char transb = 'N';
    int n = 2048;
    double alpha = 1.0;
    double beta = 0.0;

    double* a = (double*) malloc(sizeof(double) * n * n);
    double* b = (double*) malloc(sizeof(double) * n * n);
    double* c = (double*) malloc(sizeof(double) * n * n);
    
    printf("test_dgemm\n");
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i * n + j] = i * n + j;
            b[i * n + j] = j * n + i;
        }
    }

    struct timeval t1, t2;
    clock_t c1, c2;
    double elapsed_time;
    double cpu_time;
    int repeat = 100;
    
    gettimeofday(&t1, NULL);
    c1 = clock();

    for (int i = 0; i < repeat; ++i) {
        dgemm_(&transa, &transb, &n, &n, &n, &alpha, a, &n, b, &n, &beta, c, &n);
    }

    gettimeofday(&t2, NULL);
    c2 = clock();
    
    elapsed_time = (t2.tv_sec - t1.tv_sec) * 1000.0 / (double) repeat;
    elapsed_time += (t2.tv_usec - t1.tv_usec) / 1000.0 / (double) repeat;
    cpu_time = ((double) (c2 - c1)) / CLOCKS_PER_SEC * 1000.0 / (double) repeat;
    printf("test_dgemm, elapsed time: %10.4f msec\n", elapsed_time);
    printf("test_dgemm, CPU     time: %10.4f msec\n", cpu_time);
    printf("test_dgemm, CPU    ratio: %10.4f\n", cpu_time / elapsed_time);
}
