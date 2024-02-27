#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat img;	 // Mat 클래스 타입의 변수 img 선언
Point pt;

//이전 마우스 이벤트 발생 위치를 저장하는 함수
void on_mouse(int event, int x, int y, int flags, void*);

int main() {

	cout << "Hello OpenCV" << CV_VERSION << endl;

	img = imread("lenna.bmp");  // 영상 읽기

	if (img.empty()) {				// 영상이 불러와지지 않는경우 empty = true
		cout << "Image load failed";
		return -1;
	}

	//setMouseCallback() 함수를 사용하기 전에 마우스 이벤트를 받을 창 미리 생성
	namedWindow("img");
	setMouseCallback("img", on_mouse);

	imshow("img", img);
	waitKey(0);

	return 0;
}
	
//마우스 콜백 함수 on_mouse() 함수에서 함께 사용할 영상을 전역 변수 img로 선언하여 사용
//on_mouse() 함수에서는 sitch~case 구문을 이용하여 마우스 이벤트를 처리한다
void on_mouse(int event, int x, int y, int flags, void*) {
	switch (event) {
	case EVENT_LBUTTONDOWN:
		pt = Point(x, y);
		cout << "EVENT_LBUTTONDOWN: " << x << ", " << y << endl;
		break;

	case EVENT_LBUTTONUP:
		cout << "EVENT_LBUTTONUP: " << x << ", " << y << endl;
		break;

	case EVENT_MOUSEMOVE:
		if (flags & EVENT_FLAG_LBUTTON) {
			line(img, pt, Point(x, y), Scalar(0, 255, 255), 2);
			imshow("img", img);
			pt = Point(x, y);
		}
		break;
	default:
		break;
		}
	}


