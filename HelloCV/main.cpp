#include "opencv2/opencv.hpp"
#include <iostream>

int main() {

	std::cout << "Hello OpenCV" << CV_VERSION << std::endl;
	 
	cv::Mat img;					// Mat Ŭ���� Ÿ���� ���� img ����
	img = cv::imread("lenna.bmp");  // ���� �б�

	if (img.empty()) {				// ������ �ҷ������� �ʴ°�� empty = true
		std::cout << "Image load failed";
		return -1;
	}
	else {
		cv::namedWindow("image");
		cv::imshow("image", img);	// ���� �����ֱ�
	}

	cv::waitKey();					// Ű���� �Է��� ��ٸ��� �Լ�
	
	return 0;

}

