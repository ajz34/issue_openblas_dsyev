export VER="0.3.27"
export ROOT_DIR=`pwd`
export BLAS_DIR=$ROOT_DIR/OpenBLAS
export PATH=/usr/bin:$PATH

export LD_LIBRARY_PATH=$BLAS_DIR/lib:$LD_LIBRARY_PATH
export OMP_NUM_THREADS=2

# build
gcc test_dsyev.c  -fopenmp -o test_dsyev.out  -O3 -lopenblas -L$BLAS_DIR/lib
gcc test_dsyevd.c -fopenmp -o test_dsyevd.out -O3 -lopenblas -L$BLAS_DIR/lib
gcc test_dsyevr.c -fopenmp -o test_dsyevr.out -O3 -lopenblas -L$BLAS_DIR/lib
gcc test_dsyevx.c -fopenmp -o test_dsyevx.out -O3 -lopenblas -L$BLAS_DIR/lib

# test
./test_dsyev.out
./test_dsyevd.out
./test_dsyevr.out
./test_dsyevx.out

