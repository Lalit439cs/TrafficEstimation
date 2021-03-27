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

	vector<Scalar> colors;
	RNG rng;
	for (int i = 0; i < 100; i++)
	{
		int r = rng.uniform(0, 256);
		int g = rng.uniform(0, 256);
		int b = rng.uniform(0, 256);
		colors.push_back(Scalar(r, g, b));
	}

	Mat old_frame, old_gray;
	vector<Point2f> oldtracks, newtracks;
	cap >> old_frame;
	cvtColor(old_frame, old_gray, COLOR_BGR2GRAY);

	absdiff(old_gray, emptypic, old_gray);
	threshold(old_gray, old_gray, 50.0, 100.0, THRESH_BINARY);
	warpPerspective(old_gray, old_gray, wpmat, old_gray.size());
	old_gray = old_gray(Rect(472, 52, 800 - 472, 830 - 52));
	goodFeaturesToTrack(old_gray, oldtracks, 100, 0.3, 7, Mat(), 7, false, 0.04);
	Mat mask = Mat::zeros(old_gray.size(), old_gray.type());
	int trackcounter = 0;

	while (cap.read(vidframe) == true) {
		trackcounter++;
		Mat grayvidframe;
		cvtColor(vidframe, grayvidframe, COLOR_BGR2GRAY);

		absdiff(grayvidframe, emptypic, grayvidframe);
		threshold(grayvidframe, grayvidframe, 50.0, 100.0, THRESH_BINARY);
		warpPerspective(grayvidframe, grayvidframe, wpmat, grayvidframe.size());
		grayvidframe = grayvidframe(Rect(472, 52, 800 - 472, 830 - 52));

		vector<uchar> status;
		vector<float> err;
		TermCriteria criteria = TermCriteria((TermCriteria::COUNT)+(TermCriteria::EPS), 10, 0.03);
		calcOpticalFlowPyrLK(old_gray, grayvidframe, oldtracks, newtracks, status, err, Size(15, 15), 2, criteria);

		vector<Point2f> good_new;
		for (uint i = 0; i < oldtracks.size(); i++)
		{
			if (status[i] == 1) {
				good_new.push_back(newtracks[i]);
				line(mask, newtracks[i], oldtracks[i], colors[i], 2);
				circle(vidframe, newtracks[i], 5, colors[i], -1);
			}
		}
		Mat img;
		add(grayvidframe, mask, img);
		imshow("Frame", img);
		int framenum = cap.get(CAP_PROP_POS_FRAMES);
		int movingcount = 0;
		int queuecount = 0;
		int loopsize;
		if (newtracks.size() > oldtracks.size()) {
			loopsize = newtracks.size();
		}
		else {
			loopsize = oldtracks.size();
		}
		for (int i = 0; i < loopsize; i++) {
			Point2f dist = newtracks[i] - oldtracks[i];
			if (dist.x * dist.x + dist.y * dist.y >= 4) {
				movingcount++;
			}
			else {
				queuecount++;
			}
		}
		cout <<framenum<<","<< movingcount << "," << queuecount << endl;
		waitKey(30);
		old_gray = grayvidframe.clone();
		oldtracks = good_new;
	}
}

void startprocess() {
	src = { {946.0f,260.0f},{523.0f,1066.0f},{1558.0f,1070.0f},{1294.0f,252.0f} };//hardcoded values for rapid testing
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
	string emptypicloc = "C:/Users/Arka-LAPPY/Desktop/TrafficCV/empty.jpg";//remove later
	videoloc = "C:/Users/Arka-LAPPY/Desktop/TrafficCV/trafficvideo.mp4";//remove later
	emptypic = imread(emptypicloc);
	cvtColor(emptypic, emptypic, COLOR_BGR2GRAY);
	if (!emptypic.data) {
		cout << "Image not Found";
		return 0;
	}
	startprocess();
	return 0;
}