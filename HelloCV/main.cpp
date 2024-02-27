#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat img;	 // Mat Ŭ���� Ÿ���� ���� img ����
Point pt;

//���� ���콺 �̺�Ʈ �߻� ��ġ�� �����ϴ� �Լ�
void on_mouse(int event, int x, int y, int flags, void*);
//Ʈ���� �ݹ� �Լ�
void on_level_change(int pos, void* userdata);

int main() {

	cout << "Hello OpenCV" << CV_VERSION << endl;

	//�ȼ����� 0���� �ʱ�ȭ �� 400*400 ũ���� ���� img
	img = Mat::zeros(400, 400, CV_8UC1);

	namedWindow("image");
	
	//Ʈ���� ����
	//createTrackbar(Ʈ�����̸�, Ʈ���� ����â, Ʈ���� ��ġ�� ���� �ּ�, Ʈ���� �ִ� ��ġ, �ݹ��Լ�, ����� ������)
	createTrackbar("level", "image", 0, 10, on_level_change, (void*)&img);

	imshow("image", img);
	waitKey(0);

	return 0;
}

//Ʈ���� �ݹ� �Լ�
//Ʈ���� �ݹ� �Լ��� ������ ������ ����� �Ѵ�.
//Ʈ���� �ݹ� �Լ�(Ʈ������ ��ġ ����, ����� ������ ������ ��)
void on_level_change(int pos, void* userdata)
{
    Mat img = *(Mat*)userdata;

        img.setTo(pos * 16); //�ȼ��� = ����ڵ�����*16
    imshow("image", img);
}


