//C:\Users\User\Desktop\TrafficCV
//g++ topview.cpp -o test -pthread -std=c++11 `pkg-config --cflags --libs opencv`

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

vector<Point2f> src,dst;
Mat topvemp, topvfull, emptypic, traffic,cropemptypic, croptrafficpic;
string path;

void mousePointsO(int event, int x, int y, int flags, void* params) {
	Mat* image = reinterpret_cast<Mat*>(params);
	if (event == EVENT_LBUTTONDOWN) {
		src.push_back(Point2f(x, y));
	}
	if (src.size() == 4) {
		dst = { {472.0f,52.0f},{472.0f,830.0f},{800.0f,830.0f},{800.0f,52.0f} };//values used by instructor
		Mat wpmat = findHomography(src, dst);
		warpPerspective(emptypic, topvemp, wpmat, emptypic.size());
		warpPerspective(traffic, topvfull, wpmat, traffic.size());
		cropemptypic = topvemp(Rect(10, 20, 100, 50));
		croptrafficpic = topvfull(Rect(472, 52, 800 - 472, 830 - 52));
		cropemptypic = topvemp(Rect(472,52,800-472,830-52));
		imshow("Top Empty Image", topvemp);
		imshow("Cropped Empty Image", cropemptypic);
		imshow("Top Traffic Image", topvfull);
		imshow("Cropped Traffic Image", croptrafficpic);
		imwrite(path + "/croppedempty.jpg", cropemptypic);
		imwrite(path + "/croppedtraffic.jpg", croptrafficpic);
		imwrite(path + "/topempty.jpg", topvemp);
		imwrite(path + "/toptraffic.jpg", topvfull);
		src.clear();
	}
}

int main() {
	cout << "Enter directory path:\n";
	cin >> path;
	cout << "Enter empty image name:\n";
	cin >> empname;
	cout << "Enter traffic image name:\n";
	cin >> trafficname;
	string trafficpicloc = path+"/"+trafficname;//put image here
	string emptypicloc = path + "/"+empname;//put image here
	traffic = imread(trafficpicloc);
	emptypic = imread(emptypicloc);
	if ((!traffic.data)||(!emptypic.data)) {
		cout << "Images not Found";
		return 0;
	}
	cvtColor(emptypic, emptypic, COLOR_BGR2GRAY);
	cvtColor(traffic, traffic, COLOR_BGR2GRAY);
	imshow("Original Empty Image", emptypic);
	imshow("Original Traffic Image", traffic);
	setMouseCallback("Original Empty Image", mousePointsO, reinterpret_cast<void*>(&emptypic));
	waitKey(0);
	return 0;
}
