
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
#include<highgui.h> 
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
#include <io.h>
#include <conio.h>
#include <algorithm> 
#include <cv.h> 
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <string.h> 
#include <stdio.h>
#include <sys/types.h>

using namespace std;
using namespace cv;
///////////////////自动化处理图片，变为64*128大小

//1. directory 입력
#define	VIDEO_DIR	"D:\\piotr_toolbox1\\data\\Caltech\\test\\images"
#define	LABEL_DIR	"D:\\pedestrain_detector\\LDCF\\LDCF\\ldcf_test_expanded"
#define	SAVE_IMG_DIR	"D:\\pedestrain_detector\\LDCF\\LDCF\\ldcf_test_image"
////#define	VIDEO_DIR	"C:\\Users\\lijinxi\\Desktop\\picture33\videos\V001"
////#define	LABEL_DIR	"C:\\Users\\lijinxi\\Desktop\\caltech labeling\\set03v001"
////#define	SAVE_IMG_DIR	"D:\\pedestrain_detector\\LDCF\\LDCF\\ldcf_test_image"

vector<string> get_all_files_names_within_folder(string folder)
{
	vector<string> names;
	string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}
int main()
{
	//2. directory로부터 파일 리스트 가져오기

	vector<string> fileNames = get_all_files_names_within_folder(VIDEO_DIR);
	
	for (int i = 0; i < fileNames.size(); i++) //3. 각 파일에 대해서..
	{
		//3.1. 확장자 검사 ==> *.jpg, *.bmp, *.png인 경우에만 처리, 그 외에는 continue
		if (!(fileNames[i].compare(".jpg") ))//|| fileNames[i].compare(".bmp") || fileNames[i].compare(".png")
			continue;
		char input[200];
		sprintf(input, "%s\\%s", VIDEO_DIR, fileNames[i].c_str());
		char ofilename[200];
		
		//cout << "Done: " << fileNames[i] << endl;
		//cout << "Done: " << txtfilename << endl;
		
		//////3.2. 텍스트로 확장자 변경
		char txt_filepath[200];
		int idx = fileNames[i].find_last_of(".", fileNames[i].length()); //0.jpg "."의 위치를 찾음
		string txtfilename = fileNames[i].substr(0, idx) + ".txt"; //"."위치 전까지 파일 이름 가져왔음.
		sprintf(txt_filepath, "%s\\%s", LABEL_DIR, txtfilename.c_str());

		//
		//3.3. 텍스트 로드

		//sprintf(txt, "%s\\%s", LABEL_DIR, txtfilename);
		//cout << txt << endl;
		//cout << "Done: " << fileNames[i].c_str() << endl;
		Mat matImage = imread(input,1);
		//cout << "Done: " << matImage << endl;

	
		////FILE* file = fopen(txt, "r");

		//cout << "yes" << txt << endl;

		std::ifstream ifile(txt_filepath);
		if (matImage.data==0)// || file == nullptr
			cout << "fill" << endl;
			continue;

		////3.3.1. 한줄씩 읽어오기 [반복문/마지막 라인까지]
		int idx1;
		string line;
		vector<Rect> rects;
		while (std::getline(ifile, line))///////line by line to read ldcf txt on 1.txt
		{
			//cout << idx1++ << "\t" << line << endl;
			Rect r;
			std::string delimiter = "\t";
			size_t pos = 0;
			std::string token;
			vector<string> sarray;
			while ((pos = line.find(delimiter)) != std::string::npos) {
				token = line.substr(0, pos);
				sarray.push_back(token);
				line.erase(0, pos + delimiter.length());
			}
			sarray.push_back(line);
			r.x = atoi(sarray[0].c_str());
			r.y = atoi(sarray[1].c_str());
			r.width = atoi(sarray[2].c_str());
			r.height = atoi(sarray[3].c_str());
			cout << r.x << "\t" << r.y << "\t" << r.width << "\t" << r.height << endl;
			rects.push_back(r);
			sarray.clear();
		}
		for (int m = 0; m < rects.size(); m++) {
			Mat imageROI;
			Rect t = rects[i];
			t.x = t.x + t.width / 2 - t.height / 4;
			t.y = t.y;
			t.width = t.height / 2;
			t.height = t.height;
			/*Rect rect(r.x + r.width / 2 - r.height / 4, r.y, r.height / 2, r.height);*/
			//Rect rect(t1 + t3 / 2 - t4 / 4, t2, t4 / 2, t4);///////////change size
			matImage(t).copyTo(imageROI);


			//Rect rect;
			//int t1, t2, t3, t4;
			////fscanf(file, "%d %f %f %f %f\n", &imgID, &(rect.left), &(rect.top), &(rect.right), &(rect.bottom));
			//fscanf(file, " %d %d %d %d\n",  &t1, &t2, &t3, &t4);

			//3.3.2. 사람인 경우,
			//Mat croppedImg = matImage(cv::Rect(t1 + t3 / 2 - t4 / 4, t2, t4 / 2, t4)).clone();
			Mat resizeImg;
			resize(imageROI, resizeImg, cv::Size(64, 128), 0, 0, CV_INTER_CUBIC);
			sprintf_s(ofilename, "%s\\labeling_%d.bmp", SAVE_IMG_DIR, i);
			cout << "Done: " << resizeImg << endl;
			imwrite(ofilename, resizeImg);
		}


		//////while (!feof(file)) {
		//////	cout << "Done: " << txtfilename << endl;

		//////	int ID;
		//////	Rect rect;
		//////	float t1, t2, t3, t4;
		//////	//fscanf(file, "%d %f %f %f %f\n", &imgID, &(rect.left), &(rect.top), &(rect.right), &(rect.bottom));
		//////	fscanf(file, "%d %f %f %f %f\n", &ID, &t1, &t2, &t3, &t4);

		//////	//3.3.2. 사람인 경우,
		//////	Mat croppedImg = matImage(cv::Rect(t1 + t3 / 2 - t4 / 4, t2, t4 / 2, t4)).clone();
		//////	Mat resizeImg;
		//////	resize(croppedImg, resizeImg, cv::Size(64, 128), 0, 0, CV_INTER_CUBIC);
		//////	sprintf_s(ofilename, "%s\\labeling_%d.bmp", SAVE_IMG_DIR, i);
		//////	cout << "Done: " << resizeImg << endl;
		//////	imwrite(ofilename, resizeImg);
		//////}
		//사람 여러개 있으면
		//////////while (!feof(file))
		//////////{
		//////////	int imgID;
		//////////	vector<cv::Rect> rects;
		//////////	float t1, t2, t3, t4;
		//////////	//fscanf(file, "%d %f %f %f %f\n", &imgID, &(rect.left), &(rect.top), &(rect.right), &(rect.bottom));
		//////////	fscanf(file, "%d %f %f %f %f\n", &imgID, &t1, &t2, &t3, &t4);
		//////////	cv::rectangle(matImage, cvPoint(t1, t2), cvPoint(t1+t3, t2+t4), Scalar(255, 0, 0), 1, 1, 0);
		//////////	sprintf_s(ofilename, "%s\\labeling_%d.bmp", SAVE_IMG_DIR, i);
		//////////	imwrite(ofilename, matImage);


		//3.3.2. 사람인 경우,
		/*for (int k = 0; k < rects.size(); k++) {
		Mat croppedImg = matImage(cv::Rect(t1 + t3 / 2 - t4 / 4, t2, t4 / 2, t4)).clone();
		Mat resizeImg;
		resize(croppedImg, resizeImg, cv::Size(64, 128), 0, 0, CV_INTER_CUBIC);
		sprintf_s(ofilename, "%s\\labeling_%d.bmp", SAVE_IMG_DIR, i);
		}
		*/
		//cout << "Done: " << resizeImg << endl;

		//45개 partpool 추출

		rects.clear();


		//fclose(file);
	}
	return 0;
}
