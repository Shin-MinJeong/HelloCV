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

//산술연산
void arithmetic() {

	Mat src1 = imread("lenna256.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("square.bmp", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "이미지 로드 실패" << endl;
		return ;
	}

	imshow("src1", src1);
	imshow("src2", src2);

	Mat dst1, dst2, dst3, dst4;

	//덧셈연산 
	//add(입력1, 입력2, 출력, mask, 행렬의 깊이)
	add(src1, src2, dst1);
	//뺄셈연산 
	//subtract(입력1, 입력2, 출력,mask, 행렬의 깊이)
	subtract(src1, src2, dst2);
	//평균연산 
	//addWeighted(입력1, 가중치1, 입력2, 가중치2, 추가값, 출력, 행렬의 깊이)
	addWeighted(src1, 0.5, src2, 0.5, 0, dst3);
	//차이연산
	//absdiff(입력1, 입력2, 출력)
	absdiff(src1, src2, dst4);

	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);
	imshow("dst4", dst4);

	waitKey();

}

//논리연산
void logical() {

	Mat src1 = imread("lenna256.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("square.bmp", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "이미지 로드 실패" << endl;
		return;
	}

	imshow("src1", src1);
	imshow("src2", src2);

	Mat dst1, dst2, dst3, dst4;

	//논리곱 
	//bitwise_and(입력1, 입력2, 출력, mask)
	bitwise_and(src1, src2, dst1);
	//논리합 
	//bitwise_or(입력1, 입력2, 출력, mask)
	bitwise_or(src1, src2, dst2);
	//배타적 논리합 
	//bitwise_xor(입력1, 입력2, 출력, mask)
	bitwise_xor(src1, src2, dst3);
	//부정 연산 
	//bitwise_not(입력1, 출력, mask)
	bitwise_not(src1, dst4);

	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);
	imshow("dst4", dst4);

	waitKey();

}



