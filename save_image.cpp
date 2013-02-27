#include <tuple>
#include <iostream>

#include <FreeImage.h>
#include "window.h"
#include "save_image.h"

std::tuple<int, int, int> get_rgb_piecewise_linear(int n, int iter_max) {
	int N = 256; // colors per element
	int N3 = N * N * N;
	// map n on the 0..1 interval (real numbers)
	double t = (double)n/(double)iter_max;
	// expand n on the 0 .. 256^3 interval (integers)
	n = (int)(t * (double) N3);

	int b = n/(N * N);
	int nn = n - b * N * N;
	int r = nn/N;
	int g = nn - r * N;
	return std::tuple<int, int, int>(r, g, b);
}

std::tuple<int, int, int> get_rgb_smooth(int n, int iter_max) {
	// map n on the 0..1 interval
	double t = (double)n/(double)iter_max;

	// Use smooth polynomials for r, g, b
	int r = (int)(9*(1-t)*t*t*t*255);
	int g = (int)(15*(1-t)*(1-t)*t*t*255);
	int b =  (int)(8.5*(1-t)*(1-t)*(1-t)*t*255);	
	return std::tuple<int, int, int>(r, g, b);
}


void plot(window<int> &scr, std::vector<int> &colors, int iter_max, const char *fname, bool smooth_color) {
	// active only for static linking
	#ifdef FREEIMAGE_LIB
		FreeImage_Initialise();
	#endif

	unsigned int width = scr.width(), height = scr.height();
	FIBITMAP *bitmap = FreeImage_Allocate(width, height, 32); // RGBA

	int k = 0;
	std::tuple<int, int, int> rgb;
	for(int i = scr.y_min(); i < scr.y_max(); ++i) {
		for(int j = scr.x_min(); j < scr.x_max(); ++j) {
			int n = colors[k];

			if( !smooth_color ) {
				rgb = get_rgb_piecewise_linear(n, iter_max);
			}
			else {
				rgb = get_rgb_smooth(n, iter_max);
			}

			RGBQUAD col;
			col.rgbRed = std::get<0>(rgb);
			col.rgbGreen = std::get<1>(rgb);
			col.rgbBlue = std::get<2>(rgb);
			col.rgbReserved = 255;

			FreeImage_SetPixelColor(bitmap, j, i, &col);
			k++;
		}
	}

	// Save the image in a PNG file
	FreeImage_Save(FIF_PNG, bitmap, fname, PNG_DEFAULT);

	// Clean bitmap;
	FreeImage_Unload(bitmap);

	// active only for static linking
	#ifdef FREEIMAGE_LIB
		FreeImage_DeInitialise();
	#endif
}
