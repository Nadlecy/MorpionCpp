#include <winsock2.h>
#include <windows.h>

#define PORT 6969
#define WM_SOCKET WM_USER + 1
#pragma comment(lib, "ws2_32.lib")

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

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
	hwnd = CreateWindowEx(0, L"ServerWindowClass", L"Server Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);
	if (hwnd == NULL) {
		MessageBox(NULL, L"Window creation failed", L"Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	// Bind the socket
	SOCKADDR_IN serverAddr;
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

	// Listen on the socket
	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
		MessageBox(NULL, L"listen failed", L"Error", MB_OK | MB_ICONERROR);
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}

	// faire un select




	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Message loop
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// Cleanup
	closesocket(serverSocket);
	WSACleanup();

	return (int)msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam,int newSocket, SOCKET serverSocket, SOCKADDR_IN serverAddr, int addrlen) {
	switch (uMsg)
	{
	case WM_PAINT:
		// Process window paint message
		break;
	case WM_SOCKET:
		// Determine whether an error occurred on the
		// socket by using the WSAGETSELECTERROR() macro
		if (WSAGETSELECTERROR(lParam))
		{
			// Display the error and close the socke
			closesocket((SOCKET)wParam);
			break;
		}
		// Determine what event occurred on the socket
		switch (WSAGETSELECTEVENT(lParam))
		{
		case FD_ACCEPT:
			// Accept an incoming connection
			newSocket = accept(serverSocket, (SOCKADDR*)&serverAddr, &addrlen);
			// Prepare accepted socket for read, write, and close notification
			WSAAsyncSelect(newSocket, hwnd, WM_SOCKET, FD_READ | FD_WRITE | FD_CLOSE);
			send(newSocket, "Server says hi 2", (int)strlen("Server says hi 2"), 0);
			break;
		case FD_READ:
			// Receive data from the socket in wParam
			break;
		}
		break;
	}
	return 0;
}