default:
	sudo apt-get install -y libfreeimage-dev
	g++ -std=c++11 -O3 save_image.cpp utils.cpp mandel.cpp -lfreeimage