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

vector<Point2f> src,dst;
int i=0;
Mat topvemp, topvfull, emptypic, traffic;
float w = 300, h = 600;//cropped image size
string trafficpicloc = "res/traffic.jpg";//put image here
string emptypicloc = "res/empty.jpg";//put image here
bool imageshown=false;

void mousePoints(int event, int x, int y, int flags, void* params) {
	Mat* image = reinterpret_cast<Mat*>(params);
	if (event == EVENT_LBUTTONDOWN) {
		src.push_back(Point2f(x, y));
	}
	if ((src.size() == 4)&&(!imageshown)) {
		//Point2f src[4] = { {949,275},{1282,264},{510,1044},{1505,1045} };
		dst = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };
		Mat wpmat = findHomography(src, dst);
		warpPerspective(emptypic, topvemp, wpmat, Point(w, h));
		warpPerspective(traffic, topvfull, wpmat, Point(w, h));
		imshow("Empty", topvemp);
		imshow("Traffic", topvfull);
		imageshown = true;
	}
}

int main() {
	traffic = imread(trafficpicloc);
	emptypic = imread(emptypicloc);
	imshow("Original Image", emptypic);
	setMouseCallback("Original Image", mousePoints, reinterpret_cast<void*>(&emptypic));
	//imshow("Image", topvfull);
	waitKey(0);
	return 0;
}