#include<stdio.h>

extern int openblas_get_num_threads(void);
extern char* openblas_get_config(void);
extern char* openblas_get_corename(void);
extern int openblas_get_parallel(void);

int main() {
    printf("openblas_get_num_threads  %3d\n", openblas_get_num_threads());
    switch (openblas_get_parallel()) {
    case 0:
        printf("openblas_get_parallel     Serial\n"); break;
    case 1:
        printf("openblas_get_parallel     Thread\n"); break;
    case 2:
        printf("openblas_get_parallel     OpenMP\n"); break;
    }
    printf("openblas_get_corename     %s\n", openblas_get_corename());
    printf("openblas_get_config       %s\n", openblas_get_config());
}


