#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>

#define PORT 6969
//#define WM_SOCKET WM_USER + 1

#pragma comment(lib, "ws2_32.lib")

using namespace std;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	//MyRegisterClass(hInstance);


	// Create a window
	HWND hwnd;
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;    
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"ServerWindowClass";
	RegisterClassEx(&wc);
	hwnd = CreateWindowEx(0, L"ServerWindowClass", L"Server Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, nullptr, nullptr, hInstance, nullptr);

	if (hwnd == NULL)
	{
		return FALSE;
	}

	// Initialize Winsock
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		MessageBox(NULL, L"WSAStartup failed", L"Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	// Create a socket
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	int newSocket;
	if (serverSocket == INVALID_SOCKET) {
		MessageBox(NULL, L"socket failed", L"Error", MB_OK | MB_ICONERROR);
		WSACleanup();
		return 1;
	}

	// Bind the socket
	SOCKADDR_IN serverAddr;
	WSAAsyncSelect(serverSocket, hwnd, WM_USER + 1, FD_ACCEPT | FD_READ | FD_CLOSE);
	int addrlen = sizeof(serverAddr);
	size_t valread;

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(PORT); // You can change the port number
	if (bind(serverSocket, (SOCKADDR*)&serverAddr, addrlen) == SOCKET_ERROR) {
		MessageBox(NULL, L"bind failed", L"Error", MB_OK | MB_ICONERROR);
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}

	if (hwnd == NULL) {
		MessageBox(NULL, L"Window creation failed", L"Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	// Listen on the socket
	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
		MessageBox(NULL, L"listen failed", L"Error", MB_OK | MB_ICONERROR);
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}

	// Show the Window
	ShowWindow(hwnd, nCmdShow);

	// Message loop
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		UpdateWindow(hwnd);
	}

	// Cleanup
	closesocket(serverSocket);
	WSACleanup();

	return (int)msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	SOCKET SocketInfo;
	SOCKET newSocket;
	WSABUF dataBuf;
	DWORD RecvBytes;
	DWORD Flags = 0;
	char recvBuffer[512];
	dataBuf.buf = recvBuffer;
	dataBuf.len = 512;

	switch (uMsg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		// All painting occurs here, between BeginPaint and EndPaint.

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
	}

	case WM_USER + 1:
		// Determine what event occurred on the socket
		switch (WSAGETSELECTEVENT(lParam))
		{
		case FD_ACCEPT:
			// Accept an incoming connection
			newSocket = accept(wParam, NULL, NULL);
			// Prepare accepted socket for read, write, and close notification
			WSAAsyncSelect(newSocket, hwnd, WM_USER + 1, FD_READ | FD_CLOSE);
			send(newSocket, "Connect to server", (int)strlen("Connect to server"), 0);
			break;

		case FD_CLOSE:
			closesocket((SOCKET)wParam);
			break;

		case FD_READ:
			
			SocketInfo = wParam;

			if (WSARecv(SocketInfo, &dataBuf, 1, &RecvBytes, &Flags, NULL, NULL) == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					printf("WSARecv() failed with error %d\n", WSAGetLastError());
					closesocket(SocketInfo);
					return 0;
				}
			}
			else {
				system("pause");
				wstring message(recvBuffer, recvBuffer + RecvBytes);
				MessageBox(hwnd, message.c_str(), L"Notification", MB_OK | MB_ICONINFORMATION);
				send(SocketInfo, "Connect to server 3", (int)strlen("Connect to server 3"), 0);
			}
			break;
		}
		break;
	}
}