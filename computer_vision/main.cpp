//
//  main.cpp
//  computer_vision
//
//  Created by 김민채 on 9/28/25.
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

vector<Mat> LaplacianPyramid(const Mat& src){
	vector<Mat> ret;
	Mat org, half, resized;
	org = src.clone();
	for(int i = 0; i < 5; i++){
		pyrDown(org, half);
		pyrUp(half, resized, org.size());
		ret.push_back(org - resized);
		org = half;
	}
	ret.push_back(org);
	return ret;
}

vector<Mat> GaussianPyramid(const Mat& src){
	vector<Mat> ret;
	Mat current;
	current = src.clone();
	ret.push_back(current);
	for(int i = 1; i < 6; i ++){
		pyrDown(current, current);
		ret.push_back(current);
	}
	return ret;
}

Mat reconstruct(const vector<Mat>& pyr){
	Mat resized, low, up;
	low = pyr.back();
	for(int i = pyr.size() - 1; i > 0; i--){
		pyrUp(low, resized, pyr[i - 1].size());
		low = resized + pyr[i - 1];
	}
	return low;
}

int main(int argc, const char * argv[]) {
	Mat apple = imread("/Users/minchae/Xcode/computer_vision/computer_vision/burt_apple.png");
	Mat orange = imread("/Users/minchae/Xcode/computer_vision/computer_vision/burt_orange.png");
	Mat mask_apple = imread("/Users/minchae/Xcode/computer_vision/computer_vision/burt_mask.png");
	
	apple.convertTo(apple, CV_32F, 1/255.f);
	orange.convertTo(orange, CV_32F, 1/255.f);
	mask_apple.convertTo(mask_apple, CV_32F, 1/255.f);
	
	Mat mask_orange = Scalar(1, 1, 1) - mask_apple;
	
	auto l_apple = LaplacianPyramid(apple);
	auto l_orange = LaplacianPyramid(orange);
	auto g_apple = GaussianPyramid(mask_apple);
	auto g_orange = GaussianPyramid(mask_orange);
	
	vector<Mat> added;
	for(int i = 0; i < l_apple.size(); i++){
		Mat added_i, apple_part, orange_part;
		multiply(l_apple[i], g_apple[i], apple_part);
		multiply(l_orange[i], g_orange[i], orange_part);
		add(apple_part, orange_part, added_i);
		added.push_back(added_i);
	}
	
	Mat output = reconstruct(added);
	imshow("Output", output);
	waitKey();
	
	/*
	Mat output_8u;
	output.convertTo(output_8u, CV_8U, 255.0);
	imwrite("/Users/minchae/Xcode/computer_vision/computer_vision/output.png", output_8u);
	 */
	
	return 0;
}
