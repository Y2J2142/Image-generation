#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <string>

using namespace cv;

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
		circle(img1, point, size, colour_scalar, -1);
		
		Point pnt1((point.x - size) > 0 ? point.x - size : 0, (point.y - size) > 0 ? point.y - size : 0);
		Point pnt2((point.x + size) > src.cols ? src.cols : point.x + size, (point.y + size) > src.rows ? src.rows : point.y + size);
		Mat src_cmpr_part(src, Rect(pnt1, pnt2));
		Mat img1_cmpr_part(img1, Rect(pnt1, pnt2));
		Mat img2_cmpr_part(img2, Rect(pnt1, pnt2));
		
				
		auto src_to_img1 = norm(src_cmpr_part, img1_cmpr_part, NORM_INF);
		auto src_to_img2 = norm(src_cmpr_part, img2_cmpr_part, NORM_INF);
		if(src_to_img1 < src_to_img2)
		{
			Mat temp(img2, Rect(pnt1, pnt2));
			temp.copyTo(img1(Rect(pnt1, pnt2)));
		}
		
		else
		{	
			circle(img2, point, size, colour_scalar, -1);
			circle(dst, point, size, colour_scalar, -1);
		}			
		
		if(i%(limit/1000) == 0 && saver)
		{
			std::string number = std::to_string(i/(limit/1000));
			while(number.size() < 5)
				number = std::string("0") + number;
			 
			 std::string image_path = std::string("images/img") + number + std::string(".jpg"); 
			
			imwrite(image_path, dst);
		} 
			
		
	}
	 
	 return;
}
