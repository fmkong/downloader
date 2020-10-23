mkdir -p build
cd build
rm -rf *
cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/linux.cmake
make -j8
cd ..