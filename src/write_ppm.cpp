#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  assert(
    (num_channels == 3 || num_channels == 1 ) &&
    ".ppm only supports RGB or grayscale images");

  // creating ppm file
  // outline acquired from: https://en.wikipedia.org/wiki/Netpbm
  std::ofstream MyFile(filename);
  
  // if file cannot be created
  if (MyFile.fail()){
    return false;
  }

  // appropriate magic number
  if (num_channels == 3){
    MyFile << "P3" << std::endl;
  } else {
    MyFile << "P2" << std::endl;
  }
  MyFile << width << " " << height << std::endl;

  // maximum value for each colour
  MyFile << "255" << std::endl;

  // populate the file with colour values
  int pos = 0;
  for (int i = 0; i < height * width; i++){
    for (int j = 0; j < width, pos < data.size() - 3; j += 3){
      MyFile << (double) data[pos] << " "; 
      MyFile << (double) data[pos + 1] << " "; 
      MyFile << (double) data[pos + 2] << "  "; 
      pos += 3;
    }
    MyFile << std::endl;
  }
  MyFile.close();
  
  return true;
}
