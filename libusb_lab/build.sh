mkdir -p build && cd build
cmake ..
make && cd ..
cp -r build/usb_info usb_info
