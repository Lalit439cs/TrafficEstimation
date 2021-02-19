//#include "stdafx.h"
//cd /mnt/c/Users/User/Desktop/TrafficCV/
//g++ topview.cpp -o test -pthread -std=c++11 `pkg-config --cflags --libs opencv`

#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

Point2f src[4];
int i=0;

void mousePoints(int event, int x, int y, int flags, void* params) {
	Mat* image = reinterpret_cast<Mat*>(params);
	if (event == EVENT_LBUTTONDOWN) {
		cout << x << " " << y << " ";
		//addelem(x, y, i);
	}
}
void addelem(int x, int y,int index) {
	src[index].x = x;
	src[index].y = y;
	i++;
}
int main() {
	string trafficpicloc = "res/traffic.jpg";//put image here
	string emptypicloc = "res/empty.jpg";//put image here
	Mat traffic = imread(trafficpicloc);
	Mat empty = imread(emptypicloc);
	imshow("Original Image", empty);
	//setMouseCallback("Original Image", mousePoints, reinterpret_cast<void*>(&empty));
	Mat topvemp, topvfull;

	float w = 300, h = 600;
	Point2f src[4] = { {949,275},{1282,264},{510,1044},{1505,1045} };
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };
	Mat wpmat = getPerspectiveTransform(src, dst);
	warpPerspective(empty, topvemp, wpmat, Point(w, h));
	warpPerspective(traffic, topvfull, wpmat, Point(w, h));
	imshow("Image", topvemp);
	//imshow("Image", topvfull);
	waitKey(0);
	return 0;
}