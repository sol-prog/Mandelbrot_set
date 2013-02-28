Mandelbrot_set
==============

Here you could find the code for **The Mandelbrot set in C++11**, for more informations visit the project webpage:

http://solarianprogrammer.com/2013/02/28/mandelbroot-set-cpp-11/

In order to compile on your machine you'll need FreeImage installed. The code was tested with the latest stable Clang (from Xcode 4.6) and GCC 4.7.2. 

* If you have a Ubuntu (version 12.10 comes with GCC 4.7.2) machine with GCC 4.7.2 and libfreeimage-dev installed, you can compile the code with:

g++ -std=c++11 -O3 save_image.cpp utils.cpp mandel.cpp -lfreeimage

* If you use Ubuntu 12.04, the default GCC is 4.6.x. You can still compile the code by **commenting** any line that uses the <chrono> header, you need to do this only in mandel.cpp. You can compile the code with:

g++ -std=c++0x save_image.cpp utils.cpp mandel.cpp -lfreeimage

* For OS X (Xcode 4.6 with command line tools and FreeImage installed) you could use:

clang++ -std=c++11 -stdlib=libc++ save_image.cpp utils.cpp mandel.cpp -lfreeimage


You could use this program under the terms of GPL v3, for more details see:

http://www.gnu.org/copyleft/gpl.html

Copyright 2013 Sol from www.solarianprogrammer.com

