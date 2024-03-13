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

// ���� ��ȯ ���� ����
// ������ �� ���� ��ǥ ��� �� ���� �̿��Ͽ� �������� �� �� ��ǥ pt1�� pt2�� ���Ѵ�
void hough_lines() {

	src = imread("building.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
	        cerr << "Image load failed!" << endl;
	        return;
	}

	// canny�Լ��� ���������� edge�� ����
	Mat edge;
	Canny(src, edge, 50, 150); 

	// HoughLines�Լ��� �̿��Ͽ� ������ ������ �Ķ���� ��� �� ������ lines�� ����
	vector<Vec2f> lines;
	HoughLines(edge, lines, 1, CV_PI / 180, 250); 

	// edge�� RGB 3ä�� �÷� �������� ��ȯ�Ͽ� dst�� ����
	cvtColor(edge, dst, COLOR_GRAY2BGR);

	for (size_t i = 0; i < lines.size(); i++) {
		float r = lines[i][0]; // �� ���� r��
		float t = lines[i][1]; // �踦 ���� t��

		double sin_t	= sin(t);
		double cos_t	= cos(t);
		// x0�� y0�� �������� ������ ������ ������ �� ������ ���� ��ǥ
		double x0		= r * cos_t;
		double y0		= r * sin_t;
		double alpha	= 1000;

		// pt1�� pt2���� (x0, y0)���� ����� �ָ� ������ �ִ� �������� �� �� ��ǥ
		Point pt1(cvRound(x0 + alpha * (-sin_t)), cvRound(y0 + alpha * cos_t));
		Point pt2(cvRound(x0 - alpha * (-sin_t)), cvRound(y0 - alpha * cos_t));

		// ���� �׸���
		line(dst, pt1, pt2, Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow("src", src);
	imshow("dst", dst);
}

// Ȯ���� ���� ��ȯ ���� ����
// ������ ������ �ִ� ��ġ������ ������ �׷�����
void hough_line_segments() {

	src = imread("building.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// canny�Լ��� ���������� edge�� ����
	Mat edge;
	Canny(src, edge, 50, 150);

	// 	HoughLinesP() �Լ��� �̿��Ͽ� ��� ���� ������ �������� ���� ��ǥ ����
	vector<Vec4i> lines;
	HoughLinesP(edge, lines, 1, CV_PI / 180, 250);

	// edge�� RGB 3ä�� �÷� �������� ��ȯ�Ͽ� dst�� ����
	cvtColor(edge, dst, COLOR_GRAY2BGR);

	// 	HoughLinesP() �Լ��� ���� ������ ��� ���� ������ dst ���� ���� ������ �������� �׸�
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

	// src ������ ������ ����
	Mat blurred;
	blur(src, blurred, Size(3, 3));

	// ���� �����Ѵ�
	// �� ���� �߽��� �Ÿ��� 50�ȼ�, ĳ�� ���� ������� ���� �Ӱ谪�� 150, ���� �迭 ���� ���� 30���� ũ�� ���� �߽���
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