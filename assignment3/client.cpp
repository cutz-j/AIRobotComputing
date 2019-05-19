#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "opencv2/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#pragma comment (lib, "ws2_32.lib")
//float opengl_Memory();
HANDLE hMapFile; // trigger
HANDLE hMapFile2; // opencv_image
int *pMapView;
int *pMapView2;

int main() {
	WSADATA wsa;
	SOCKET s;
	SOCKADDR_IN saddr;

	WSAStartup(MAKEWORD(2, 2), &wsa);
	s = socket(AF_INET, SOCK_STREAM, 0);
	
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(5000);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//InetPton(AF_INET, _T("127.0.0.1"), &saddr.sin_addr.s_addr);
	connect(s, (SOCKADDR*)&saddr, sizeof(saddr));
	std::cout << "connected" << std::endl;

	while (1) {
		char buf[512];
		int nSend;
		int nRecv;

		memset(buf, 0, sizeof(buf));
		nRecv = recv(s, buf, sizeof(buf), 0);
		if (nRecv == SOCKET_ERROR)
			break;


		if ((atoi(buf) == 1)) {
			// 1번 전송 받았을 때의 경우 //
			std::cout << "1번 선택" << std::endl;
			hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(int)*3, L"OPENCV_MEMORY");
			pMapView = (int*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
			pMapView[0] = 1;

			// size 재정의 //
			while (1) {
				if (pMapView[0] != 1) {
					int imgSize = pMapView[0];
					hMapFile2 = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(int)*imgSize, L"IMAGE_MEMORY");
					pMapView2 = (int*)MapViewOfFile(hMapFile2, FILE_MAP_READ, 0, 0, 0);
					
					char c[20];
					for (int j = 0; j < imgSize; j++) {
						_itoa_s(pMapView2[j], c, sizeof(int), 10);
						strcpy_s(buf, 20, c);
						strcat_s(buf, sizeof(buf), ".");
						//std::cout << buf << std::endl;
						// python server로 img 전송 //
						nSend = send(s, buf, strlen(buf), 0);
						if (nSend == SOCKET_ERROR)
							break;
					}
					printf("image received \n");
					break;
				}
			}

			printf("image sent \n");
			
			}

		if ((atoi(buf) == 2)) {
			// openGL //
			std::cout << "2번 선택" << std::endl;
			hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(int) * 3, L"OPENCV_MEMORY");
			pMapView = (int*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
			pMapView[0] = 2;

		}
		
	}
	closesocket(s);
	WSACleanup();

	return 0;
}