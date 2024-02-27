#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat img;	 // Mat 클래스 타입의 변수 img 선언
Point pt;

//이전 마우스 이벤트 발생 위치를 저장하는 함수
void on_mouse(int event, int x, int y, int flags, void*);
//트랙바 콜백 함수
void on_level_change(int pos, void* userdata);

int main() {

	cout << "Hello OpenCV" << CV_VERSION << endl;

	//픽셀값이 0으로 초기화 된 400*400 크기의 영상 img
	img = Mat::zeros(400, 400, CV_8UC1);

	namedWindow("image");
	
	//트랙바 생성
	//createTrackbar(트랙바이름, 트랙바 생성창, 트랙바 위치를 받을 주소, 트랙바 최대 위치, 콜백함수, 사용자 포인터)
	createTrackbar("level", "image", 0, 10, on_level_change, (void*)&img);

	imshow("image", img);
	waitKey(0);

	return 0;
}

//트랙바 콜백 함수
//트랙바 콜백 함수는 정해진 형식을 따라야 한다.
//트랙바 콜백 함수(트랙바의 위치 정보, 사용자 데이터 포인터 값)
void on_level_change(int pos, void* userdata)
{
    Mat img = *(Mat*)userdata;

        img.setTo(pos * 16); //픽셀값 = 사용자데이터*16
    imshow("image", img);
}


