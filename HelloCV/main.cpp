#include "opencv2/opencv.hpp"
#include <iostream>

int main() {

	std::cout << "Hello OpenCV" << CV_VERSION << std::endl;
	 
	cv::Mat img;					// Mat 클래스 타입의 변수 img 선언
	img = cv::imread("lenna.bmp");  // 영상 읽기

	if (img.empty()) {				// 영상이 불러와지지 않는경우 empty = true
		std::cout << "Image load failed";
		return -1;
	}
	else {
		cv::namedWindow("image");
		cv::imshow("image", img);	// 영상 보여주기
	}

	cv::waitKey();					// 키보드 입력을 기다리는 함수
	
	return 0;

}

