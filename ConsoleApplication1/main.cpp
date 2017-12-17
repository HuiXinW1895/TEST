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

	//<span style = "white-space:pre">  < / span>//��ȡ�Զ����  
	/*Mat element1 = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat out1;
	//<span style = "white-space:pre">  < / span>//�������Ͳ���  
	dilate(noise, out1, element1);
	Mat element2 = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat out2;
	//���и�ʴ����  
	erode(out1, out2, element2);

	Canny(out2, canny, 50, 200, 3);*/

	dstImage = image.clone();
	
	vector<Vec4i> lines;//����һ��ʸ���ṹlines���ڴ�ŵõ����߶�ʸ������  
	HoughLinesP(canny, lines, 1, CV_PI / 180, 60, 30, 20);

	//��4��������ͼ�л��Ƴ�ÿ���߶�  
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
	imshow("ԭͼ", image);
	//imshow("�Ҷ�", graye);
	imshow("�Ҷ�+�˲�", noise);
	imshow("canny����", canny);
	imshow("������", dstImage);

	waitKey(0);
	return 0;
	
}