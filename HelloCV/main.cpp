#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

//마스크 함수
void mask_setTo();
void mask_copyTo();

int main(void) {

	cout << "Hello OpenCV" << CV_VERSION << endl;

	mask_setTo();
	mask_copyTo();

	return 0;
}


void mask_setTo() {

	Mat src = imread("lenna.bmp", IMREAD_COLOR);
	Mat mask = imread("mask_smile.bmp", IMREAD_GRAYSCALE);

	if (src.empty() || mask.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	//setTo(행렬 원소 값, 마스크 행렬)
	//src 이미지를 마스크 값 만큼 노란색으로 표시한다.
	//Scalar(파란색, 녹색, 빨간색, 투명도)
	src.setTo(Scalar(0, 255, 255), mask);

	imshow("src", src);
	imshow("mask", mask);

	waitKey();
	destroyAllWindows();
}

void mask_copyTo() {
	Mat src = imread("airplane.bmp", IMREAD_COLOR);
	Mat mask = imread("mask_plane.bmp", IMREAD_GRAYSCALE);
	Mat dst = imread("field.bmp", IMREAD_COLOR);

	if (src.empty() || mask.empty() || dst.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	//copyTo(복사본 행렬, 마스크 행렬)
	//mask 영상의 픽셀값이 0이 아닌 위치에서만 복사한다.(검정색이 아닌 것)
	//mask 변수에 0이 아닌 위치 값을 dst로 복사한다.
	src.copyTo(dst, mask);

	imshow("src", src);
	imshow("mask", mask);
	imshow("dst", dst);

	waitKey(0);
	destroyAllWindows();
}