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


Point2f src[4] = { {0.0f,0.0f},{0.0f,0.0f},{0.0f,0.0f},{0.0f,0.0f} };
int index=0;
float w = 300, h = 600;

void mousePoints(int event, int x, int y, int flags, void* params) {//not working. need to update global src
	Mat* image = reinterpret_cast<Mat*>(params);
	if (event == EVENT_LBUTTONDOWN) {
		if (index < 4) {
			src[index] = { x,y };
			index++;
		}
	}
}
int main() {
	string trafficpicloc = "res/traffic.jpg";//put image here
	string emptypicloc = "res/empty.jpg";//put image here
	Mat traffic = imread(trafficpicloc);
	Mat empty = imread(emptypicloc);
	imshow("Original Image", empty);
	setMouseCallback("Image", mousePoints, reinterpret_cast<void*>(&empty));

	if (index > 3) {
		while (true) {
			Mat topvemp, topvfull;
			Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };
			Mat wpmat = getPerspectiveTransform(src, dst);
			warpPerspective(empty, topvemp, wpmat, Point(w, h));
			warpPerspective(traffic, topvfull, wpmat, Point(w, h));
			imshow("Image", topvemp);
			//imshow("Image", topvfull);
			waitKey(0);
		}
	}
	return 0;
}