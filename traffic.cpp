//C:\Users\User\Desktop\TrafficCV
//g++ topview.cpp -o test -pthread -std=c++11 `pkg-config --cflags --libs opencv`

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

vector<Point2f> src,dst;
Mat topvemp, topvfull, emptypic, traffic,wpmat, cropemptypic, croptrafficpic;
Mat vidframe, flow, prevframe;
string empname,trafficname,videoloc;

void playvideo() {
	VideoCapture cap(videoloc);
	while (true) {
		cap.read(vidframe);
		cvtColor(vidframe, vidframe, COLOR_BGR2GRAY);
		absdiff(vidframe, emptypic, vidframe);
		threshold(vidframe, vidframe, 50.0, 100.0, THRESH_BINARY);
		warpPerspective(vidframe, vidframe, wpmat, vidframe.size());
		vidframe = vidframe(Rect(472, 52, 800 - 472, 830 - 52));
		int movingcount = 0;
		int staticcount = 0;
		int framenum=cap.get(CAP_PROP_POS_FRAMES);
		if (prevframe.empty() == false) {
			calcOpticalFlowFarneback(prevframe, vidframe, flow, 0.4, 1, 12, 2, 8, 1.2, 0);
			for (int y = 0; y < vidframe.rows; y += 5) {
				for (int x = 0; x < vidframe.cols; x += 5) {
					Point2f flowatxy = flow.at<Point2f>(y, x) / 5;
					int intensity = (int)vidframe.at<uchar>(y, x);
					int pixelval = pow(flowatxy.x,2.0)+pow(flowatxy.y,2.0);
					if (intensity > 50) {
						if (pixelval > 1.0) {
							movingcount++;
						}
						else {
							staticcount++;
						}
					}
				}
			}
		}
		cout << framenum<<" "<< movingcount <<" "<< staticcount << "\n";
		imshow("Video", vidframe);
		waitKey(50);
		prevframe = vidframe;
	}
}
void mousePointsO(int event, int x, int y, int flags, void* params) {
	Mat* image = reinterpret_cast<Mat*>(params);
	if (event == EVENT_LBUTTONDOWN) {
		src.push_back(Point2f(x, y));
	}
	if (src.size() == 4) {
		dst = { {472.0f,52.0f},{472.0f,830.0f},{800.0f,830.0f},{800.0f,52.0f} };//values used by instructor
		wpmat = findHomography(src, dst);
		warpPerspective(emptypic, topvemp, wpmat, emptypic.size());
		warpPerspective(traffic, topvfull, wpmat, traffic.size());
		cropemptypic = topvemp(Rect(10, 20, 100, 50));
		croptrafficpic = topvfull(Rect(472, 52, 800 - 472, 830 - 52));
		cropemptypic = topvemp(Rect(472,52,800-472,830-52));
		src.clear();
		playvideo();
	}
}
int main() {
	/*cout << "Enter empty image directory and name:\n";
	cin >> empname;
	cout << "Enter traffic image directory and name:\n";
	cin >> trafficname;*/
	empname = "C:/Users/User/Desktop/TrafficCV/empty.jpg";//removelater
	trafficname = "C:/Users/User/Desktop/TrafficCV/empty.jpg";//removelater
	videoloc = "C:/Users/User/Desktop/TrafficCV/trafficvideo.mp4";//removelater
	string trafficpicloc =trafficname;//put image here
	string emptypicloc =empname;//put image here
	traffic = imread(trafficpicloc);
	emptypic = imread(emptypicloc);
	cvtColor(emptypic, emptypic, COLOR_BGR2GRAY);
	cvtColor(traffic, traffic, COLOR_BGR2GRAY);
	if ((!traffic.data)||(!emptypic.data)) {
		cout << "Images not Found";
		return 0;
	}
	imshow("Original Empty Image", emptypic);
	//imshow("Original Traffic Image", traffic);
	setMouseCallback("Original Empty Image", mousePointsO, reinterpret_cast<void*>(&emptypic));
	waitKey(0);
	return 0;
}
