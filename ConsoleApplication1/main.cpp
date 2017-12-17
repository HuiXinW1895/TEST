#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include <vector>
#include <opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  

using namespace cv;
using namespace std;

int main()
{	
	Mat image = imread("1.jpg");
	Mat graye, noise, canny,dstImage;

	cvtColor(image, graye, COLOR_BGR2GRAY);
	medianBlur(image, noise, 5);
	Canny(noise, canny, 50, 200, 3);
	dstImage = canny.clone();

	//<span style = "white-space:pre">  < / span>//获取自定义核  
	/*Mat element1 = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat out1;
	//<span style = "white-space:pre">  < / span>//进行膨胀操作  
	dilate(noise, out1, element1);
	Mat element2 = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat out2;
	//进行腐蚀操作  
	erode(out1, out2, element2);

	Canny(out2, canny, 50, 200, 3);*/

	dstImage = image.clone();
	
	vector<Vec4i> lines;//定义一个矢量结构lines用于存放得到的线段矢量集合  
	HoughLinesP(canny, lines, 1, CV_PI / 180, 60, 30, 20);

	//【4】依次在图中绘制出每条线段  
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		double k = (l[1] - l[3]) / (l[0] - l[2])*1.0;
		if (k<-0.5||k>0.5) {
			if ((l[1] - l[3])*(l[1] - l[3]) + (l[0] - l[2])*(l[0] - l[2])<4500)
			    line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 188, 255), 1, CV_AA);

			else
				line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(286, 288, 155), 1, CV_AA);
		}
	}

	imwrite("a.jpg", canny);
	imshow("原图", image);
	//imshow("灰度", graye);
	imshow("灰度+滤波", noise);
	imshow("canny算子", canny);
	imshow("车道线", dstImage);

	waitKey(0);
	return 0;
	
}