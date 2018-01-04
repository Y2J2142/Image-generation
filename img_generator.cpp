#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
#include <sys/time.h>
#include <future>
#include <vector>
#include "img_generator.hpp"
using namespace cv;


int main(int argc, char * argv[] )
{
	Mat src;
	
	src = imread("hqdefault.jpg",CV_LOAD_IMAGE_COLOR);
	Mat output(src.rows, src.cols, CV_8UC3, Scalar(255,255,255));
	int limit = atoi(argv[1]);
	int size = atoi(argv[2]);
	int threads = atoi(argv[3]);
	
	
	auto start = getTickCount();
	std::vector<std::future<void>> futures;
	for(int i = 0 ; i < threads; i++)
	{
			futures.push_back( std::async(std::launch::async, generate, src, output, limit/threads, size, i*src.cols/threads, (i+1)*src.cols/threads, threads==1));
	}
	for( auto &f : futures )
		f.get();
	imwrite("output.jpg", output); 
	
	auto end = getTickCount();
	std::cout << (end-start)/getTickFrequency() << std::endl;		
	
	
	return 0;
}



