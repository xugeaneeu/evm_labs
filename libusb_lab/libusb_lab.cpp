#include <iostream>
#include <libusb.h>
#include <stdio.h>

using namespace std;

void print_device_info(libusb_device *device);

int main() {
  libusb_device **devices;
  libusb_context *ctx = nullptr;
  int result;
  ssize_t device_count;
  result = libusb_init(&ctx);
  
  if (result < 0) {
    cerr << "Error initializing libusb: " << result << endl;
    return 1;
  }
  
  device_count = libusb_get_device_list(ctx, &devices);
  if (device_count < 0) {
    cerr << "Error while retrieving the device list." << endl;
    return 1;
  }
  cout << "Number of connected devices: " << device_count << endl;
  
  for (ssize_t i = 0; i < device_count; i++) {
    print_device_info(devices[i]);
  }
  
  libusb_free_device_list(devices, 1);
  libusb_exit(ctx);
  return 0;
}

void print_device_info(libusb_device *device) {
  libusb_device_descriptor desc;
  libusb_config_descriptor *config;
  
  int result = libusb_get_device_descriptor(device, &desc);
  if (result < 0) {
    cerr << "Error receiving a device descriptor: " << result << endl;
    return;
  }
  
  libusb_get_config_descriptor(device, 0, &config);
  cout << "Device class code: " << static_cast<int>(desc.bDeviceClass) << endl;
  cout << "ProductID: " << desc.idProduct << endl;
  cout << "Manufacturer ID: " << desc.idVendor << endl;
  libusb_device_handle *handle;
  result = libusb_open(device, &handle);
  if (result == 0) {
    unsigned char buffer[256];
    if (desc.iSerialNumber > 0) { 
      libusb_get_string_descriptor_ascii(
          handle, desc.iSerialNumber,
          buffer, sizeof(buffer) );
      cout << "Serial number: " << buffer << endl;
    }else {
      cout << "Serial number: Not available" << endl;
    }
    if (desc.iProduct > 0) {
      libusb_get_string_descriptor_ascii(
          handle, desc.iProduct, buffer,
          sizeof(buffer));
      cout << "Product Name: " << buffer << endl;
    }else {
      cout << "Product name: Not available" << endl;
    }
  }
  cout << "--------------------------------" << endl;
}
