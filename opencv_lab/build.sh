mkdir -p build && cd build
cmake ..
make && cd ..
cp -r build/DisplayImage DisplayImage
