
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
#include <stdio.h>
#include <io.h>
#include <conio.h>
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
#include<highgui.h> 
#include <cv.h> 
using namespace std;
using namespace cv;
#define STR_DIR2 "D:\\piotr_toolbox1\\data\\Caltech\\test\\nooverlapped_image"
///////////正规化图片为64*128大小。。。。手动法
int main()
{
	char ifilename[2000];
	char ofilename[2000];
	char txtname[20000];
	for (int i = 0; i < 5; i++) {
		Mat matImage;
		//Mat imageROI;
		//char ID[10000];
		int ID;
		//int number;

		sprintf_s(ifilename, "%s\\set06_V000_I00029_%d.jpg", STR_DIR2, i);
		//sprintf_s(ofilename, "C:\\Users\\lijinxi\\Desktop\\picture_set10v009\\labeling_%d.bmp", i);
		sprintf_s(txtname, "D:\\piotr_toolbox1\\data\\Caltech\\test\\nooverlapped\\set06_V000_I00029.txt");
		matImage = imread(ifilename, 1);
		FILE* file = fopen(txtname, "r");

		matImage = imread(ifilename, 1);
		//sprintf_s(ofilename, "%s/%d_labeing.png", STR_DIR2, i);		
		////for (int j = 0; j < 10; j++) {
		////	float t1, t2, t3, t4;
		////	
		////	fscanf(file, "%d %f %f %f %f\n", &ID, &t1, &t2, &t3, &t4);

		////	//cv::rectangle(matImage, cvPoint(t1, t2), cvPoint(t3 + t1, t4 + t2), Scalar(255, 0, 255), 1, 1, 0);
		////	
		////	Rect rect(t1, t2, t3, t4);
		////	matImage(rect).copyTo(imageROI);
		////	sprintf_s(ofilename, "C:\\Users\\lijinxi\\Desktop\\picture233\\labeling_%d_%d.bmp", STR_DIR2, i, j);
		////	imwrite(ofilename,imageROI);

		////	imageROI.release();
		std::vector<cv::Rect> rects;
		for (size_t j = 0; j < 5; j++)
		{
			float t1, t2, t3, t4;
			fscanf(file, "%d %f %f %f %f\n", &ID, &t1, &t2, &t3, &t4);
			rects.push_back(cv::Rect(t1 + t3 / 2 - t4 / 4, t2, t4 / 2, t4));
		}
		std::vector<Mat> subImages;
		for (int k = 0; k < rects.size(); k++)
		{
			Mat tempImg;
			matImage(rects[k]).copyTo(tempImg);
			subImages.push_back(tempImg);
			Mat changeimage;
			resize(tempImg, changeimage, cv::Size(64, 128), 0, 0, CV_INTER_CUBIC);
			sprintf_s(ofilename, "D:\\piotr_toolbox1\\data\\Caltech\\test\\normalization\\labeling_%d_%d.bmp", i, k);

			imwrite(ofilename, changeimage);


		}
		//imwrite(ofilename, imageROI);
		//imwrite(ofilename, matImage);
		//imshow("picture", matImage);
		//matImage.release();
		//waitKey(0);
	}


	//namedWindow("pict", WINDOW_AUTOSIZE );


	return 0;
}
//int main() {
//	//텍스트 불러와서 rectangle / text 이미지에 출력하는 코드
//		ifstream read;
//			read.open("D:\piotr_toolbox1\data\Caltech\savepath_labeling\test2.txt", ios::in);
//			if (read.fail())
//				return 0;
//
//			Mat img = imread("D:\piotr_toolbox1\data\Caltech\savepath_labeling\set06_V000_I00029.jpg", CV_LOAD_IMAGE_COLOR);
//			while (!read.eof())
//			{
//				if (read.empty())
//					break;
//
//				Rect position;
//				float number;
//				read >> number;
//				position.x = number < 0 ? 0 : number;
//				read >> number;
//				position.y = number < 0 ? 0 : number;
//				read >> number;
//				position.width = number < 0 ? 0 : number;
//				read >> number;
//				position.height = number < 0 ? 0 : number;
//				read >> number;
//				float prob = number;
//				rectangle(img, position, Scalar(0, 255, 0), 2);
//				char probs[100];
//				sprintf(probs, "%.2f", prob);
//				int myFontFace = 2;
//				double myFontScale = 0.4;
//				cout << filename << "\t";;
//				putText(img, probs, Point(position.x, position.y), myFontFace, myFontScale, Scalar(255, 255, 255));
//				cout << position.x << "\t" << position.y << "\t" << position.width << "\t" << position.height << endl;
//			}
//	imwrite("D:\piotr_toolbox1\data\Caltech\savepath_labeling\set06_V000_I00029_mapped.jpg", img);
//	read.close();
//}
