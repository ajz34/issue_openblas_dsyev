export VER="2024.1"
export ROOT_DIR=`pwd`
export BLAS_DIR=$ROOT_DIR/OneMKL/mkl/$VER
export PATH=/usr/bin:$PATH

export LD_LIBRARY_PATH=$BLAS_DIR/lib:$LD_LIBRARY_PATH
export OMP_NUM_THREADS=16

# build
for func in dgemm dsyrk dsyev dsyevd dsyevr dsyevx dspgv dspgvd dspgvx
do
    gcc test_$func.c -o test_$func -fopenmp -O3 -L$BLAS_DIR/lib -Wl,--no-as-needed -lmkl_intel_lp64 -lmkl_gnu_thread -lmkl_core -lgomp -lpthread -lm -ldl
done

# test
for func in dgemm dsyrk dsyev dsyevd dsyevr dsyevx dspgv dspgvd dspgvx
do
    ./test_$func
done

