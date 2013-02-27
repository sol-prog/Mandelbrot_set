#ifndef WINDOW__H
#define WINDOW__H

template <typename T>
class window {
	T _x_min, _x_max, _y_min, _y_max;

public:
	window(T x_min, T x_max, T y_min, T y_max)
	: _x_min(x_min), _x_max(x_max), _y_min(y_min), _y_max(y_max)
	{}

// Utility functions for getting the size, width and height of the window
	T size() {
		return (width() * height());
	}

	T width() {
		return (_x_max - _x_min);
	}

	T height() {
		return (_y_max - _y_min);
	}

// Getters and setters for the window elements
	T x_min() {
		return _x_min;
	}

	void x_min(T x_min) {
		_x_min = x_min;
	}	

	T x_max() {
		return _x_max;
	}

	void x_max(T x_max) {
		_x_max = x_max;
	}		

	T y_min() {
		return _y_min;
	}

	void y_min(T y_min) {
		_y_min = y_min;
	}		

	T y_max() {
		return _y_max;
	}

	void y_max(T y_max) {
		_y_max = y_max;
	}

// Reset all values
	void reset(T x_min, T x_max, T y_min, T y_max) {
		_x_min = x_min;
		_x_max = x_max;
		_y_min = y_min;
		_y_max = y_max;
	}
};
#endif

