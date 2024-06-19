export VER="2024.1"
export ROOT_DIR=`pwd`
export BLAS_DIR=$ROOT_DIR/OneMKL/mkl/$VER
export PATH=/usr/bin:$PATH

export LD_LIBRARY_PATH=$BLAS_DIR/lib:$LD_LIBRARY_PATH
export OMP_NUM_THREADS=2

# build
gcc test_dsyev.c  -o test_dsyev  -fopenmp -O3 -L$BLAS_DIR/lib -Wl,--no-as-needed -lmkl_intel_lp64 -lmkl_gnu_thread -lmkl_core -lgomp -lpthread -lm -ldl
gcc test_dsyevd.c -o test_dsyevd -fopenmp -O3 -L$BLAS_DIR/lib -Wl,--no-as-needed -lmkl_intel_lp64 -lmkl_gnu_thread -lmkl_core -lgomp -lpthread -lm -ldl
gcc test_dsyevr.c -o test_dsyevr -fopenmp -O3 -L$BLAS_DIR/lib -Wl,--no-as-needed -lmkl_intel_lp64 -lmkl_gnu_thread -lmkl_core -lgomp -lpthread -lm -ldl
gcc test_dsyevx.c -o test_dsyevx -fopenmp -O3 -L$BLAS_DIR/lib -Wl,--no-as-needed -lmkl_intel_lp64 -lmkl_gnu_thread -lmkl_core -lgomp -lpthread -lm -ldl

# test
./test_dsyev
./test_dsyevd
./test_dsyevr
./test_dsyevx

