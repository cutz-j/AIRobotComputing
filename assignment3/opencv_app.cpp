#include "opencv2/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <conio.h>
#include <windows.h>
#include <iostream>

void drawImage(cv::Mat *image);
HANDLE hMapFile; // 메모리 포인터 변수 (trigger)
HANDLE hMapFile2;
int *pMapView;
int *pMapView2;
cv::Mat image;

int getSize(cv::Mat *image) {
	return image->rows * image->cols * 3;
}

int getRow(cv::Mat *image) {
	return image->rows;
}

int getCol(cv::Mat *image) {
	return image->cols;
}


int main(void) {
	
	hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(int)*3, L"OPENCV_MEMORY");
	pMapView = (int*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	
	while (1) {
		if (pMapView[0] == 1) {
			drawImage(&image);
			hMapFile2 = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(int)*getSize(&image), L"IMAGE_MEMORY");
			pMapView2 = (int*)MapViewOfFile(hMapFile2, FILE_MAP_WRITE, 0, 0, 0);
			pMapView[0] = getSize(&image);

			//printf("%d %d %d", getCol(&image), getRow(&image), getSize(&image));

			for (int i = 0; i < getCol(&image); i++) {
				for (int j = 0; j < getRow(&image); j++) {
					for (int k = 0; k < 3; k++) {
						auto& pixel = image.at<cv::Vec3b>(j, i);
						pMapView2[(i * getRow(&image) * 3) + (j * 3) + k] = (int)pixel[k];
					}
				}
			}
			
			printf("image sent \n");
			break;
		}
	}
	return 0;
}

void drawImage(cv::Mat *image) {
	/*
	function: image draw

	input: cv::Mat *image
	
	output: void
	*/
	*image = cv::imread("d:/data/sample.jpg");
	cv::Size boardSize(9, 6);

	std::vector<cv::Point2f> corners;
	bool patternFound = cv::findChessboardCorners(*image, boardSize, corners);
	cv::drawChessboardCorners(*image, boardSize, cv::Mat(corners), patternFound);

	cv::resize(*image, *image, cv::Size(image->cols / 5, image->rows / 5), 0, 0, CV_INTER_NN);

	cv::namedWindow("image", 1);
	cv::imshow("image", *image);
	cv::waitKey(0);
}