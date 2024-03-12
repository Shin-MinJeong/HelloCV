#include "opencv2/opencv.hpp"
#include <iostream>
#include <opencv2/core/utils/logger.defines.hpp>
#include <opencv2/core/utils/logtag.hpp>
#include <opencv2/core/utils/logger.hpp> 
#define OPENCV_LOGGER_DEFINES_HPP

using namespace cv;
using namespace std;

void filter_embossing();
void blurring_mean();
void noise_gaussian();
void filter_bilateral();
void filter_median();


Mat src;
Mat dst;

int main(void) {

	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_ERROR);

	filter_embossing();
	blurring_mean();
	noise_gaussian();
	filter_bilateral();
	filter_median();

	waitKey(0);
	destroyAllWindows();

	return 0;
}

//엠보싱 필터
void filter_embossing() {	

	src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "이미지 로드 에러" << endl;
		return;
	}

	float data[] = { -1, -1, 0, -1, 0, 1, 0, 1, 1 };
	Mat emboss(3, 3, CV_32FC1, data);

	filter2D(src, dst, -1, emboss, Point(-1, -1), 128);

	imshow("emboss_src", src);
	imshow("emboss_dst", dst);

}

//블러링
void blurring_mean() {

	src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "이미지 로드 에러" << endl;
		return;
	}

	imshow("blur_src", src); 

	for (int ksize = 3; ksize < 8; ksize += 2) {
		blur(src, dst, Size(ksize, ksize));

		String desc = format("Mean: %d x %d", ksize, ksize);

		putText(dst, desc, Point(10, 30), FONT_HERSHEY_PLAIN, 1.0, Scalar(255), 1, LINE_AA);

		imshow("blur_dst", dst); 
		waitKey(0);
	}

}

//가우시안 필터
void noise_gaussian() {

	src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "이미지 로드 에러" << endl;
		return;
	}

	imshow("noise_src", src);

	for (int stddev = 10; stddev < 31; stddev += 10) {
		Mat noise(src.size(), CV_32SC1);
		randn(noise, 0, stddev); //난수생성

		add(src, noise, dst, Mat(), CV_8U);

		String desc = format("stddev = %d", stddev);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);

		imshow("noise_dst", dst);
		waitKey(0);

	}
}

//양방향 필터링
void filter_bilateral() {

	src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "이미지 로드 에러" << endl;
		return;
	}

	// 평균이 0이고 표준 편차가 5인 가우시안 잡음 추가
	Mat noise(src.size(), CV_32SC1);

	randn(noise, 0, 5);
	add(src, noise, src, Mat(), CV_8U);

	// 표준 편차가 5인 가우시안 필터링 수행
	Mat dst1;
	GaussianBlur(src, dst1, Size(), 5);

	// 색 공간의 표준 편차는 10, 좌표 공간의 표준편자는 5를 사용하는 양방향 필터링 수행
	Mat dst2;
	bilateralFilter(src, dst2, -1, 10 , 5);

	imshow("src", src);
	imshow("Gaussian_dst1", dst1);
	imshow("bilateral_dst2", dst2);

}

//미디언 필터링
void filter_median() {

	src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "이미지 로드 에러" << endl;
		return;
	}

	// src 영상에서 10%에 해당하는 픽셀 값을 0 또는 255로 설정
	// 소금&후추 잡음
	int num = (int)(src.total() * 0.1);

	for (int i = 0; i < num; i++) {
		int x = rand() % src.cols;
		int y = rand() % src.rows;

		src.at<uchar>(y, x) = (i % 2) * 255;
	}

	// 표준 편차가 1인 가우시안 필터링 수행
	Mat dst1;
	GaussianBlur(src, dst1, Size(), 1);

	// 크기가 3인 미디언 필터링 수행
	Mat dst2;
	medianBlur(src, dst2, 3);

	imshow("src", src);
	imshow("Gaussian_dst1", dst1);
	imshow("median_dst2", dst2);
}


