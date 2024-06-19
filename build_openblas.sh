export VER="0.3.27"
export ROOT_DIR=`pwd`
export BLAS_DIR=$ROOT_DIR/OpenBLAS
export PATH=/usr/bin:$PATH

# download openblas
# wget https://github.com/OpenMathLib/OpenBLAS/releases/download/v$VER/OpenBLAS-$VER.tar.gz OpenBLAS-$VER.tar.gz
rm -r OpenBLAS-$VER
tar -xf OpenBLAS-$VER.tar.gz

# build and install openblas
cd OpenBLAS-$VER
make CC=gcc FC=gfortran \
    TARGET=ZEN USE_64BITINT=1 DYNAMIC_ARCH=1 NO_CBLAS=0 NO_LAPACK=0 NO_LAPACKE=0\
    NO_AFFINITY=1 USE_OPENMP=1 MAX_THREADS=16 -j32
make install PREFIX=$BLAS_DIR

