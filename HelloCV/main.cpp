#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void arithmetic();
void logical();


int main(void) {

	arithmetic();
	logical();

	return 0;
}

//�������
void arithmetic() {

	Mat src1 = imread("lenna256.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("square.bmp", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "�̹��� �ε� ����" << endl;
		return ;
	}

	imshow("src1", src1);
	imshow("src2", src2);

	Mat dst1, dst2, dst3, dst4;

	//�������� 
	//add(�Է�1, �Է�2, ���, mask, ����� ����)
	add(src1, src2, dst1);
	//�������� 
	//subtract(�Է�1, �Է�2, ���,mask, ����� ����)
	subtract(src1, src2, dst2);
	//��տ��� 
	//addWeighted(�Է�1, ����ġ1, �Է�2, ����ġ2, �߰���, ���, ����� ����)
	addWeighted(src1, 0.5, src2, 0.5, 0, dst3);
	//���̿���
	//absdiff(�Է�1, �Է�2, ���)
	absdiff(src1, src2, dst4);

	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);
	imshow("dst4", dst4);

	waitKey();

}

//������
void logical() {

	Mat src1 = imread("lenna256.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("square.bmp", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "�̹��� �ε� ����" << endl;
		return;
	}

	imshow("src1", src1);
	imshow("src2", src2);

	Mat dst1, dst2, dst3, dst4;

	//���� 
	//bitwise_and(�Է�1, �Է�2, ���, mask)
	bitwise_and(src1, src2, dst1);
	//���� 
	//bitwise_or(�Է�1, �Է�2, ���, mask)
	bitwise_or(src1, src2, dst2);
	//��Ÿ�� ���� 
	//bitwise_xor(�Է�1, �Է�2, ���, mask)
	bitwise_xor(src1, src2, dst3);
	//���� ���� 
	//bitwise_not(�Է�1, ���, mask)
	bitwise_not(src1, dst4);

	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);
	imshow("dst4", dst4);

	waitKey();

}



