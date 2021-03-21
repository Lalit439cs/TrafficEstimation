//C:\Users\User\Desktop\TrafficCV
//g++ topview.cpp -o test -pthread -std=c++11 `pkg-config --cflags --libs opencv`

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include<Windows.h>
#include<Pdh.h>

using namespace cv;
using namespace std;

vector<Point2f> src, dst;
Mat emptypic, wpmat;
Mat vidframe, flow, prevframe;
string empname, videoloc;

void playvideo() {
	VideoCapture cap(videoloc);
	while (cap.read(vidframe) == true) {
		cvtColor(vidframe, vidframe, COLOR_BGR2GRAY);
		absdiff(vidframe, emptypic, vidframe);
		threshold(vidframe, vidframe, 50.0, 100.0, THRESH_BINARY);
		warpPerspective(vidframe, vidframe, wpmat, vidframe.size());
		vidframe = vidframe(Rect(472, 52, 800 - 472, 830 - 52));
		int movingcount = 0;
		int queuecount = 0;
		int framenum = cap.get(CAP_PROP_POS_FRAMES);
		if (prevframe.empty() == false) {
			calcOpticalFlowFarneback(prevframe, vidframe, flow, 0.4, 1, 12, 2, 8, 1.2, 0);
			for (int y = 0; y < vidframe.rows; y += 5) {
				for (int x = 0; x < vidframe.cols; x += 5) {
					Point2f flowatxy = flow.at<Point2f>(y, x) / 5;
					int intensity = (int)vidframe.at<uchar>(y, x);
					int pixelval = pow(flowatxy.x, 2.0) + pow(flowatxy.y, 2.0);
					if (intensity > 50) {
						if (pixelval > 1.0) {
							movingcount++;
						}
						queuecount++;
					}
				}
			}
		}
		cout << framenum << "," << movingcount << "," << queuecount << "\n";
		imshow("Video", vidframe);
		waitKey(30);
		prevframe = vidframe;
	}
}

void startprocess() {
	src= { {946.0f,260.0f},{523.0f,1066.0f},{1558.0f,1070.0f},{1294.0f,252.0f} };//hardcoded values for rapid testing
	dst = { {472.0f,52.0f},{472.0f,830.0f},{800.0f,830.0f},{800.0f,52.0f} };//values used by instructor
	wpmat = findHomography(src, dst);
	playvideo();
	destroyAllWindows();
}

int main() {
	//cout << "Enter traffic image and video directory and name in separate lines:\n";
	//cin >> empname;
	//cin >> videoloc;
	//string emptypicloc = empname;//put image here
	string emptypicloc = "C:/Users/User/Desktop/TrafficCV/empty.jpg";//remove later
	videoloc = "C:/Users/User/Desktop/TrafficCV/trafficvideo.mp4";//remove later
	emptypic = imread(emptypicloc);
	cvtColor(emptypic, emptypic, COLOR_BGR2GRAY);
	if (!emptypic.data) {
		cout << "Image not Found";
		return 0;
	}
	startprocess();
	return 0;
}
