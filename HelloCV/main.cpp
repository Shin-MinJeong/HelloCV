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

void hough_lines();
void hough_line_segments();
void hough_circle();

int main(void) {

	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_ERROR);

	hough_lines();
	hough_line_segments();
	hough_circle();

	waitKey(0);
	destroyAllWindows();

	return 0;
}

// 허프 변환 직선 검출
// 직선의 양 끝점 좌표 ρ와 θ 값을 이용하여 직선상의 두 점 좌표 pt1과 pt2를 구한다
void hough_lines() {

	src = imread("building.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
	        cerr << "Image load failed!" << endl;
	        return;
	}

	// canny함수로 에지영상을 edge에 저장
	Mat edge;
	Canny(src, edge, 50, 150); 

	// HoughLines함수를 이용하여 직선의 방정식 파라미터 ρ와 θ 정보를 lines에 저장
	vector<Vec2f> lines;
	HoughLines(edge, lines, 1, CV_PI / 180, 250); 

	// edge를 RGB 3채널 컬러 영상으로 변환하여 dst에 저장
	cvtColor(edge, dst, COLOR_GRAY2BGR);

	for (size_t i = 0; i < lines.size(); i++) {
		float r = lines[i][0]; // ρ를 변수 r에
		float t = lines[i][1]; // θ를 변수 t에

		double sin_t	= sin(t);
		double cos_t	= cos(t);
		// x0와 y0는 원점에서 직선에 수선을 내렸을 때 만나는 점의 좌표
		double x0		= r * cos_t;
		double y0		= r * sin_t;
		double alpha	= 1000;

		// pt1과 pt2에는 (x0, y0)에서 충분히 멀리 떨어져 있는 직선상의 두 점 좌표
		Point pt1(cvRound(x0 + alpha * (-sin_t)), cvRound(y0 + alpha * cos_t));
		Point pt2(cvRound(x0 - alpha * (-sin_t)), cvRound(y0 - alpha * cos_t));

		// 직선 그리기
		line(dst, pt1, pt2, Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow("src", src);
	imshow("dst", dst);
}

// 확률적 허프 변환 직선 검출
// 실제로 직선이 있는 위치에서만 선분이 그려진다
void hough_line_segments() {

	src = imread("building.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// canny함수로 에지영상을 edge에 저장
	Mat edge;
	Canny(src, edge, 50, 150);

	// 	HoughLinesP() 함수를 이용하여 모든 직선 성분의 시작점과 끝점 좌표 구함
	vector<Vec4i> lines;
	HoughLinesP(edge, lines, 1, CV_PI / 180, 250);

	// edge를 RGB 3채널 컬러 영상으로 변환하여 dst에 저장
	cvtColor(edge, dst, COLOR_GRAY2BGR);

	// 	HoughLinesP() 함수에 의해 구해진 모든 직선 성분을 dst 영상 위에 빨간색 직선으로 그림
	for (Vec4i l : lines) {
		line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow("segments_src", src);
	imshow("segments_dst", dst);

}

void hough_circle() {

	src = imread("coins.png", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// src 영상의 잡음을 제거
	Mat blurred;
	blur(src, blurred, Size(3, 3));

	// 원을 검출한다
	// 두 원의 중심점 거리가 50픽셀, 캐니 에지 검출기의 높은 임계값은 150, 축적 배열 원소 값이 30보다 크면 원의 중심점
	vector<Vec3f> circles;
	HoughCircles(blurred, circles, HOUGH_GRADIENT, 1, 50, 150, 30);

	cvtColor(src, dst, COLOR_GRAY2BGR);

	for (Vec3f c : circles) {
		Point center(cvRound(c[0]), cvRound(c[1]));
		int radius = cvRound(c[2]);
		circle(dst, center, radius, Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow("circle_src", src);
	imshow("circle_dst", dst);

}