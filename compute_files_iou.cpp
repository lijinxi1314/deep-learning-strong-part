/////////////////////positive,height>50 positive,negative,height>50 negative, ground truth 안에서 사람이 있어요,근데 LDCF 인식 못해서..이런 것 NOTdetect 설정한다.
/////////////////////   test, train04 모두 file 결과 나와다.
///////////////////// check 수량
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
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
#include <vector>  
#include <string>  
#include <fstream>  
#include <iostream>
#include  <assert.h>
#include <tchar.h>
#include <stdio.h>
#include <string.h> 
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
using namespace std;
using namespace cv;
//#define	WIDTH	64
//#define	HEIGHT	128
//
//#define	M	3
//#define	CELL_SIZE	floor(WIDTH/M)
//#define	NUM_PARTPOOL	45
//#define	NUM_W_CELL	1*M
//#define	NUM_H_CELL	2*M
//using namespace cv;
//Rect partPool[NUM_PARTPOOL] = {
//	//시작셀(x, y(시작좌표), width, height)
//	{0,0,3,6},{0,0,3,2},{ 0,0,3,4 },{1,0,2,6},{0,0,2,6},{0,2,3,3}
//};

/////////iou 계산
float calculateIoUFrom(Rect r1, Rect r2)
{
	float iou = 0;
	float x1, y1, x2, y2, width1, height1, width2, height2;

	x1 = r1.x;
	y1 = r1.y;
	width1 = r1.width;
	height1 = r1.height;

	x2 = r2.x;
	y2 = r2.y;
	width2 = r2.width;
	height2 = r2.height;

	float endx, startx, width;
	endx = max(x1 + width1, x2 + width2);
	startx = min(x1, x2);
	width = width1 + width2 - (endx - startx);
	float endy, starty, height;
	endy = max(y1 + height1, y2 + height2);
	starty = min(y1, y2);
	height = height1 + height2 - (endy - starty);

	if (width <= 0 || height <= 0) {
		iou = 0;
	}
	else {
		float Area, Area1, Area2;
		Area = width*height;
		Area1 = width1*height1;
		Area2 = width2*height2;
		iou = Area*1. / (Area1 + Area2 - Area);
	}


	return iou;
}

#define LDCF_DIR "D:\\piotr_toolbox1\\data\\Caltech\\train04\\ldcf"
#define GT_DIR "D:\\piotr_toolbox1\\data\\Caltech\\train04\\annotations"
//#define LDCF_DIR "D:\\piotr_toolbox1\\data\\Caltech\\test\\test_ldcf"
//#define GT_DIR "D:\\piotr_toolbox1\\data\\Caltech\\train04\\test_gt"
#define POS_DIR "D:\\piotr_toolbox1\\data\\Caltech\\train04\\positive"
#define NEG_DIR "D:\\piotr_toolbox1\\data\\Caltech\\train04\\negative"
#define NOTDETECT_DIR "D:\\piotr_toolbox1\\data\\Caltech\\train04\\notdetect"
#define LARGE_POS_DIR "D:\\piotr_toolbox1\\data\\Caltech\\train04\\large_positive"
#define LARGE_NEG_DIR "D:\\piotr_toolbox1\\data\\Caltech\\train04\\large_negative"
#define NOOVERLAP "D:\\piotr_toolbox1\\data\\Caltech\\train04\\nooverlapped"
#define	IOU_TH_VAL	0.5
/////////directory 설정
using namespace std;

vector<string> get_all_files_names_within_folder(string folder)
{
	vector<string> names;
	string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
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
	//Rect r1;
	//Rect r2;
	//=> 학습 테스트 다해야함.
	//directory 설정
	//directory  "D:\piotr_toolbox1\data\Caltech\test\annotations"
	//파일 리스트 가져오기

	//for (int i = 0; i < 파일개수; i++)
	//{
	//	if (파일이름[i].compare(".txt"))
	//	{
	//		//현재 텍스트 파일 로드.(파일1)
	//		//파일 경로를 바꿔서 LDCF 파일 로드 (파일2)
	//		//파일1
	//		vector<Rect> gtrect;
	//		while (파일 각 라인 읽어오기)
	//		{
	//			Rect r;
	//			//r ==> 값을 읽어옴
	//			gtrect.push_back(r);
	//		}

	//		//파일2
	//		vector<Rect> ldcfrect;
	//		while (파일 각 라인 읽어오기)
	//		{
	//			Rect r;
	//			//r ==> 값을 읽어옴
	//			ldcfrect.push_back(r);
	//		}
	//		//IoU 비교
	//		//IoU > 0.5
	//		//gtrect, ldcfrect IoU 호출하면 보다 높으면 positive
	//		//negative로 LDCF 좌표 정보 저장해야함.. 
	//		//만약에 bounding box에 오버랩되는 애가 없음 ==> positive가 없으면... 
	//		//positive 없는 애들 gtrect 좌표 정보 저장.
	//		//저장할때 파일이름은 그대로 쓰고 디렉토리만 바꿔서 텍스트 저장

	//	}
	//}


	///////파일 리스트 가져오기
	//vector<string> fileNames_ldcf = get_all_files_names_within_folder(LDCF_DIR);
	vector<string> fileNames_gt = get_all_files_names_within_folder(GT_DIR);
	
	int positive = 0;
	//int largepositive = 0;
	int negative = 0;
	int largenegative = 0;
	int nooverlapped = 0;

	int nodetected = 0;
	int iou_number = 0;

	int iou = 0;
	int ldcf = 0;
	int fneg = 0;
	int fullgt = 0;

	//FILE* fstat = fopen("D:\\piotr_toolbox1\\data\\Caltech\\train04\\train.txt", "w");
	for (int i = 0; i < fileNames_gt.size(); i++) {//ground truth list 가져오기,get the ground truth size 
		//read ground truth .txt file
		if (!(fileNames_gt[i].compare(".txt")))
			continue;

		char filepath[300];
		char ldcf_filepath[300];
		char gt_filepath[300];

		/////read LDCF txt,read ground truth txt
		sprintf(ldcf_filepath, "%s\\%s", LDCF_DIR, fileNames_gt[i].c_str());
		sprintf(gt_filepath, "%s\\%s", GT_DIR, fileNames_gt[i].c_str());
		/////filepath :the path of positive dir,negative dir ,notdetect dir ,write txt result to positive dir,nehative dir ,notdetect dir 
		sprintf(filepath, "%s\\%s", POS_DIR, fileNames_gt[i].c_str());
		/*FILE* file = fopen(filepath, "w");
		fclose(file);
		sprintf(filepath, "%s\\%s", NEG_DIR, fileNames_gt[i].c_str());
		file = fopen(filepath, "w");
		fclose(file);
		sprintf(filepath, "%s\\%s", NOTDETECT_DIR, fileNames_gt[i].c_str());
		file = fopen(filepath, "w");
		fclose(file);*/

		/////input ldcf,gt file
		std::ifstream ldcf_file(ldcf_filepath);
		std::ifstream gt_file(gt_filepath);

		string line;
		vector<Rect> ldcfrects;
		//cout << "LDCF" << endl;
		int idx = 0;
		while (std::getline(ldcf_file, line))///////line by line to read ldcf txt on 1.txt
		{
			//cout << idx++ <<"\t" << line << endl;
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
			r.x = atoi(sarray[1].c_str());
			r.y = atoi(sarray[2].c_str());
			r.width = atoi(sarray[3].c_str());
			r.height = atoi(sarray[4].c_str());
			//cout << r.x << "\t" << r.y << "\t" << r.width << "\t" << r.height << endl;
			ldcfrects.push_back(r);
			sarray.clear();
		}

		///////ground truth bounding box...
		vector<Rect> gtrects;
		//cout << "GT" << endl;
		while (std::getline(gt_file, line))///////line by line to read ground truth txt on 1.txt
		{
			//cout << idx++ << "\t" << line << endl;
			Rect r;
			std::string delimiter = " ";
			size_t pos = 0;
			std::string token;
			vector<string> sarray;
			//cout << line << "\t";
			while ((pos = line.find(delimiter)) != std::string::npos) {
				token = line.substr(0, pos);
				sarray.push_back(token);
				line.erase(0, pos + delimiter.length());
			}
			//cout << sarray.size() << endl;
			if (sarray.size() < 3)
				continue;

			r.x = atoi(sarray[1].c_str());
			r.y = atoi(sarray[2].c_str());
			r.width = atoi(sarray[3].c_str());
			r.height = atoi(sarray[4].c_str());

			//cout << r.x << "\t" << r.y << "\t" << r.width << "\t" << r.height << endl;
			gtrects.push_back(r);
			sarray.clear();
		}
		fullgt += gtrects.size();
		///////groud truth rectangle ,first all the groud truth rectangle is false
		//////// bool==>false,true
		///////LDCF rectangle ,first all the LDCF rectangle is false
		//////// bool==>false,true

		bool* isGT = new bool[gtrects.size()];
		for (int m = 0; m < gtrects.size(); m++)//j
			isGT[m] = false;

		for (int m = 0; m < ldcfrects.size(); m++)////// read idcf rectangle from 0 to end on 1.txt
		{
			float maxIoU = 0;
			for (int n = 0; n < gtrects.size(); n++)////// read gt rectangle from 0 to end on 1.txt
			{
				///////IoU 비교 gtrect, ldcfrect IoU 호출하면 보다 높으면 positive==>isLD[m] = true,isGT[n] = true==>출력
				float iouVal = calculateIoUFrom(gtrects[n], ldcfrects[m]);
				if (maxIoU < iouVal)
					maxIoU = iouVal;

				//cout << iouVal << endl;
				if (iouVal >= IOU_TH_VAL)
					isGT[n] = true;
			}
			//cout << "max: " <<maxIoU << endl;

			//rect ==> 0.1 0.3 0.5 ==> max(0.1 0.3 0.5) => 0.5 >= 0.5 ==> positive

			if (maxIoU >= IOU_TH_VAL)
			{
				positive++;
				//save to positive
				sprintf_s(filepath, "%s\\%s", POS_DIR, fileNames_gt[i].c_str());
				FILE* out = fopen(filepath, "a");
				fprintf(out, "%d\t%d\t%d\t%d\n", ldcfrects[m].x, ldcfrects[m].y, ldcfrects[m].width, ldcfrects[m].height);
				fclose(out);

				if (ldcfrects[m].height > 50)
				{
					//largepositive++;
					int largepositive = 0;
					//save to large positive
					sprintf_s(filepath, "%s\\%s", LARGE_POS_DIR, fileNames_gt[i].c_str());
					FILE* out = fopen(filepath, "a");
					fprintf(out, "%d\t%d\t%d\t%d\t%d\n", ldcfrects[m].x, ldcfrects[m].y, ldcfrects[m].width, ldcfrects[m].height, largepositive);
					cout << "positive(large) " << positive << "\t" << largepositive << endl;
					largepositive++;
					fclose(out);


				}
			}
			else
			{
				negative++;
				//save to negative
				sprintf_s(filepath, "%s\\%s", NEG_DIR, fileNames_gt[i].c_str());
				FILE* out = fopen(filepath, "a");
				fprintf(out, "%d\t%d\t%d\t%d\n", ldcfrects[m].x, ldcfrects[m].y, ldcfrects[m].width, ldcfrects[m].height);
				fclose(out);

				if (ldcfrects[m].height > 50)
				{
					largenegative++;
					//save to large negative
					sprintf_s(filepath, "%s\\%s", LARGE_NEG_DIR, fileNames_gt[i].c_str());
					FILE* out = fopen(filepath, "a");
					fprintf(out, "%d\t%d\t%d\t%d\n", ldcfrects[m].x, ldcfrects[m].y, ldcfrects[m].width, ldcfrects[m].height);
					fclose(out);

				}
			}
			ldcf++;

			if (maxIoU == 0 && ldcfrects[m].height > 50)
			{
				int nooverlapped = 0;
				sprintf_s(filepath, "%s\\%s", NOOVERLAP, fileNames_gt[i].c_str());
				FILE* out = fopen(filepath, "a");
				fprintf(out, "%d\t%d\t%d\t%d\t%d\n", ldcfrects[m].x, ldcfrects[m].y, ldcfrects[m].width, ldcfrects[m].height, nooverlapped);
				nooverlapped++;
				fclose(out);

			}
		}

		for (int k = 0; k < gtrects.size(); k++)
			if (isGT[k] == false)
			{
				nodetected++;
				//save to nodetected.
				char filepath[300];
				sprintf_s(filepath, "%s\\%s", NOTDETECT_DIR, fileNames_gt[i].c_str());
				FILE* out = fopen(filepath, "a"); //파일을 연다.
				fprintf(out, "%d\t%d\t%d\t%d\n", gtrects[k].x, gtrects[k].y, gtrects[k].width, gtrects[k].height);  //k번째 rectange의 x, y, width, height좌표값을 파일에 쓴다.
				fclose(out);//파일을 닫는다.

			}

		ldcfrects.clear();
		gtrects.clear();
		delete[] isGT;

	}
	//fclose(fstat);
	//cout << positive << "\t" << negative << "\t" << nodetected <<"\t" << iou_number <<endl;

	//cout << "positive(large) " << positive << "\t" << largepositive << endl;
	cout << "negative(large) " << negative << "\t" << largenegative << endl;
	//cout << "nooverlapped " << nooverlapped << endl;
	cout << "nodetected" << nodetected << endl;
	cout << "full gt: "<< "\t" << fullgt << " full ldcf: " <<ldcf << endl;
	
	return 0;
}
