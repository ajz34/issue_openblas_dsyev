export VER="0.3.27"
export ROOT_DIR=`pwd`
export BLAS_DIR=$ROOT_DIR/OpenBLAS
export PATH=/usr/bin:$PATH

# download openblas
wget https://github.com/OpenMathLib/OpenBLAS/releases/download/v$VER/OpenBLAS-$VER.tar.gz OpenBLAS-$VER.tar.gz
rm -r $BLAS_DIR
mkdir $BLAS_DIR
tar -xf OpenBLAS-$VER.tar.gz -C $BLAS_DIR
mv $BLAS_DIR/OpenBLAS-$VER/* $BLAS_DIR
rm -r $BLAS_DIR/OpenBLAS-$VER

# build and install openblas
cd $BLAS_DIR
make CC=gcc FC=gfortran USE_OPENMP=1 NUM_THREADS=2 -j4
make install PREFIX=$BLAS_DIR

