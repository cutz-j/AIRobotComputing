#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "pch.h"
#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <windows.h>

#pragma comment (lib, "ws2_32.lib")
float opencv_Memory();
//float opengl_Memory();
HANDLE hMapFile;
float *pMapView;



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
			std::cout << "1번 선택" << std::endl;
			hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(float)*2, L"OPENCV_MEMORY");
			pMapView = (float*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
			opencv_Memory();
			int imgSize = pMapView[0];

			// size 재정의 //
			hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, imgSize, L"OPENCV_MEMORY");
			pMapView = (float*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);

			}
		if ((atoi(buf) == 2)) {
			std::cout << "2번 선택" << std::endl;
		}
	}
	closesocket(s);
	WSACleanup();

	return 0;
}

float opencv_Memory(void) {
	/*
	
	
	*/
	float localMemory[1];
	localMemory[0] = 1.0;
	pMapView[0] = localMemory[0];

	printf("signaling\n");
	

	return *pMapView;
}