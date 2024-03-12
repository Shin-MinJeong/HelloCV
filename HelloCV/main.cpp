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

	// sobel �Լ��� ����Ͽ� �̺�
	// x�� �������� 1�� ��̺� = dx
	// y�� �������� 1�� ��̺� = dy
	Sobel(src, dx, CV_32FC1, 1, 0);
	Sobel(src, dy, CV_32FC1, 0, 1);

	Mat fmag, mag;

	// magnitude �Լ��� �׷����Ʈ ũ�⸦ ���(����� ���� ����)
	// �Ǽ��� ��� fmag�� �׷��̽����� �������� ��ȯ�Ͽ� mag�� ����
	magnitude(dx, dy, fmag);
	fmag.convertTo(mag, CV_8UC1);

	// �׷����Ʈ ũ�� �Ӱ谪�� 150���� �����Ͽ� ������ �Ǻ�
	// ��� edge�� ���� ���� mag ��� ���� ���� 150���� ũ�� 255��, ������ 0���� ����
	// �Ӱ谪�� 150���� ���� �����ϸ� �� ���� ���� �ȼ��� edge ���� ��Ÿ��
	Mat edge = mag > 150;

	imshow("sobel_src", src);
	imshow("sobel_mag", mag); // mag == �׷����Ʈ ũ�⸦ �׷��̽����� ���� �������� ��Ÿ�� ��
	imshow("sobel_edge", edge); // edge == �׷����Ʈ ũ�� > 150 �ȼ��� �������, �׷��� ���� �ȼ��� ���������� ǥ���� ���� ����
}

void canny_edge() {

	src = imread("road.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst1, dst2;

	// canny �˰���
	// �Ӱ谪�� ������� ������ �Ǻ��Ǵ� �ȼ��� �� ������
	// �Ӱ谪�� ������� ������ �ش��ϴ� �ȼ��� ������ ������ ���ɼ��� ������
	Canny(src, dst1, 50, 100); // ���� �Ӱ谪 = 50 , ���� �Ӱ谪 = 100
	Canny(src, dst2, 50, 150); // ���� �Ӱ谪 = 50 , ���� �Ӱ谪 = 150

	imshow("canny_src", src);
	imshow("canny_dst1", dst1);
	imshow("canny_dst2", dst2);

}

