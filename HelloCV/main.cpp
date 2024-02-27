#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat img;	 // Mat Ŭ���� Ÿ���� ���� img ����
Point pt;

//���� ���콺 �̺�Ʈ �߻� ��ġ�� �����ϴ� �Լ�
void on_mouse(int event, int x, int y, int flags, void*);

int main() {

	cout << "Hello OpenCV" << CV_VERSION << endl;

	img = imread("lenna.bmp");  // ���� �б�

	if (img.empty()) {				// ������ �ҷ������� �ʴ°�� empty = true
		cout << "Image load failed";
		return -1;
	}

	//setMouseCallback() �Լ��� ����ϱ� ���� ���콺 �̺�Ʈ�� ���� â �̸� ����
	namedWindow("img");
	setMouseCallback("img", on_mouse);

	imshow("img", img);
	waitKey(0);

	return 0;
}
	
//���콺 �ݹ� �Լ� on_mouse() �Լ����� �Բ� ����� ������ ���� ���� img�� �����Ͽ� ���
//on_mouse() �Լ������� sitch~case ������ �̿��Ͽ� ���콺 �̺�Ʈ�� ó���Ѵ�
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


