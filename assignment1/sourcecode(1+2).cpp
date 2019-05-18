#include <iostream>
#include "opencv2/core/core.hpp" // cv core lib
#include "opencv2/highgui.hpp" 
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <cstdlib>
#include <string>

int assignment2(); // calibration --> assignment 2
std::vector<cv::Point2f> capture(int save); // capture 함수
int assignment3(); // PnP --> assignment3

int main() {
	assignment3();

	return 0;
}

std::vector<cv::Point2f> capture(int save=0) {
	/* 
	function: 이미지 캡쳐 후, corner 정보 출력, spacebar 누르면 함수 종료 후, return
	
	inputs:
		- save: 기본 not-save, 1일때, image file save

	outputs:
		- corners: img 코너 정보
	*/

	cv::VideoCapture cam(0); // camera 구동
	cv::Mat image; // image matrix

	int row = 9; // 체크무늬 개수 9 x 7
	int col = 7;

	cv::Size boardSize(row, col); // size 변수
	std::vector<cv::Point2f> corners; // corner를 저장하는 2dvec

	while (1) {
		cam.read(image);
		bool patternFound = cv::findChessboardCorners(image, boardSize, corners); // chessboard
		cv::drawChessboardCorners(image, boardSize, cv::Mat(corners), patternFound); // draw
		cv::imshow("cam", image); // 출력

		int key = cv::waitKey(32);

		if (patternFound && key == 32) // 32 == spacebar
			break;
	}
	
	if (save == 1) {
		cv::imwrite("res.jpg", image);
	}
	cv::waitKey(0);
	return corners;
}

int assignment2(void) {
	/* 
	function: 카메라 좌표계를 파악하여 K(intrinsic param) RT(extrinsic param)매트릭스 값 구하기
	
	inputs: X

	outputs: X
	*/

	std::vector<cv::Point2f> corners = capture(1); // corner를 저장하는 2dvec
	
	int row = 9;
	int col = 7;

	std::string count;
	std::string jpg;
	std::string name;

	float sqSize = 2.5; // 격자간 거리
	
	std::vector<cv::Point3f> cornerPoints3D; // 3d vec

	// 3차원 vector 계산 과정 //
	for (int v=0; v < col; v++)
		for (int u = 0; u < row; u++) {
			cv::Point3f tmp;
			tmp.x = u * sqSize;
			tmp.y = v * sqSize;
			tmp.z = 0; // z 정사영 압축

			cornerPoints3D.push_back(tmp); // 담기
		}
	
	std::vector<std::vector<cv::Point2f> > imagePoints; // 2d vec
	imagePoints.push_back(corners); // 추출한 corner 담기

	std::vector<std::vector<cv::Point3f> > objectPoints; // 3d vec
	objectPoints.push_back(cornerPoints3D);

	std::vector <cv::Mat> rvecs, tvecs; // [extrinsic mats] rvecs: extrinsic // tvecs: 
	cv::Mat intrinsic_Matrix(3, 3, CV_64F); // [intrinsic mats]
	cv::Mat distortion_coeffs(8, 1, CV_64F);

	cv::Size imageSize = cv::Size(col, row);

	cv::calibrateCamera(objectPoints, imagePoints, imageSize, intrinsic_Matrix, distortion_coeffs, rvecs, tvecs); // K matrix 계산


	// matrix 출력 //
	for (int v = 0; v < 3; v++) {
		for (int u = 0; u < 3; u++) {
			std::cout << intrinsic_Matrix.at<double>(v, u) << "\t";
		}
		std::cout << std::endl;
	}

	return 0;
}

int assignment3(void) {
	/*
	function: 선형변환식을 통해 차원을 변화시킨 후, 선을 이미지 상에 증강시키는 함수

	inputs: X

	outputs: X
	*/

	int row = 9; // 체크박스 개수
	int col = 7;

	std::string name; // 저장용 변수
	name = "1.jpg";

	cv::Size boardSize(row, col);

	std::vector<cv::Point2f> corner2D; // 2d vec
	corner2D.clear(); // clear

	float sqSize = 2.5; // 체크박스 square size

	std::vector<cv::Point3f> corner3D; // 3d vec
	corner3D.clear(); // clear

	// 3d vec //
	for (int v = 0; v < col; v++)
		for (int u = 0; u < row; u++) {
			cv::Point3f tmp;
			tmp.x = u * sqSize;
			tmp.y = v * sqSize;
			tmp.z = 0;

			corner3D.push_back(tmp); // corner3D에 넣기
		}

	float lineLength = 3.0; // line 3cm

	std::vector<cv::Point3f> objectPoints; // model Point --> 그리고 싶은 점의 좌표계


	// 3차원 각 독립 line 그리기 //
	objectPoints.push_back(cv::Point3f(0, 0, 0));
	objectPoints.push_back(cv::Point3f(lineLength, 0, 0));
	objectPoints.push_back(cv::Point3f(0, lineLength, 0));
	objectPoints.push_back(cv::Point3f(0, 0, lineLength));

	// capture //
	cv::VideoCapture cam(0);
	cv::Mat image;


	// 6Dof //
	cv::Mat cameraMatrix = cv::Mat::zeros(3, 3, CV_64F);
	

	// extrinsic R T //
	cv::Mat rotationMatrix = cv::Mat::zeros(3, 3, CV_64F);
	cv::Mat translationVector = cv::Mat::zeros(3, 1, CV_64F);

	cv::Mat distCoeffs(4, 1, cv::DataType<double>::type);
	distCoeffs.at<double>(0) = 0;
	distCoeffs.at<double>(1) = 0;
	distCoeffs.at<double>(2) = 0;
	distCoeffs.at<double>(3) = 0;

	std::vector<std::vector<cv::Point2f> > imagePoints; // 2d
	std::vector<std::vector<cv::Point3f> > objPoints; // 3d

	while (1) {
		cam.read(image); // capture read
		corner2D.clear(); //clear

		cam.read(image);
		bool patternFound = cv::findChessboardCorners(image, boardSize, corner2D); // pattern found --> 1
		cv::drawChessboardCorners(image, boardSize, cv::Mat(corner2D), patternFound); // pattern draw

		cv::Size imageSize = cv::Size(image.cols, image.rows); // imagesize size writer

		if (patternFound) {
			imagePoints.push_back(corner2D);
			objPoints.push_back(corner3D);

			cv::calibrateCamera(objPoints, imagePoints, imageSize, cameraMatrix, distCoeffs, rotationMatrix, translationVector); // Kmatrix 구하기
			cameraMatrix.at<double>(2, 2) = 1.0;
			
			cv::solvePnP(corner3D, corner2D, cameraMatrix, distCoeffs, rotationMatrix, translationVector); // K RT 매트릭스 계산

			std::vector<cv::Point2f> projectedPoints;
			cv::projectPoints(objectPoints, rotationMatrix, translationVector, cameraMatrix, distCoeffs, projectedPoints); // 2d에 사영
			
			// 2d/3d vector에 담기 //
			
			//std::cout << intrinsic_Matrix.at<double>(1, 2) << std::endl;

			
			// 증강 선 그리기 //
			cv::line(image, projectedPoints.at(0), projectedPoints.at(1),
				cv::Scalar(0, 0, 255), 2, 8, 0);
			cv::line(image, projectedPoints.at(0), projectedPoints.at(2),
				cv::Scalar(0, 255, 0), 2, 8, 0);
			cv::line(image, projectedPoints.at(0), projectedPoints.at(3),
				cv::Scalar(255, 0, 0), 2, 8, 0);

		}

		cv::imshow("cam", image);
		
		cv::imwrite(name, image);
		int key = cv::waitKey(10);
		if (key == 27)
			break;
		name.at(0)++;
	}

	return 0;
}


















