export VER="0.3.27"
export ROOT_DIR=`pwd`
export BLAS_DIR=$ROOT_DIR/OpenBLAS-cmake
export PATH=/usr/bin:$PATH

export LD_LIBRARY_PATH=$BLAS_DIR/lib:$LD_LIBRARY_PATH
export OMP_NUM_THREADS=2

# build
for func in config dgemm dsyrk dsyev dsyevd dsyevr dsyevx dspgv dspgvd dspgvx
do
    gcc test_$func.c -fopenmp -o test_$func -O3 -lopenblas -L$BLAS_DIR/lib
done

# test
for func in config dgemm dsyrk dsyev dsyevd dsyevr dsyevx dspgv dspgvd dspgvx
do
    ./test_$func
done

