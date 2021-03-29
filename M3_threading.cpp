//C:\Users\User\Desktop\TrafficCV
//g++ topview.cpp -o test -pthread -std=c++11 `pkg-config --cflags --libs opencv`

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <string>
#include <vector>

using namespace cv;
using namespace std;


vector<Point2f> src,dst;
Mat emptypic ,wpmat;
Mat vidframe, prevframe;
string empname,videoloc;
string emptypicloc;
int globalcount=0;
int movingcount,queuecount;
int gap;
int numthreads=4;

void* subplayvideo( void* arg){
	int ith=globalcount++;
	int last= (ith+1) * gap;
	int start= ith * gap;
	Mat flow;
	if (ith==numthreads-1){last=vidframe.cols;}
	Mat curframe=vidframe(Range::all(), Range(start,last));
	int movingcountt = 0;
		int queuecountt = 0;
	if (prevframe.empty() == false) {
			Mat prevpart=prevframe(Range::all(), Range(start,last));
			calcOpticalFlowFarneback(prevpart, curframe, flow, 0.4, 1, 12, 2, 8, 1.2, 0);
			for (int y = 0; y < curframe.rows; y += 5) {
				for (int x = 0; x < curframe.cols; x += 5) {
					Point2f flowatxy = flow.at<Point2f>(y, x) / 5;
					int intensity = (int)curframe.at<uchar>(y, x);
					int pixelval = pow(flowatxy.x,2.0)+pow(flowatxy.y,2.0);
					if (intensity > 50) {
						if (pixelval > 1.0) {
							movingcountt++;
						}
						queuecountt++;
					}
				}
			}
	}
	movingcount+=movingcountt;
	queuecount+=queuecountt;
	pthread_exit(0);
}
int main() {
	time_t start=time(NULL);
	ofstream file("M3_threading"+to_string(numthreads)+".csv");
	file<<"Frame Number,Moving Density,Queue Density\n";
	//cout << "Enter empty image and video directory name in separate lines:"<<endl;
	videoloc="/home/lkm/opencv_test/trafficvideo.mp4";
	//cin >> empname;
	//cin >> videoloc;
	emptypicloc ="/home/lkm/opencv_test/traffic.jpg";//put image here
	emptypic = imread(emptypicloc);
	cvtColor(emptypic, emptypic, COLOR_BGR2GRAY);
	if (!emptypic.data) {
		cout << "Image not Found"<<endl;
		return 0;
	}
	//imshow("Original Empty Image", emptypic);
	src = { {946.0f,260.0f},{523.0f,1066.0f},{1558.0f,1070.0f},{1294.0f,252.0f} };//hardcoded values for rapid testing
	dst = { {472.0f,52.0f},{472.0f,830.0f},{800.0f,830.0f},{800.0f,52.0f} };//values used by instructor
	wpmat = findHomography(src, dst);
	VideoCapture cap(videoloc);
	//ofstream out("C:/Users/User/Desktop/TrafficCV/out.txt");
	//out << "Frame Number" << "," << "Moving Density" << "," << "Queue Density" << "\n";
	while (cap.read(vidframe)==true) {
		cvtColor(vidframe, vidframe, COLOR_BGR2GRAY);
		absdiff(vidframe, emptypic, vidframe);
		threshold(vidframe, vidframe, 50.0, 100.0, THRESH_BINARY);
		warpPerspective(vidframe, vidframe, wpmat, vidframe.size());
		vidframe = vidframe(Rect(472, 52, 800 - 472, 830 - 52));
		movingcount = 0;
		queuecount = 0;
		gap=vidframe.cols / numthreads;
		int framenum=cap.get(CAP_PROP_POS_FRAMES);
		globalcount=0;
		pthread_t tids[numthreads];
		for (int i = 0; i < numthreads; i++) {
			pthread_attr_t attr;
			pthread_attr_init(&attr);
			pthread_create(&tids[i], &attr, subplayvideo, NULL);
			//waitKey(300);
		}
		for (int k = 0; k < numthreads; k++) {
			pthread_join(tids[k], NULL);
		}
		string st=to_string(framenum)+","+to_string(movingcount)+","+to_string(queuecount)+"\n";
		cout<<framenum<<endl;
		file<< st;
		
		//cout << framenum<<","<< movingcount <<","<< queuecount <<endl;
		//out << framenum << "," << movingcount << "," << queuecount << "\n";
		//imshow("Video", vidframe);
		//waitKey(30);
		prevframe = vidframe;
	}
	file.close();
	destroyAllWindows();
	//out.close();
	//waitKey(0);
	cout<<time(NULL)-start;
	return 0;
}
