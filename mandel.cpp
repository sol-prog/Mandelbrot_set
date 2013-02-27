#include <iostream>
#include <complex>
#include <vector>
#include <chrono>

#include "window.h"
#include "save_image.h"
#include "utils.h"

// clang++ -std=c++11 -stdlib=libc++ -O3 save_image.cpp utils.cpp mandel.cpp -lfreeimage

// Convert a pixel coordinate to the complex domain
std::complex<double> scale(window<int> &scr, window<double> &fr, std::complex<double> c) {
	std::complex<double> aux(c.real() / (double)scr.width() * fr.width() + fr.x_min(),
		c.imag() / (double)scr.height() * fr.height() + fr.y_min());
	return aux;
}

// Check if a point is in the set or escapes to infinity, return the number if iterations
int escape(std::complex<double> c, int iter_max, const std::function<std::complex<double>(std::complex<double>, 
	std::complex<double>)> &func) {
	std::complex<double> z(0);
	int iter = 0;

	while (abs(z) < 2.0 && iter < iter_max) {
		z = func(z, c);
		iter++;
	}

	return iter;
}

// Loop over each pixel from our image and check if the points associated with this pixel escape to infinity
void get_number_iterations(window<int> &scr, window<double> &fract, int iter_max, std::vector<int> &colors,
	const std::function<std::complex<double>(std::complex<double>, std::complex<double>)> &func) {
	int k = 0;
	for(int i = scr.y_min(); i < scr.y_max(); ++i) {
		for(int j = scr.x_min(); j < scr.x_max(); ++j) {
			std::complex<double> c((double)j, (double)i);
			c = scale(scr, fract, c);
			colors[k] = escape(c, iter_max, func);
			k++;
		}
	}
}

void fractal(window<int> &scr, window<double> &fract, int iter_max, std::vector<int> &colors,
	const std::function<std::complex<double>(std::complex<double>, std::complex<double>)> &func,
	const char *fname, bool smooth_color) {
	auto start = std::chrono::steady_clock::now();
	get_number_iterations(scr, fract, iter_max, colors, func);
	auto end = std::chrono::steady_clock::now();
	std::cout << "Time to generate " << fname << " = " << std::chrono::duration <double, std::milli> (end - start).count() << " [ms]" << std::endl;

	// Save (show) the result as an image
	plot(scr, colors, iter_max, fname, smooth_color);
}

void mandelbrot() {
	// Define the size of the image
	window<int> scr(0, 1200, 0, 1200);
	// The domain in which we test for points
	window<double> fract(-2.2, 1.2, -1.7, 1.7);

	// The function used to calculate the fractal
	auto func = [] (std::complex <double> z, std::complex<double> c) -> std::complex<double> {return z * z + c; };

	int iter_max = 500;
	const char *fname = "mandelbrot.png";
	bool smooth_color = true;
	std::vector<int> colors(scr.size());

	// Experimental zoom (bugs ?). This will modify the fract window (the domain in which we calculate the fractal function) 
	//zoom(1.0, -1.225, -1.22, 0.15, 0.16, fract); //Z2
	
	fractal(scr, fract, iter_max, colors, func, fname, smooth_color);
}

void triple_mandelbrot() {
	// Define the size of the image
	window<int> scr(0, 1200, 0, 1200);
	// The domain in which we test for points
	window<double> fract(-1.5, 1.5, -1.5, 1.5);

	// The function used to calculate the fractal
	auto func = [] (std::complex <double> z, std::complex<double> c) -> std::complex<double> {return z * z * z + c; };

	int iter_max = 500;
	const char *fname = "triple_mandelbrot.png";
	bool smooth_color = true;
	std::vector<int> colors(scr.size());

	fractal(scr, fract, iter_max, colors, func, fname, smooth_color);
}

int main() {

	mandelbrot();
	triple_mandelbrot();

	return 0;
}
