#pragma comment(lib, "ws2_32.lib")

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <iostream>

#define PORT 6969
#define DATA_BUFSIZE 8192
//#define IPADDRESS 10.1.144.26

using namespace std;

typedef struct _SOCKET_INFORMATION {
	BOOL RecvPosted;
	CHAR Buffer[DATA_BUFSIZE];
	WSABUF DataBuf;
	SOCKET Socket;
	DWORD BytesSEND;
	DWORD BytesRECV;
	struct _SOCKET_INFORMATION* Next;
} SOCKET_INFORMATION, * LPSOCKET_INFORMATION;

#define WM_SOCKET (WM_USER + 1)

LPSOCKET_INFORMATION SocketInfoList;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
int main()
{
	HINSTANCE hInstance = GetModuleHandle(0);

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

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

	//Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h
	wVersionRequested = MAKEWORD(2, 2);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		//Tell the user that we could not find a usable
		//Winsock DLL.                                  
		MessageBox(NULL, L"WSAStartup failed with error: %d", L"Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	int status, valread, client_fd;
	struct sockaddr_in serv_addr;
	char buffer[1024] = { 0 };
	if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		MessageBox(NULL, L"Socket creation error", L"Error", MB_OK | MB_ICONERROR);
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, "10.1.144.26", &serv_addr.sin_addr)
		<= 0) {
		MessageBox(NULL, L"Invalid address / Address not supported", L"Error", MB_OK | MB_ICONERROR);
		return -1;
	}

	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//WSAAsyncSelect(serverSocket, NULL, WM_USER + 1, FD_ACCEPT | FD_READ | FD_CLOSE);
	if ((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
		MessageBox(NULL, L"Connection Failed", L"Error", MB_OK | MB_ICONERROR);
		return -1;
	}

	if (hwnd == NULL) {
		MessageBox(NULL, L"Window creation failed", L"Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	// Show the Window
	//ShowWindow(hwnd, nCmdShow);

	// Message loop
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// Cleanup
	closesocket(clientSocket);
	WSACleanup();

	return (int)msg.wParam;
	
}

void FreeSocketInformation(SOCKET s)
{
	SOCKET_INFORMATION* SI = SocketInfoList;
	SOCKET_INFORMATION* PrevSI = NULL;

	while (SI)
	{
		if (SI->Socket == s)
		{
			if (PrevSI) {
				PrevSI->Next = SI->Next;
			}
			else {
				SocketInfoList = SI->Next;
				closesocket(SI->Socket);
				GlobalFree(SI);
				return;
			}
		}
		PrevSI = SI;
		SI = SI->Next;
	}
}

void CreateSocketInformation(SOCKET s)
{
	LPSOCKET_INFORMATION SI;

	if ((SI = (LPSOCKET_INFORMATION)GlobalAlloc(GPTR, sizeof(SOCKET_INFORMATION))) == NULL)
	{
		printf("GlobalAlloc() failed with error %d\n", GetLastError());
		return;
	}
	else
		printf("GlobalAlloc() for SOCKET_INFORMATION is OK!\n");
	// Prepare SocketInfo structure for use
	SI->Socket = s;
	SI->RecvPosted = FALSE;
	SI->BytesSEND = 0;
	SI->BytesRECV = 0;
	SI->Next = SocketInfoList;
	SocketInfoList = SI;
}



LPSOCKET_INFORMATION GetSocketInformation(SOCKET s)
{
	SOCKET_INFORMATION* SI = SocketInfoList;
	while (SI)
	{
		if (SI->Socket == s)
			return SI;
		SI = SI->Next;
	}
	return NULL;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)

{

	SOCKET Accept;
	LPSOCKET_INFORMATION SocketInfo;
	DWORD RecvBytes;
	DWORD SendBytes;
	DWORD Flags;

	if (uMsg == WM_SOCKET)
	{
		if (WSAGETSELECTERROR(lParam))
		{
			printf("Socket failed with error %d\n", WSAGETSELECTERROR(lParam));
			FreeSocketInformation(wParam);
		}
		else
		{
			printf("Socket looks fine!\n");
			switch (WSAGETSELECTEVENT(lParam)) {
			case FD_ACCEPT:
				if ((Accept = accept(wParam, NULL, NULL)) == INVALID_SOCKET)
				{
					printf("accept() failed with error %d\n", WSAGetLastError());
					break;
				}
				else {
					printf("accept() is OK!\n");

					// Create a socket information structure to associate with the socket for processing I/O
					CreateSocketInformation(Accept);
					printf("Socket number %d connected\n", Accept);
					WSAAsyncSelect(Accept, hwnd, WM_SOCKET, FD_READ | FD_WRITE | FD_CLOSE);
					break;
				}

			case FD_READ:
				SocketInfo = GetSocketInformation(wParam);
				// Read data only if the receive buffer is empty
				if (SocketInfo->BytesRECV != 0)
				{
					SocketInfo->RecvPosted = TRUE;
					return 0;
				}
				else
				{
					SocketInfo->DataBuf.buf = SocketInfo->Buffer;
					SocketInfo->DataBuf.len = DATA_BUFSIZE;
					Flags = 0;
					if (WSARecv(SocketInfo->Socket, &(SocketInfo->DataBuf), 1, &RecvBytes,
						&Flags, NULL, NULL) == SOCKET_ERROR)
					{
						if (WSAGetLastError() != WSAEWOULDBLOCK)
						{
							printf("WSARecv() failed with error %d\n", WSAGetLastError());
							FreeSocketInformation(wParam);
							return 0;
						}
					}
					else // No error so update the byte count
					{
						printf("WSARecv() is OK!\n");
						SocketInfo->BytesRECV = RecvBytes;
					}
				}
				// DO NOT BREAK HERE SINCE WE GOT A SUCCESSFUL RECV. Go ahead
				// and begin writing data to the client
			case FD_WRITE:
				SocketInfo = GetSocketInformation(wParam);
				if (SocketInfo->BytesRECV > SocketInfo->BytesSEND)
				{
					SocketInfo->DataBuf.buf = SocketInfo->Buffer + SocketInfo->BytesSEND;
					SocketInfo->DataBuf.len = SocketInfo->BytesRECV - SocketInfo->BytesSEND;
					if (WSASend(SocketInfo->Socket, &(SocketInfo->DataBuf), 1, &SendBytes, 0,
						NULL, NULL) == SOCKET_ERROR)
					{
						if (WSAGetLastError() != WSAEWOULDBLOCK)
						{
							printf("WSASend() failed with error %d\n", WSAGetLastError());
							FreeSocketInformation(wParam);
							return 0;
						}
					}
					else // No error so update the byte count
					{
						printf("WSASend() is OK!\n");
						SocketInfo->BytesSEND += SendBytes;
					}
				}
				if (SocketInfo->BytesSEND == SocketInfo->BytesRECV)
				{
					SocketInfo->BytesSEND = 0;
					SocketInfo->BytesRECV = 0;
					// If a RECV occurred during our SENDs then we need to post an FD_READ notification on the socket
					if (SocketInfo->RecvPosted == TRUE)
					{
						SocketInfo->RecvPosted = FALSE;
						PostMessage(hwnd, WM_SOCKET, wParam, FD_READ);
					}
				}
				break;
			case FD_CLOSE:
				printf("Closing socket %d\n", wParam);
				FreeSocketInformation(wParam);
				break;
			}
		}
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);

}
