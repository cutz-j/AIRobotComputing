#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"

int program1();
int program2();
int program3();

int main() {
	//program1();
	//program2();
	program3();
	return 0;
}

int program1() {

	cv::VideoCapture cam(0);

	cv::Mat frame;

	while (1) {
		cam.read(frame);;
		cv::namedWindow("image", 1);

		cv::Size boardSize(9, 6);
		std::vector<cv::Point2f> corners;
		bool patternFound = cv::findChessboardCorners(frame, boardSize, corners);
		cv::drawChessboardCorners(frame, boardSize, cv::Mat(corners), patternFound);

		cv::imshow("image", frame);
		int key = cv::waitKey(15);
		if (key == 27)
			break;
	}
	return 0;
}

int program2() {
	cv::VideoCapture cam(0);
	cv::Mat image;

	int row = 9; int col = 7;

	cv::Size boardSize(row, col);

	std::vector<cv::Point2f> cornerPoints;

	while (1) {
		cam.read(image);
		bool patternFound = cv::findChessboardCorners(image, boardSize, cornerPoints);

		cv::drawChessboardCorners(image, boardSize, cv::Mat(cornerPoints), patternFound);

		cv::imshow("cam", image);

		int key = cv::waitKey(30);
		if (patternFound && key == 32)
			break;
	}

	float squareSize = 2.5;
	std::vector<cv::Point3f> cornerPoints3D;

	for (int v = 0; v < col; v++)
		for (int u = 0; u < row; u++) {
			cv::Point3f tmp;
			tmp.x = u * squareSize;
			tmp.y = v * squareSize;
			tmp.z = 0;

			cornerPoints3D.push_back(tmp);
		}

	std::vector<std::vector<cv::Point2f> > imagePoints;
	imagePoints.push_back(cornerPoints);

	std::vector<std::vector<cv::Point3f> > objectPoints;
	objectPoints.push_back(cornerPoints3D);

	std::vector <cv::Mat> rvecs, tvecs;
	cv::Mat intrinsic_matrix(3, 3, CV_64F);
	cv::Mat distortion_coeffs(8, 1, CV_64F);

	cv::Size imageSize = cv::Size(image.cols, image.rows);

	cv::calibrateCamera(objectPoints, imagePoints, imageSize, intrinsic_matrix, distortion_coeffs, rvecs, tvecs);

	for (int v = 0; v < 3; v++) {
		for (int u = 0; u < 3; u++) {
			printf("%f\t", intrinsic_matrix.at<double>(v, u));
		}
		printf("\n");
	}




	return 0;
}

int program3() {
	int row = 9; int col = 7;

	cv::Size boardSize(row, col);
	std::vector<cv::Point2f> cornerPoints2D;
	cornerPoints2D.clear();

	float squareSize = 2.5;
	std::vector<cv::Point3f> cornerPoints3D;
	cornerPoints3D.clear();

	for (int v = 0; v < col; v++)
		for (int u = 0; u < row; u++) {
			cv::Point3f tmp;
			tmp.x = u * squareSize;
			tmp.y = v * squareSize;
			tmp.z = 0;

			cornerPoints3D.push_back(tmp);
		}

	float lineLength = 3.0;

	std::vector<cv::Point3f> objectPoints;

	objectPoints.push_back(cv::Point3f(0, 0, 0));
	objectPoints.push_back(cv::Point3f(lineLength, 0, 0));
	objectPoints.push_back(cv::Point3f(0, lineLength, 0));
	objectPoints.push_back(cv::Point3f(0, 0, lineLength));

	cv::VideoCapture cam(0);
	cv::Mat image;

	cv::Mat cameraMatrix = cv::Mat::zeros(3, 3, CV_64F);
	
	cv::Mat rotationMatrix = cv::Mat::zeros(3, 3, CV_64F);
	cv::Mat translationVector = cv::Mat::zeros(3, 1, CV_64F);

	cv::Mat distCoeffs(4, 1, cv::DataType<double>::type);
	distCoeffs.at<double>(0) = 0;
	distCoeffs.at<double>(1) = 0;
	distCoeffs.at<double>(2) = 0;
	distCoeffs.at<double>(3) = 0;

	std::vector<std::vector<cv::Point2f> > imagePoints;
	std::vector<std::vector<cv::Point3f> > objPoints;

	while (1) {
		cam.read(image);
		cornerPoints2D.clear();

		bool patternFound = cv::findChessboardCorners(image, boardSize, cornerPoints2D);
		cv::drawChessboardCorners(image, boardSize, cv::Mat(cornerPoints2D), patternFound);
		
		cv::Size imageSize = cv::Size(image.cols, image.rows);

		if (patternFound) {
			imagePoints.push_back(cornerPoints2D);
			objPoints.push_back(cornerPoints3D);

			cv::calibrateCamera(objPoints, imagePoints, imageSize, cameraMatrix, distCoeffs, rotationMatrix, translationVector);
			cameraMatrix.at<double>(2, 2) = 1.0;

			cv::solvePnP(cornerPoints3D, cornerPoints2D, cameraMatrix, distCoeffs, rotationMatrix, translationVector);

			std::vector<cv::Point2f> projectedPoints;
			cv::projectPoints(objectPoints, rotationMatrix, translationVector, cameraMatrix, distCoeffs, projectedPoints);

			cv::line(image, projectedPoints.at(0), projectedPoints.at(1), cv::Scalar(0, 0, 255), 2, 8, 0);
			cv::line(image, projectedPoints.at(0), projectedPoints.at(2), cv::Scalar(0, 255, 0), 2, 8, 0);
			cv::line(image, projectedPoints.at(0), projectedPoints.at(3), cv::Scalar(255, 0, 0), 2, 8, 0);
		}

		cv::imshow("cam", image);

		int key = cv::waitKey(10);
		if (key == 27)
			break;

	}

	return 0;
}