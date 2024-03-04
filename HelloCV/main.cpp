#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;


int main(void) {


	Mat src1 = imread("lenna256.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("square.bmp",   IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "이미지 로드 실패" << endl;
		return -1;
	}

	imshow("src1", src1);
	imshow("src2", src2);

	Mat dst1, dst2, dst3, dst4 ;

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
	imshow("dst1", dst1);

	waitKey();

	return 0;
}



