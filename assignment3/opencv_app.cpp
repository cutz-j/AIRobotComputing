#include "pch.h"
#include "opencv2/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <conio.h>
#include <windows.h>
#include <iostream>

cv::Mat drawImage(void);
HANDLE hMapFile; // 메모리 포인터 변수
float *pMapView;

int getSize(cv::Mat *image) {
	return image->rows * image->cols * 3;
}

float getCopy(cv::Mat *image, float *arr) {
	return image->copyTo(arr);
}

int main(void) {
	hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(float)*2, L"OPENCV_MEMORY");
	pMapView = (float*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);

	
	while (1) {
		if (pMapView[0] == 1.0) {
			printf("%f", pMapView[0]);
			cv::Mat image = drawImage();
			pMapView[0] = getSize(&image);

			hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(float)*getSize(&image), L"OPENCV_MEMORY");
			pMapView = (float*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);

			
		}
		
	}
	return 0;
}

cv::Mat drawImage(void) {
	cv::Mat image = cv::imread("e:/data/sample.jpg");
	//cv::namedWindow("image", 1);

	cv::Size boardSize(9, 6);

	std::vector<cv::Point2f> corners;
	bool patternFound = cv::findChessboardCorners(image, boardSize, corners);
	cv::drawChessboardCorners(image, boardSize, cv::Mat(corners), patternFound);

	cv::imshow("image", image); // 시각화
	cv::waitKey(0);
	return image;
}