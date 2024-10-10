export VER="0.3.27"
export ROOT_DIR=`pwd`
export BLAS_DIR=$ROOT_DIR/OpenBLAS-cmake
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
mkdir build
cd build
cmake .. -DBUILD_SHARED_LIBS=1 -DUSE_OPENMP=1 -DNO_AFFINITY=1 -DCMAKE_C_FLAGS="-O2" -DCMAKE_INSTALL_PREFIX=$BLAS_DIR
make -j32
make install

