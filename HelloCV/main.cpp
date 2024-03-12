#include "opencv2/opencv.hpp"
#include <iostream>
#include <opencv2/core/utils/logger.defines.hpp>
#include <opencv2/core/utils/logtag.hpp>
#include <opencv2/core/utils/logger.hpp> 
#define OPENCV_LOGGER_DEFINES_HPP

using namespace cv;
using namespace std;

Mat src;
Mat dst;

void sobel_edge();
void canny_edge();

int main(void) {

	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_ERROR);

	sobel_edge(); 
	canny_edge();

	waitKey(0);
	destroyAllWindows();

	return 0;
}

void sobel_edge() {

	src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
	        cerr << "Image load failed!" << endl;
	        return;
	}

	Mat dx, dy;

	// sobel 함수를 사용하여 미분
	// x축 방향으로 1차 편미분 = dx
	// y축 방향으로 1차 편미분 = dy
	Sobel(src, dx, CV_32FC1, 1, 0);
	Sobel(src, dy, CV_32FC1, 0, 1);

	Mat fmag, mag;

	// magnitude 함수로 그래디언트 크기를 계산(밝기의 차이 검출)
	// 실수형 행렬 fmag를 그레이스케일 형식으로 변환하여 mag에 저장
	magnitude(dx, dy, fmag);
	fmag.convertTo(mag, CV_8UC1);

	// 그래디언트 크기 임계값을 150으로 설정하여 에지를 판별
	// 행렬 edge의 원소 값은 mag 행렬 원소 값이 150보다 크면 255로, 작으면 0으로 설정
	// 임계값을 150보다 낮게 설정하면 더 많은 에지 픽셀이 edge 영상에 나타남
	Mat edge = mag > 150;

	imshow("sobel_src", src);
	imshow("sobel_mag", mag); // mag == 그래디언트 크기를 그레이스케일 영상 형식으로 나타낸 것
	imshow("sobel_edge", edge); // edge == 그래디언트 크기 > 150 픽셀은 흰색으로, 그렇지 않은 픽셀은 검은색으로 표현된 이진 영상
}

void canny_edge() {

	src = imread("road.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst1, dst2;

	// canny 알고리즘
	// 임계값을 낮출수록 에지로 판별되는 픽셀이 더 많아짐
	// 임계값을 낮출수록 잡음에 해당하는 픽셀도 에지로 검출할 가능성이 높아짐
	Canny(src, dst1, 50, 100); // 낮은 임계값 = 50 , 높은 임계값 = 100
	Canny(src, dst2, 50, 150); // 낮은 임계값 = 50 , 높은 임계값 = 150

	imshow("canny_src", src);
	imshow("canny_dst1", dst1);
	imshow("canny_dst2", dst2);

}

