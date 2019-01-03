 //////////////////positive 16       negative 48        frist positive 16-> negative 48 
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


#define LDCF_DIR "D:\\piotr_toolbox1\\data\\Caltech\\train04\\ldcf"
#define GT_DIR "D:\\piotr_toolbox1\\data\\Caltech\\train04\\annotations"
//#define LDCF_DIR "D:\\piotr_toolbox1\\data\\Caltech\\test\\test_ldcf"
//#define GT_DIR "D:\\piotr_toolbox1\\data\\Caltech\\train04\\test_gt"
#define POS_DIR "D:\\piotr_toolbox1\\data\\Caltech\\train04\\positive"
#define NEG_DIR "D:\\piotr_toolbox1\\data\\Caltech\\train04\\negative"
#define NOTDETECT_DIR "D:\\piotr_toolbox1\\data\\Caltech\\train04\\notdetect"
#define LARGE_POS_DIR "D:\\piotr_toolbox1\\data\\Caltech\\train04\\large_positive_TEST"
#define LARGE_NEG_DIR "D:\\piotr_toolbox1\\data\\Caltech\\train04\\large_negative"
#define NOOVERLAP "D:\\piotr_toolbox1\\data\\Caltech\\train04\\nooverlapped_TEST"
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

//int main()
//{
//	vector<string> fileNames_gt = get_all_files_names_within_folder(GT_DIR);
//
//	int positive = 0;
//	//int largepositive = 0;
//	int negative = 0;
//	int largenegative = 0;
//
//	int nodetected = 0;
//	int iou_number = 0;
//
//	int iou = 0;
//	int ldcf = 0;
//	int fneg = 0;
//	int fullgt = 0;
//
//
//	FILE* file = fopen("count.txt", "w");
//	//FILE* fstat = fopen("D:\\piotr_toolbox1\\data\\Caltech\\train04\\train.txt", "w");
//	for (int i = 0; i < fileNames_gt.size(); i++) {//ground truth list 가져오기,get the ground truth size 
//												   //read ground truth .txt file
//		if (!(fileNames_gt[i].compare(".txt")))
//			continue;
//
//		fprintf(file, "%s\t", fileNames_gt[i].c_str());
//
//		char filepath[300];
//		char ldcf_filepath[300];
//		char gt_filepath[300];
//
//		/////read LDCF txt,read ground truth txt
//		sprintf(ldcf_filepath, "%s\\%s", LDCF_DIR, fileNames_gt[i].c_str());
//		sprintf(gt_filepath, "%s\\%s", GT_DIR, fileNames_gt[i].c_str());
//		/////filepath :the path of positive dir,negative dir ,notdetect dir ,write txt result to positive dir,nehative dir ,notdetect dir 
//		sprintf(filepath, "%s\\%s", POS_DIR, fileNames_gt[i].c_str());
//		/*FILE* file = fopen(filepath, "w");
//		fclose(file);
//		sprintf(filepath, "%s\\%s", NEG_DIR, fileNames_gt[i].c_str());
//		file = fopen(filepath, "w");
//		fclose(file);
//		sprintf(filepath, "%s\\%s", NOTDETECT_DIR, fileNames_gt[i].c_str());
//		file = fopen(filepath, "w");
//		fclose(file);*/
//
//		/////input ldcf,gt file
//		std::ifstream ldcf_file(ldcf_filepath);
//		std::ifstream gt_file(gt_filepath);
//
//		string line;
//		vector<Rect> ldcfrects;
//		//cout << "LDCF" << endl;
//		int idx = 0;
//		while (std::getline(ldcf_file, line))///////line by line to read ldcf txt on 1.txt
//		{
//			//cout << idx++ <<"\t" << line << endl;
//			Rect r;
//			std::string delimiter = "\t";
//			size_t pos = 0;
//			std::string token;
//			vector<string> sarray;
//			while ((pos = line.find(delimiter)) != std::string::npos) {
//				token = line.substr(0, pos);
//				sarray.push_back(token);
//				line.erase(0, pos + delimiter.length());
//			}
//			r.x = atoi(sarray[1].c_str());
//			r.y = atoi(sarray[2].c_str());
//			r.width = atoi(sarray[3].c_str());
//			r.height = atoi(sarray[4].c_str());
//			//cout << r.x << "\t" << r.y << "\t" << r.width << "\t" << r.height << endl;
//			ldcfrects.push_back(r);
//			sarray.clear();
//		}
//
//		///////ground truth bounding box...
//		vector<Rect> gtrects;
//		//cout << "GT" << endl;
//		while (std::getline(gt_file, line))///////line by line to read ground truth txt on 1.txt
//		{
//			//cout << idx++ << "\t" << line << endl;
//			Rect r;
//			std::string delimiter = " ";
//			size_t pos = 0;
//			std::string token;
//			vector<string> sarray;
//			//cout << line << "\t";
//			while ((pos = line.find(delimiter)) != std::string::npos) {
//				token = line.substr(0, pos);
//				sarray.push_back(token);
//				line.erase(0, pos + delimiter.length());
//			}
//			//cout << sarray.size() << endl;
//			if (sarray.size() < 3)
//				continue;
//
//			r.x = atoi(sarray[1].c_str());
//			r.y = atoi(sarray[2].c_str());
//			r.width = atoi(sarray[3].c_str());
//			r.height = atoi(sarray[4].c_str());
//
//			//cout << r.x << "\t" << r.y << "\t" << r.width << "\t" << r.height << endl;
//			gtrects.push_back(r);
//			sarray.clear();
//		}
//		fullgt += gtrects.size();
//		///////groud truth rectangle ,first all the groud truth rectangle is false
//		//////// bool==>false,true
//		///////LDCF rectangle ,first all the LDCF rectangle is false
//		//////// bool==>false,true
//
//		bool* isGT = new bool[gtrects.size()];
//		for (int m = 0; m < gtrects.size(); m++)//j
//			isGT[m] = false;
//
//		int largepositive = 0;
//		int largenegative = 0;
//		//1 image
//		for (int m = 0; m < ldcfrects.size(); m++)////// read idcf rectangle from 0 to end on 1.txt
//		{
//			float maxIoU = 0;
//			for (int n = 0; n < gtrects.size(); n++)////// read gt rectangle from 0 to end on 1.txt
//			{
//				///////IoU 비교 gtrect, ldcfrect IoU 호출하면 보다 높으면 positive==>isLD[m] = true,isGT[n] = true==>출력
//				float iouVal = calculateIoUFrom(gtrects[n], ldcfrects[m]);
//				if (maxIoU < iouVal)
//					maxIoU = iouVal;
//
//				//cout << iouVal << endl;
//				if (iouVal >= IOU_TH_VAL)
//					isGT[n] = true;
//			}
//			//cout << "max: " <<maxIoU << endl;
//
//			//rect ==> 0.1 0.3 0.5 ==> max(0.1 0.3 0.5) => 0.5 >= 0.5 ==> positive
//
//			if (maxIoU >= IOU_TH_VAL)
//			{
//				
//				
//				if (ldcfrects[m].height > 50)
//				{
//					
//					
//					largepositive++;
//					////save to large positive
//					//sprintf_s(filepath, "%s\\%s", LARGE_POS_DIR, fileNames_gt[i].c_str());
//					//FILE* out = fopen(filepath, "a");
//					//fprintf(out, "%d\t%d\t%d\t%d\t%d\n", ldcfrects[m].x, ldcfrects[m].y, ldcfrects[m].width, ldcfrects[m].height, largepositive);
//					//cout << "positive(large) " << "\t" << largepositive << endl;
//					////largepositive++;
//					//fclose(out);
//
//
//				}
//			}
//			
//			
//			if (maxIoU == 0 && ldcfrects[m].height > 50)
//			{
//				largenegative++;
//
//				//int nooverlapped = 0;
//				//sprintf_s(filepath, "%s\\%s", NOOVERLAP, fileNames_gt[i].c_str());
//				//FILE* out = fopen(filepath, "a");
//				//fprintf(out, "%d\t%d\t%d\t%d\t%d\\n", ldcfrects[m].x, ldcfrects[m].y, ldcfrects[m].width, ldcfrects[m].height);
//				//fclose(out);
//
//			}
//		}
//
//		fprintf(file, "%d\t%d\n", largepositive, largenegative);
//		ldcfrects.clear();
//		gtrects.clear();
//		delete[] isGT;
//
//	}
//	fclose(file);
//	
//
//	return 0;
//}
int main() {
	FILE* file1 = fopen("C:\\Users\\lijinxi\\Documents\\Visual Studio 2015\\Projects\\fine_tuning_positive_negative\\fine_tuning_positive_negative\\test_large_positive_p6.txt", "r");
	FILE* file2 = fopen("C:\\Users\\lijinxi\\Documents\\Visual Studio 2015\\Projects\\fine_tuning_positive_negative\\fine_tuning_positive_negative\\test_nooverlapped_p6.txt", "r");
	FILE* file3 = fopen("p6_test_positive_negative.txt", "w");
	std::ifstream in(file1); //텍스트 파일 읽어와서 파일 포인터를 filepath로 넣음. 
	std::ifstream in1(file2);
	std::ofstream out(file3);
	string line;
	string a;
	int b;
	char buf[1024];
	char buf1[1024];
	for (int a = 0; a < 1000; a++) {
		for (int i = 0; i < 16; i++) {
			in.getline(buf, 2014);
			fprintf(file3, "%s\n", buf);
		}
		for (int j = 0; j < 48; j++) {
			in1.getline(buf1, 2014);
			fprintf(file3, "%s\n", buf1);
		}
	}
	
		
	
	/*while (getline(in, line)) 
	{
		cout << line << endl;
		out << line << endl;
	}
*/
	/*while (std::getline(txtfile, line)) {
		for (int m = 0; m < 16; m++) {

			fprintf(file3, "%s\n", line);
		}
	}*/
	
}
