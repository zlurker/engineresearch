#pragma once

#define IDS_APP_TITLE			103

#define IDR_MAINFRAME			128
#define IDD_GAMEENGINE_DIALOG	102
#define IDD_ABOUTBOX			103
#define IDM_ABOUT				104
#define IDM_EXIT				105

//#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <thread>

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[100];                  // The title bar text
WCHAR szWindowClass[100];            // the main window class name
HWND handle;
HDC hdc;
HGLRC hglrc;
//renderer* rend;
std::thread thread;
DWORD style;

void render();
GLint MySetPixelFormat();
bool InitGL(GLvoid);
GLvoid ReSizeGLScene(GLsizei width, GLsizei height);
int DrawGLScene(GLvoid);
int mainMessageLoop(HACCEL hAccelTable = 0);

GLfloat	rtri;				// Angle for the triangle
GLfloat	rquad;				// Angle for the quad
const std::wstring wnd_class(L"my_wnd_class");

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

int mainMessageLoop(HACCEL hAccelTable)
{
	MSG msg;

	while (::GetMessage(&msg, 0, 0, 0) > 0)  // loop until WM_QUIT(0) received
	{
		// now, handle window messages
		if (!::TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;                 // return nExitCode of PostQuitMessage()
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX winClass;

	// populate window class struct
	winClass.cbSize = sizeof(WNDCLASSEX);
	winClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;                                    // class styles: CS_OWNDC, CS_PARENTDC, CS_CLASSDC, CS_GLOBALCLASS, ...
	winClass.lpfnWndProc = WndProc;                  // pointer to window procedure
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;
	winClass.hInstance = hInstance;                              // owner of this class
	winClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);   // default icon
	winClass.hIconSm = 0;
	winClass.hCursor = LoadCursor(0, IDC_ARROW);              // default arrow cursor
	winClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);   // default white brush
	winClass.lpszMenuName = 0;
	winClass.lpszClassName = L"Test";
	winClass.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);   // default small icon

	if (!RegisterClassEx(&winClass)) {
		::MessageBox(0, L"Register failed.", L"Error", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	style = WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	handle = CreateWindowEx(WS_EX_CLIENTEDGE, L"Test",NULL,style,800,600,800,600,0,0,hInstance,NULL);
	int exitCode;
	exitCode = mainMessageLoop();
	return 0;
}

