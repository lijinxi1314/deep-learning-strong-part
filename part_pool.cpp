#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>  
#include <vector>  
#include <iostream>  
#include <fstream>  
#include <cstring>  
#include <cstdlib>  
#include <cmath>  
#include <algorithm>  
#include <math.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <opencv2/core/core_c.h>
#include <opencv2/core/core.hpp>
#include <opencv2/flann/miniflann.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/photo/photo.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/highgui/highgui.hpp>
#include <windows.h>   
using namespace std;
using namespace cv;
#include<iostream> 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define	WIDTH	64
#define	HEIGHT	128

#define	M	3
#define	CELL_SIZE	floor(WIDTH/M)
#define	NUM_PARTPOOL	45
#define	NUM_W_CELL	1*M
#define	NUM_H_CELL	2*M
using namespace cv;
//Rect partPool[NUM_PARTPOOL] = {
//	 //시작셀(x, y(시작좌표), width, height)
//	{0, 0, 2, 2},{1,0,2,2},{0,1,2,2},{1,1,2,2},{0,2,2,2},{1,2,2,2},{ 0,3,2,2 },{ 1,3,2,2 },{ 0,4,2,2 },{ 1,4,2,2 },
//	{0,0,3,2},{0,1,3,2},{ 0,2,3,2 },{ 0,3,3,2 },{ 0,4,3,2 },
//	{0,0,2,3},{ 1,0,2,3 },{ 0,1,2,3 },{ 1,1,2,3 },{0,2,2,3 },{ 1,2,2,3 },{ 0,3,2,3 },{ 1,3,2,3 },
//	{0,0,3,3},{ 0,1,3,3 },{ 0,2,3,3 },{ 0,3,3,3 },
//	{0,0,2,4},{ 1,0,2,4 },{ 0,1,2,4 },{ 1,1,2,4 },{ 0,2,2,4 },{ 1,2,2,4 },
//	{0,0,3,4},{ 0,1,3,4 },{ 0,2,3,4 },
//	{0,0,2,5},{ 0,1,2,5 },{ 1,0,2,5 },{ 1,1,2,5 },
//	{0,0,3,5},{ 0,1,3,5 },
//	{ 0,0,2,6 },{ 1,0,2,6 },
//	{0,0,3,6}
//};
Rect partPool[NUM_PARTPOOL] = {
	//시작셀(x, y(시작좌표), width, height)
	{ 0,0,3,6 },{ 0,0,3,2 },{ 0,0,3,4 },{ 1,0,2,6 },{ 0,0,2,6 },{ 0,2,3,3 }
};


//////////////一张64*128 大小的图片的45种 part pool

int main(){
	char output[100];
	Mat matImage = imread("C:\\Users\\lijinxi\\Desktop\\picture_set03v011\\labeling_586_2.bmp");
	for (int i = 0; i < NUM_PARTPOOL; i++)
	{
		Mat part = matImage(Rect(partPool[i].x * CELL_SIZE, partPool[i].y * CELL_SIZE, partPool[i].width* CELL_SIZE, partPool[i].height*CELL_SIZE)).clone();
		sprintf_s(output, "C:\\Users\\lijinxi\\Desktop\\picture_set03v001\\586labeling_%d.bmp", i);
		imwrite(output, part);
	}
}

////////int main() {
////////	Mat matImage = imread("C:\\Users\\lijinxi\\Desktop\\picture_set03v011\\labeling_148_0.bmp");
////////	float t1 = 0;
////////	float t2 = 0;
////////	float width = 64;
////////	float height = 128;
////////	//45 prototypes
////////	///////////////              1(1)
////////	//1:part->full
////////	//cv::rectangle(matImage, cvPoint(t1, t2), cvPoint(t1+width, t2+height), Scalar(255, 0, 0), 1, 1, 0);
////////	//Mat croppedImg = matImage(cv::Rect(t1, t2, width, height)).clone();
////////
////////
////////	///////////////              2(10)
////////	//2(1): part->(2*2)
////////	//cv::rectangle(matImage, cvPoint(t1, t2), cvPoint(t1 + 2*width/3, t2 + height/3), Scalar(255, 0, 0), 1, 1, 0);
////////	//Mat croppedImg = matImage(cv::Rect(t1, t2, 2*width/3, height/3)).clone();
////////
////////	//2(2): part->(2*2)
////////	//cv::rectangle(matImage, cvPoint(t1+width/3, t2), cvPoint(t1 + width, t2 + height/3), Scalar(255, 0, 0), 1, 1, 0);
////////	//Mat croppedImg = matImage(cv::Rect(t1 + width / 3, t2, 2*width/3, height/3)).clone();
////////
////////	//2(3): part->(2*2)
////////	//cv::rectangle(matImage, cvPoint(t1, t2+height/6), cvPoint(t1 + 2*width/3, t2 + height/2), Scalar(255, 0, 0), 1, 1, 0);
////////	//Mat croppedImg = matImage(cv::Rect(t1, t2 + height / 6, 2*width/3, height/3)).clone();
////////
////////	//2(4): part->(2*2)
////////	//cv::rectangle(matImage, cvPoint(t1 + width / 3, t2 + height / 6), cvPoint(t1 + width, t2 + height / 2), Scalar(255, 0, 0), 1, 1, 0);
////////	//Mat croppedImg = matImage(cv::Rect(t1 + width / 3, t2 + height / 6, 2 * width / 3, height / 3)).clone();
////////
////////	//2(5): part->(2*2)
////////	//cv::rectangle(matImage, cvPoint(t1, t2+height/3), cvPoint(t1 + 2*width/3, t2 + 2*height/3), Scalar(255, 0, 0), 1, 1, 0);
////////	//Mat croppedImg = matImage(cv::Rect(t1, t2 + height / 3, 2*width/3, height/3)).clone();
////////
////////	//2(6): part->(2*2)
////////	//cv::rectangle(matImage, cvPoint(t1 + width / 3, t2 + height / 3), cvPoint(t1 + width, t2 + 2*height / 3), Scalar(255, 0, 0), 1, 1, 0);
////////	//Mat croppedImg = matImage(cv::Rect(t1 + width / 3, t2 + height / 3, 2 * width / 3, height / 3)).clone();
////////
////////	//2(7): part->(2*2)
////////	//cv::rectangle(matImage, cvPoint(t1, t2+height/2), cvPoint(t1 + 2*width/3, t2 + 5*height/6), Scalar(255, 0, 0), 1, 1, 0);
////////	//Mat croppedImg = matImage(cv::Rect(t1, t2+height/2, 2*width/3, height/3)).clone();
////////
////////	//2(8): part->(2*2)
////////	//cv::rectangle(matImage, cvPoint(t1 + width / 3, t2 + height / 2), cvPoint(t1 + width, t2 + 5*height / 6), Scalar(255, 0, 0), 1, 1, 0);
////////	//Mat croppedImg = matImage(cv::Rect(t1 + width / 3, t2 + height / 2, 2 * width / 3, height / 3)).clone();
////////
////////	//2(9): part->(2*2)
////////	//cv::rectangle(matImage, cvPoint(t1, t2+2*height/3), cvPoint(t1 + 2*width/3, t2 + height), Scalar(255, 0, 0), 1, 1, 0);
////////	//Mat croppedImg = matImage(cv::Rect(t1, t2 + 2 * height / 3, 2*width/3, height/3)).clone();
////////
////////	//2(10): part->(2*2)
////////	//cv::rectangle(matImage, cvPoint(t1 + width / 3, t2 + 2 * height / 3), cvPoint(t1 + width, t2 + height), Scalar(255, 0, 0), 1, 1, 0);
////////	//Mat croppedImg = matImage(cv::Rect(t1 + width / 3, t2 + 2 * height / 3, 2 * width / 3, height / 3)).clone();
////////
////////
////////	///////////////              3(5)
////////
////////	//3(1):part->(3*2)
////////	//cv::rectangle(matImage, cvPoint(t1, t2), cvPoint(t1+width, t2+height/3), Scalar(255, 0, 0), 1, 1, 0);
////////	//Mat croppedImg = matImage(cv::Rect(t1, t2, width, height/3)).clone();
////////
////////	//3(2):part->(3*2)
////////	//cv::rectangle(matImage, cvPoint(t1, t2 + height / 6), cvPoint(t1 + width, t2 + height / 2), Scalar(255, 0, 0), 1, 1, 0);
////////	//Mat croppedImg = matImage(cv::Rect(t1, t2 + height / 6,width, height/3)).clone();
////////
////////	//3(3):part->(3*2)
////////	//cv::rectangle(matImage, cvPoint(t1, t2+height/3), cvPoint(t1+width, t2+2*height/3), Scalar(255, 0, 0), 1, 1, 0);
////////	//Mat croppedImg = matImage(cv::Rect(t1, t2 + height / 3, width, height/3)).clone();
////////
////////	//3(4):part->(3*2)
////////	//cv::rectangle(matImage, cvPoint(t1, t2 + height / 2), cvPoint(t1 + width, t2 + 5*height / 6), Scalar(255, 0, 0), 1, 1, 0);
////////	//Mat croppedImg = matImage(cv::Rect(t1, t2 + height / 2, width, height / 3)).clone();
////////
////////	//3(5):part->(3*2)
////////	//cv::rectangle(matImage, cvPoint(t1, t2+2*height / 3), cvPoint(t1+width, t2+height), Scalar(255, 0, 0), 1, 1, 0);
////////	//Mat croppedImg = matImage(cv::Rect(t1, t2 + 2 * height / 3, width, height/3)).clone();
////////
////////	///////////////              4(8)
////////
////////	//4(1):part->(2*3)
////////	//cv::rectangle(matImage, cvPoint(t1, t2), cvPoint(t1+2*width/3, t2+height/2), Scalar(255, 0, 0), 1, 1, 0);
////////	//Mat croppedImg = matImage(cv::Rect(t1, t2, 2 * width / 3,height / 2)).clone();
////////
////////	//4(2):part->(2*3)
////////	cv::rectangle(matImage, cvPoint(t1 + width / 3, t2), cvPoint(t1 + width, t2 + height / 2), Scalar(255, 0, 0), 1, 1, 0);
////////	Mat croppedImg = matImage(cv::Rect(t1 + width / 3, t2,2 * width / 3,height / 2)).clone();
////////
////////	//4(3):part->(2*3)
////////	//cv::rectangle(matImage, cvPoint(t1, t2 + height / 6), cvPoint(t1+2*width/3, t2+2*height/3), Scalar(255, 0, 0), 1, 1, 0);
////////	//Mat croppedImg = matImage(cv::Rect(t1, t2, 2 * width / 3,height / 2)).clone();
////////
////////	//4(4):part->(2*3)
////////	//cv::rectangle(matImage, cvPoint(t1 + width / 3, t2), cvPoint(t1 + width, t2 + height / 2), Scalar(255, 0, 0), 1, 1, 0);
////////	//Mat croppedImg = matImage(cv::Rect(t1 + width / 3, t2,2 * width / 3,height / 2)).clone();
////////
////////
////////	namedWindow("hua");
////////	imshow("hua", matImage);
////////	imshow("hua", croppedImg);
////////	waitKey(6000);
////////}
