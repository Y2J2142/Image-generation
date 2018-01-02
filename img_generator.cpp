#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <string>
#include <iostream>
#include <sys/time.h>
#include <thread>
using namespace cv;

float colour_counter(Mat);
Mat generate(Mat, int, int);
int main(int argc, char * argv[] )
{
	Mat src;
	
	src = imread("hqdefault.jpg",CV_LOAD_IMAGE_COLOR);
	int limit = atoi(argv[1]);
	int size = atoi(argv[2]);
	auto start = getTickCount();
	
	Mat output = generate(src, limit, size);
	
	auto end = getTickCount();
	std::cout << (end-start)/getTickFrequency() << std::endl;		
	
	imwrite("output.jpg", output);
	
	return 0;
}



float colour_counter(Mat src, Mat m1)
{
	float counter = 0;
	for(int i = 0; i < m1.cols; i++)
		for(int j = 0; j < m1.rows; j++)
		{
			Vec3b src_clr = src.at<Vec3b>(Point(i, j));
			Vec3b m1_clr = m1.at<Vec3b>(Point(i, j));
			counter += abs(src_clr[0] - m1_clr[0]) + abs(src_clr[1] - m1_clr[1]) + abs(src_clr[2] - m1_clr[2]);
		}
		
	return counter;
	
}
 Mat generate(Mat src, int limit, int size)
 {
	 Mat img1(src.size().height, src.size().width, CV_8UC3, Scalar(255,255,255));
	Mat img2(src.size().height, src.size().width, CV_8UC3, Scalar(255,255,255));
	
	RNG rng(0xFFFFFFFF);
	
	
	for(auto i = 0; i<limit;i++)
	{
		Point point(rng.uniform(0, src.size().width), rng.uniform(0, src.size().height));
		Vec3b colour = src.at<Vec3b>(point);
		Scalar colour_scalar(colour[0], colour[1], colour[2]);
		circle(img1, point, size, colour_scalar, -1);
		
		Point pnt1((point.x - size) > 0 ? point.x - size : 0, (point.y - size) > 0 ? point.y - size : 0);
		Point pnt2((point.x + size) > src.cols ? src.cols : point.x + size, (point.y + size) > src.rows ? src.rows : point.y + size);
		Mat src_cmpr_part(src, Rect(pnt1, pnt2));
		Mat img1_cmpr_part(img1, Rect(pnt1, pnt2));
		Mat img2_cmpr_part(img2, Rect(pnt1, pnt2));
		
				
		auto src_to_img1 = norm(src_cmpr_part, img1_cmpr_part, NORM_INF);
		auto src_to_img2 = norm(src_cmpr_part, img2_cmpr_part, NORM_INF);
		if(src_to_img1 < src_to_img2)
			img2.copyTo(img1);
		else
			circle(img2, point, size, colour_scalar, -1);
		/*
		if(i%100 == 0)
		{
			std::string number = std::to_string(i/100);
			while(number.size() < 5)
				number = std::string("0") + number;
			 
			 std::string image_path = std::string("images/img") + number + std::string(".jpg"); 
			
			imwrite(image_path, img1);
		} 
		*/
		
	}
	 
	 return img1;
}
