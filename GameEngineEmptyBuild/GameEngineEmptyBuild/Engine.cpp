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
GLint MySetPixelFormat(int nCmdShow);
bool setPixelFormat(int colorBits, int depthBits, int stencilBits);
int findPixelFormat(int colorBits, int depthBits, int stencilBits);

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

/*bool setPixelFormat(int colorBits, int depthBits, int stencilBits)
{
	PIXELFORMATDESCRIPTOR pfd;

	// find out the best matched pixel format
	int pixelFormat = findPixelFormat(colorBits, depthBits, stencilBits);

	if (pixelFormat == 0) {
		return false;
	}

	::MessageBox(0, L"Found pixel format.", L"Error", MB_ICONEXCLAMATION | MB_OK);

	// set members of PIXELFORMATDESCRIPTOR with given mode ID
	::DescribePixelFormat(hdc, pixelFormat, sizeof(pfd), &pfd);
	// set the fixel format
	if (!::SetPixelFormat(hdc, pixelFormat, &pfd))
		return false;

	return true;
}

///////////////////////////////////////////////////////////////////////////////
// find the best pixel format
///////////////////////////////////////////////////////////////////////////////
int findPixelFormat(int colorBits, int depthBits, int stencilBits)
{
	int currMode;                               // pixel format mode ID
	int bestMode = 0;                           // return value, best pixel format
	int currScore = 0;                          // points of current mode
	int bestScore = 0;                          // points of best candidate
	PIXELFORMATDESCRIPTOR pfd;

	// search the available formats for the best mode
	bestMode = 0;
	bestScore = 0;
	for (currMode = 1; ::DescribePixelFormat(hdc, currMode, sizeof(pfd), &pfd) > 0; ++currMode)
	{
		// ignore if cannot support opengl
		if (!(pfd.dwFlags & PFD_SUPPORT_OPENGL))
			continue;

		// ignore if cannot render into a window
		if (!(pfd.dwFlags & PFD_DRAW_TO_WINDOW))
			continue;

		// ignore if cannot support rgba mode
		if ((pfd.iPixelType != PFD_TYPE_RGBA) || (pfd.dwFlags & PFD_NEED_PALETTE))
			continue;

		// ignore if not double buffer
		if (!(pfd.dwFlags & PFD_DOUBLEBUFFER))
			continue;

		// try to find best candidate
		currScore = 0;

		// colour bits
		if (pfd.cColorBits >= colorBits) ++currScore;
		if (pfd.cColorBits == colorBits) ++currScore;

		// depth bits
		if (pfd.cDepthBits >= depthBits) ++currScore;
		if (pfd.cDepthBits == depthBits) ++currScore;

		// stencil bits
		if (pfd.cStencilBits >= stencilBits) ++currScore;
		if (pfd.cStencilBits == stencilBits) ++currScore;

		// alpha bits
		if (pfd.cAlphaBits > 0) ++currScore;

		// check if it is best mode so far
		if (currScore > bestScore)
		{
			bestScore = currScore;
			bestMode = currMode;
		}
	}

	return bestMode;
}*/

GLint MySetPixelFormat(int nCmdShow)
{

	//hdc = GetDC(handle);

	PIXELFORMATDESCRIPTOR pfd = { sizeof(pfd), 1 };
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_SUPPORT_COMPOSITION | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cAlphaBits = 8;
	pfd.iLayerType = PFD_MAIN_PLANE;

	GLint  iPixelFormat;

	// get the device context's best, available pixel format match
	if ((iPixelFormat = ChoosePixelFormat(hdc, &pfd)) == 0)
	{
		::MessageBox(0, L"Set Viewport.", L"Error", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// make that match the device context's current pixel format
	if (SetPixelFormat(hdc, iPixelFormat, &pfd) == FALSE)
	{
		::MessageBox(0, L"Set Viewport.", L"Error", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	if ((hglrc = wglCreateContext(hdc)) == NULL)
	{
		::MessageBox(0, L"Set Viewport.", L"Error", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	if ((wglMakeCurrent(hdc, hglrc)) == NULL)
	{
		::MessageBox(0, L"Set Viewport.", L"Error", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	//ReleaseDC(handle, hdc);
	ShowWindow(handle, nCmdShow);
	::MessageBox(0, L"Sucess.", L"Error", MB_ICONEXCLAMATION | MB_OK);


	return 1;
}

bool InitGL(GLvoid)										// All setup for opengl goes here
{
	glShadeModel(GL_SMOOTH);							// Enable smooth shading
	glClearColor(0.1f, 0.7f, 0.2f, 0.5f);				// Black background
	glClearDepth(1.0f);									// Depth buffer setup
	glEnable(GL_DEPTH_TEST);							// Enables depth testing
	glDepthFunc(GL_LEQUAL);								// The type of depth testing to do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really nice perspective calculations
	return TRUE;										// Initialisation went ok
}

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize and initialise the gl window
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void render() {
	while (true) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear screen and depth buffer
		glLoadIdentity();									// Reset the current modelview matrix
		glTranslatef(-1.5f, 0.0f, -6.0f);						// Move left 1.5 units and into the screen 6.0
		glRotatef(rtri, 0.0f, 1.0f, 0.0f);						// Rotate the triangle on the y axis 
		glBegin(GL_TRIANGLES);								// Start drawing a triangle
		glColor3f(1.0f, 0.0f, 0.0f);						// Red
		glVertex3f(0.0f, 1.0f, 0.0f);					// Top Of triangle (front)
		glColor3f(0.0f, 1.0f, 0.0f);						// Green
		glVertex3f(-1.0f, -1.0f, 1.0f);					// Left of triangle (front)
		glColor3f(0.0f, 0.0f, 1.0f);						// Blue
		glVertex3f(1.0f, -1.0f, 1.0f);					// Right of triangle (front)
		glColor3f(1.0f, 0.0f, 0.0f);						// Red
		glVertex3f(0.0f, 1.0f, 0.0f);					// Top Of triangle (right)
		glColor3f(0.0f, 0.0f, 1.0f);						// Blue
		glVertex3f(1.0f, -1.0f, 1.0f);					// Left of triangle (right)
		glColor3f(0.0f, 1.0f, 0.0f);						// Green
		glVertex3f(1.0f, -1.0f, -1.0f);					// Right of triangle (right)
		glColor3f(1.0f, 0.0f, 0.0f);						// Red
		glVertex3f(0.0f, 1.0f, 0.0f);					// Top Of triangle (back)
		glColor3f(0.0f, 1.0f, 0.0f);						// Green
		glVertex3f(1.0f, -1.0f, -1.0f);					// Left of triangle (back)
		glColor3f(0.0f, 0.0f, 1.0f);						// Blue
		glVertex3f(-1.0f, -1.0f, -1.0f);					// Right of triangle (back)
		glColor3f(1.0f, 0.0f, 0.0f);						// Red
		glVertex3f(0.0f, 1.0f, 0.0f);					// Top Of triangle (left)
		glColor3f(0.0f, 0.0f, 1.0f);						// Blue
		glVertex3f(-1.0f, -1.0f, -1.0f);					// Left of triangle (left)
		glColor3f(0.0f, 1.0f, 0.0f);						// Green
		glVertex3f(-1.0f, -1.0f, 1.0f);					// Right of triangle (left)
		glEnd();											// Done drawing the pyramid

		glLoadIdentity();									// Reset the current modelview matrix
		glTranslatef(1.5f, 0.0f, -7.0f);						// Move right 1.5 units and into the screen 7.0
		glRotatef(rquad, 1.0f, 1.0f, 1.0f);					// Rotate the quad on the x axis 
		glBegin(GL_QUADS);									// Draw a quad
		glColor3f(0.0f, 1.0f, 0.0f);						// Set The color to green
		glVertex3f(1.0f, 1.0f, -1.0f);					// Top Right of the quad (top)
		glVertex3f(-1.0f, 1.0f, -1.0f);					// Top Left of the quad (top)
		glVertex3f(-1.0f, 1.0f, 1.0f);					// Bottom left of the quad (top)
		glVertex3f(1.0f, 1.0f, 1.0f);					// Bottom right of the quad (top)
		glColor3f(1.0f, 0.5f, 0.0f);						// Set The color to orange
		glVertex3f(1.0f, -1.0f, 1.0f);					// Top Right of the quad (bottom)
		glVertex3f(-1.0f, -1.0f, 1.0f);					// Top Left of the quad (bottom)
		glVertex3f(-1.0f, -1.0f, -1.0f);					// Bottom left of the quad (bottom)
		glVertex3f(1.0f, -1.0f, -1.0f);					// Bottom right of the quad (bottom)
		glColor3f(1.0f, 0.0f, 0.0f);						// Set The color to red
		glVertex3f(1.0f, 1.0f, 1.0f);					// Top Right of the quad (front)
		glVertex3f(-1.0f, 1.0f, 1.0f);					// Top Left of the quad (front)
		glVertex3f(-1.0f, -1.0f, 1.0f);					// Bottom left of the quad (front)
		glVertex3f(1.0f, -1.0f, 1.0f);					// Bottom right of the quad (front)
		glColor3f(1.0f, 1.0f, 0.0f);						// Set The color to yellow
		glVertex3f(1.0f, -1.0f, -1.0f);					// Top Right of the quad (back)
		glVertex3f(-1.0f, -1.0f, -1.0f);					// Top Left of the quad (back)
		glVertex3f(-1.0f, 1.0f, -1.0f);					// Bottom left of the quad (back)
		glVertex3f(1.0f, 1.0f, -1.0f);					// Bottom right of the quad (back)
		glColor3f(0.0f, 0.0f, 1.0f);						// Set The color to blue
		glVertex3f(-1.0f, 1.0f, 1.0f);					// Top Right of the quad (left)
		glVertex3f(-1.0f, 1.0f, -1.0f);					// Top Left of the quad (left)
		glVertex3f(-1.0f, -1.0f, -1.0f);					// Bottom left of the quad (left)
		glVertex3f(-1.0f, -1.0f, 1.0f);					// Bottom right of the quad (left)
		glColor3f(1.0f, 0.0f, 1.0f);						// Set The color to violet
		glVertex3f(1.0f, 1.0f, -1.0f);					// Top Right of the quad (right)
		glVertex3f(1.0f, 1.0f, 1.0f);					// Top Left of the quad (right)
		glVertex3f(1.0f, -1.0f, 1.0f);					// Bottom left of the quad (right)
		glVertex3f(1.0f, -1.0f, -1.0f);					// Bottom right of the quad (right)
		glEnd();

		rtri += 0.2f;											// Increase the rotation variable for the triangle
		rquad -= 0.15f;
		//if (DrawGLScene() == 0)
			//::MessageBox(0, L"Error with draw", L"Error", MB_ICONEXCLAMATION | MB_OK);
		::SwapBuffers(hdc);
	}
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

	handle = CreateWindowEx(WS_EX_CLIENTEDGE, L"Test", NULL, style, 0, 0, 800, 600, 0, 0, hInstance, NULL);

	hdc = GetDC(handle);

	// if (setPixelFormat(32, 24, 8)) {
		//return 0;
	//}
	MySetPixelFormat(nCmdShow);

	if (!InitGL())
		::MessageBox(0, L"Failed", L"Error", MB_ICONEXCLAMATION | MB_OK);

	ReSizeGLScene(640, 480);
	rtri = 0.0f;
	rquad = 0.0f;
	std::thread thread(render);
	int exitCode;
	exitCode = mainMessageLoop();
	return 0;
}

