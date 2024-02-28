#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

//����ũ �Լ�
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

	//setTo(��� ���� ��, ����ũ ���)
	//src �̹����� ����ũ �� ��ŭ ��������� ǥ���Ѵ�.
	//Scalar(�Ķ���, ���, ������, ����)
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

	//copyTo(���纻 ���, ����ũ ���)
	//mask ������ �ȼ����� 0�� �ƴ� ��ġ������ �����Ѵ�.(�������� �ƴ� ��)
	//mask ������ 0�� �ƴ� ��ġ ���� dst�� �����Ѵ�.
	src.copyTo(dst, mask);

	imshow("src", src);
	imshow("mask", mask);
	imshow("dst", dst);

	waitKey(0);
	destroyAllWindows();
}