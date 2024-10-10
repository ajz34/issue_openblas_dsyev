export VER="0.3.28"
export ROOT_DIR=`pwd`
export BLAS_DIR=$ROOT_DIR/OpenBLAS-$VER-fflags
export PATH=/usr/bin:$PATH

export LD_LIBRARY_PATH=$BLAS_DIR/lib:$LD_LIBRARY_PATH
export OMP_NUM_THREADS=16

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

