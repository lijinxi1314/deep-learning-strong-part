
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
using namespace std;
using namespace cv;
//FILE* file1 = fopen("C:\\Users\\VIP\\Desktop\\picture11\\2.txt", "r");



#define STR_DIR2 "C:\\Users\\VIP\\Desktop\\picture33\\videos\\V000"
int main()
{
	//char filename[200];
	//sprintf(filename, "%s/000%d.png", STR_DIR2, index);
	//filename... 
 //   _finddata_t fd;
 //   long handle;
 //   int result = 1;
 //   handle = _findfirst("E:\\code!!!\\*.*", &fd);  //현재 폴더 내 모든 파일을 찾는다.
 //
 //   if (handle == -1)
 //   {
 //       printf("There were no files.\n");
 //       return 0;
 //   }
 //
 //   while (result != -1)
 //   {
 //       printf("File: %s\n", fd.name);
 //       result = _findnext(handle, &fd);
 //   }
 //
 //   _findclose(handle);
 //   return 0;



	//_finddata_t fd;
	//long handle;
	//int result = 1;
	//char foldername[100];
	//sprintf(foldername, "C:\\Users\\VIP\\Desktop\\picture11\\");
	//handle = _findfirst("C:\\Users\\VIP\\Desktop\\picture11\\*.*", &fd);  //현재 폴더 내 모든 파일을 찾는다.

	/*if (handle == -1)
	{
		printf("There were no files.\n");
		return;
	}
*/
//char filename[100];
//char txtname[100];
//while (result != -1)
//{
//	//printf("File: %s\n", fd.name);
//	//sprintf(filename, "%s\\%s.png", foldername, fd.name);
//	//sprintf(txtname, "%s\\%s.txt", foldername, fd.name);
//	//C:\\Users\\EunjeongKo\\Documents\\카카오톡 받은 파일\\pddataset.docx
//	result = _findnext(handle, &fd);
//}





/*****************************KITTI***************************/
//ifstream myfile;
//myfile.open(file);
//char ifilename[200];
//char ofilename[200];
//char txtname[200];
//for (int i = 0; i < 2000; i++) {
//	Mat matImage;
//	char ID[100];
//	int number;
//	sprintf_s(ifilename, "%s\\%d.jpg", STR_DIR2, i);
//	sprintf_s(ofilename, "%s\\labeling_%d.bmp", STR_DIR2, i);
//	sprintf_s(txtname, "C:\\Users\\VIP\\Desktop\\picture11\\00%d.txt", i);
//	sprintf_s(ofilename, "%s/%d_labeing.png", STR_DIR2, i);
//	matImage = imread(ifilename, 1);
//
//	FILE* file1 = fopen("C:\\Users\\VIP\\Desktop\\picture11\\%d.txt", "r");
//	FILE* file;
//	file = fopen(txtname, "r");
//	/*float a[100][15];
//	for (int i = 0; i < 100; i++) {
//		for (int j = 0; j < 15; j++) {
//			if(a[0][j]=="Pedestrian")
//
//		}
//
//	}*/
//	for (int i = 0; i < 10; i++)
//	{
//		float t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14;
//		fscanf(file, "%s %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n", &ID, &t1, &t2, &t3, &t4, &t5, &t6, &t7, &t8, &t9, &t10, &t11, &t12, &t13, &t14);
//		
//	
//			if (t7 - t5 > 40) {
//				cv::rectangle(matImage, cvPoint(t4, t5), cvPoint(t6, t7), Scalar(255, 0, 255), 1, 1, 0);
//			}
//			else {
//				cv::rectangle(matImage, cvPoint(t4, t5), cvPoint(t6, t7), Scalar(0, 255, 0), 1, 1, 0);
//			}

//#define STR_DIR2 "E:\dataset\Caltech\code3.2.1\data-USA\videos\set00\V000"					

//	}
//*******************************************CALTECH****************************************//
	char ifilename[2000];
	char ofilename[2000];
	char txtname[20000];
	for (int i = 0; i < 1842; i++) {
		Mat matImage;
		char ID[10000];
		//int number;
		
		sprintf_s(ifilename, "%s\\%d.jpg", STR_DIR2, i);
		sprintf_s(ofilename, "%s\\labeling_%d.bmp", STR_DIR2, i);
		sprintf_s(txtname, "C:\\Users\\VIP\\Desktop\\picture33\\labeling\\set06V000\\%d.txt", i);
		matImage = imread(ifilename, 1);
		FILE* file;
		file = fopen(txtname, "r");
			
		matImage = imread(ifilename, 1);
		//sprintf_s(ofilename, "%s/%d_labeing.png", STR_DIR2, i);		
		for (int i = 0; i < 10; i++) {
			float t1, t2, t3, t4;
			
			fscanf(file, "%s %f %f %f %f\n", &ID, &t1, &t2, &t3, &t4);
			
			cv::rectangle(matImage, cvPoint(t1, t2), cvPoint(t3 + t1, t4 + t2), Scalar(255, 0, 255), 1, 1, 0);
			
		}
		imwrite(ofilename, matImage);
		imshow("picture", matImage);
		matImage.release();

	}
	
		waitKey(0);
		return 0;

		/*float t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14;

		fscanf(file, "%s %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n", &ID, &t1, &t2, &t3, &t4, &t5, &t6, &t7, &t8, &t9, &t10, &t11, &t12, &t13, &t14);

		cv::rectangle(matImage, cvPoint(t4, t5), cvPoint(t6, t7), Scalar(255, 255, 0), 1, 1, 0);*/
		//_findclose(handle);

	}

	


	////FILE* file1 = fopen("C:\\Users\\VIP\\Desktop\\picture11\\2.txt", "r");
	//	//Mat img = imread("C:\\Users\\VIP\\Desktop\\picture11\\1.png");
	//	char *imageSrc = "C:\\Users\\VIP\\Desktop\\picture11\\1.png";
	//	Mat matImage = imread(imageSrc, -1);
	//	//IplImage *iplImage = cvLoadImage(imageSrc, -1);


	//	if (matImage.data == 0 )
	//		//|| iplImage->imageData == 0)
	//	{
	//		cout << "falied" << endl;
	//		return -1;
	//	}
	//	char ID[15];

	//	FILE* file1 = fopen("C:\\Users\\VIP\\Desktop\\picture11\\1.txt", "r");

	//	float t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14;

	//	fscanf(file1, "%s %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n", &ID, &t1, &t2, &t3, &t4, &t5, &t6, &t7, &t8, &t9, &t10, &t11, &t12, &t13, &t14);
	//	//FILE* file2 = fopen("C:\\Users\\VIP\\Desktop\\picture11\\3.txt","w");

	//	//printf("%s %f %f %f %f\n", ID, t4, t5, t6, t7);

	//	cv::rectangle(matImage, cvPoint(t4, t5), cvPoint(t6, t7), Scalar(255, 0, 0), 1, 1, 0);
	//	//cv::rectangle(matImage, Rect(t4, t5, t6, t7), Scalar(0, 0, 255), 1, 1, 0);
	//	//cvRectangle(iplImage, cvPoint(t4, t5), cvPoint(t6, t7), Scalar(0, 255, 255), 1, 1, 0);


	//	namedWindow("picture");
	//	imshow("picture", matImage);
	//	
	//	imwrite("C:\\Users\\VIP\\Desktop\\picture11\\labeling_1.bmp", matImage);

	//	//cvSave("C:\\Users\\VIP\\Desktop\\picture11\\labeling_5.jpg", matImage);
	//	waitKey(0);
	//	fclose(file1);
	//	return 0;
	




