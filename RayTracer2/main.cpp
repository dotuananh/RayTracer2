#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;

//------------------------------------------------------------------------------
// Define a structure to store RGB component of a color
//------------------------------------------------------------------------------
typedef struct _RGBType {
  double r;
  double g;
  double b;
}RGBType;

//------------------------------------------------------------------------------
// Save the result to a BMP file
//------------------------------------------------------------------------------
void saveBMP(const char* fileName, int w, int h, int dpi, RGBType* data) {
  FILE* f;
  int k = w * h;
  int s = 4 * k;
  int fileSize = 54 + s;

  double factor = 39.375;
  int m = static_cast<int>(factor);
  int ppm = dpi * m;

  unsigned char bmpFileHeader[14] = {
    'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
  unsigned char bmpInfoHeader[40] = {
    40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};

  bmpFileHeader[2] = (unsigned char)(fileSize);
  bmpFileHeader[3] = (unsigned char)(fileSize>>8);
  bmpFileHeader[4] = (unsigned char)(fileSize>>16);
  bmpFileHeader[5] = (unsigned char)(fileSize>>24);

  bmpInfoHeader[4] = (unsigned char)(w);
  bmpInfoHeader[5] = (unsigned char)(w>>8);
  bmpInfoHeader[6] = (unsigned char)(w>>16);
  bmpInfoHeader[7] = (unsigned char)(w>>24);

  bmpInfoHeader[8] = (unsigned char)(h);
  bmpInfoHeader[9] = (unsigned char)(h>>8);
  bmpInfoHeader[10] = (unsigned char)(h>>16);
  bmpInfoHeader[11] = (unsigned char)(h>>24);

  bmpInfoHeader[21] = (unsigned char)(s);
  bmpInfoHeader[22] = (unsigned char)(s>>8);
  bmpInfoHeader[23] = (unsigned char)(s>>16);
  bmpInfoHeader[24] = (unsigned char)(s>>24);

  bmpInfoHeader[25] = (unsigned char)(ppm);
  bmpInfoHeader[26] = (unsigned char)(ppm>>8);
  bmpInfoHeader[27] = (unsigned char)(ppm>>16);
  bmpInfoHeader[28] = (unsigned char)(ppm>>24);


  bmpInfoHeader[29] = (unsigned char)(ppm);
  bmpInfoHeader[30] = (unsigned char)(ppm>>8);
  bmpInfoHeader[31] = (unsigned char)(ppm>>16);
  bmpInfoHeader[32] = (unsigned char)(ppm>>24);

  f = fopen(fileName, "wb");

  fwrite(bmpFileHeader, 1, 14, f);
  fwrite(bmpInfoHeader, 1, 40, f);

  for (int  i = 0; i < k; i++) {
    RGBType rgb = data[i];

    double red = (data[i].r)*255;
    double green = (data[i].g)*255;
    double blue = (data[i].b)*255;

    unsigned char color[3] = {
      (int)floor(blue), (int)floor(green), (int)floor(red)};

    fwrite(color, 1, 3, f);
  }

  fclose(f);
}

//------------------------------------------------------------------------------
// Main function
//------------------------------------------------------------------------------
int main(int argc, char* argv) {
  cout << "Rendering..." << endl;

  // The dimension of the rendering picture
  int dpi = 72;
  int width = 640;
  int height = 480;
  int n = width * height;
  int currentIndex;

  RGBType* pixels = new RGBType[n];

  // Loop through each pixel and compute the color we should display
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      // return color
      currentIndex = y * width + x;

      if ((x > 200) && (x < 440) && (y > 200) && (y < 280)) {
        pixels[currentIndex].r = 23;
        pixels[currentIndex].g = 222;
        pixels[currentIndex].b = 10;
      }
      else
      {
        pixels[currentIndex].r = 0;
        pixels[currentIndex].r = 0;
        pixels[currentIndex].r = 0;
      }
    }
  }

  saveBMP("scene.bmp", width, height, dpi, pixels);
  return 0;
}
