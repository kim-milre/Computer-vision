//
//  main.cpp
//  HW2_HoughCircleDetector
//
//  Created by 김민채 on 10/23/25.
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;


int main(int argc, const char * argv[]) {
	Mat img, gray;

	if(argc != 2){
		cout << "Usage: ./HW2_HoughCircleDetector <image_path>" << endl;
		return -1;
	}
	img = imread(argv[1], IMREAD_COLOR);
	if(img.empty()){
		cout << "Could not open image: " << argv[1] << endl;
		return -1;
	}
	cvtColor(img, gray, COLOR_BGR2GRAY);
	medianBlur(gray, gray, 7);
	vector<Vec3f> circles;
	HoughCircles(gray, circles, HOUGH_GRADIENT, 1, 40, 60, 60, 20, 100);
	for( size_t i = 0; i < circles.size(); i++){
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		circle(img, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		circle(img, center, radius, Scalar(0, 0, 255), 3, 8, 0);
	}
	cout << "Detected coin count : " << circles.size() << endl;
	
	namedWindow("Coins", 1);
	imshow("Coins", img);
	waitKey();
	
	return 0;
}
