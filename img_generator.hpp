#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <string>
#include <cmath>
#include <thread>
#include <atomic>
using namespace cv;

void generate(Mat, Mat, int, int, int, int, bool);
Point draw_line(Mat, Point, int, const Scalar&, int, RNG);

void generate(Mat src, Mat dst, int limit, int size, int range_begin, int range_end, bool saver)
 {
	Mat img1(src.size().height, src.size().width, CV_8UC3, Scalar(255,255,255));
	Mat img2(src.size().height, src.size().width, CV_8UC3, Scalar(255,255,255));
	
	RNG rng(0xFFFFFFFF);
	
	
	for(auto i = 0; i<limit;i++)
	{
		Point point(rng.uniform(range_begin, range_end), rng.uniform(0, src.size().height));
		Vec3b colour = src.at<Vec3b>(point);
		Scalar colour_scalar(colour[0], colour[1], colour[2]);
		
		Point pnt1((point.x - size) > 0 ? point.x - size : 0, (point.y - size) > 0 ? point.y - size : 0);
		Point pnt2(min(src.cols, point.x + size), min(src.rows, point.y + size));
				
						
		Mat src_cmpr_part(src, Rect(pnt1, pnt2));
		Mat img1_cmpr_part(img1, Rect(pnt1, pnt2));
		Mat img2_cmpr_part(img2, Rect(pnt1, pnt2));
		
				
		auto src_to_img1 = norm(src_cmpr_part, img1_cmpr_part, NORM_INF);
		auto src_to_img2 = norm(src_cmpr_part, img2_cmpr_part, NORM_INF);
		if(src_to_img1 < src_to_img2)
		{
			Mat temp1(img1, Rect(pnt1, pnt2));
			Mat temp2(img2, Rect(pnt1, pnt2));
			memcpy(temp1.data, temp2.data, sizeof(temp1.data));
		}
		else
		{
				circle(img2, point, size, colour_scalar, -1);
				circle(dst, point, size, colour_scalar, -1);
		}
		if(i%(limit/10000) == 0 && saver)
		{
			std::string number(std::to_string(i/(limit/10000)));
			while(number.size() < 5)
				number = std::string("0") + number;
			 
			std::string image_path = std::string("images/img") + number + std::string(".jpg"); 
			imwrite(image_path, dst);
		}
			
	}
	 
	 return;
}


Point draw_line(Mat dst, Point center, int length, const Scalar& colour, int thicc, RNG rng)
{
	length*=20;
	double angle = rng.uniform(0.0, 360.0) * CV_PI / 180;
	double offset_x = cos(angle) * length;
	double offset_y = sin(angle) * length;
	offset_x += center.x;
	offset_y += center.y;
	
	offset_x = offset_x > dst.cols ? dst.cols : offset_x < 0 ? 0 : offset_x;
	offset_y = offset_y > dst.rows ? dst.rows : offset_y < 0 ? 0 : offset_y; 
	Point end( offset_x, offset_y);
	line(dst, center, end, colour, thicc);
	
	return end;
	
	
} 


