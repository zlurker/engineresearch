// GameEngine.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "GameEngine.h"
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <thread>


#define MAX_LOADSTRING 100


class renderer {
public:

};

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HDC hdc;
HGLRC hglrc;
renderer* rend;
std::thread thread;
DWORD style;

void render();
GLint MySetPixelFormat();
bool InitGL(GLvoid);
GLvoid ReSizeGLScene(GLsizei width, GLsizei height);
int DrawGLScene(GLvoid);

GLfloat	rtri;				// Angle for the triangle
GLfloat	rquad;				// Angle for the quad
const std::wstring wnd_class(L"my_wnd_class");


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void swapBuffers()
{

}

int DrawGLScene(GLvoid)                                 // Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
	glLoadIdentity();                                   // Reset The Current Modelview Matrix
	return TRUE;                                        // Everything Went OK
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

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_GAMEENGINE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	std::thread thread(render);

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAMEENGINE));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}




//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	memset(&wcex, 0, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMEENGINE));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = wnd_class.c_str();
	wcex.hIconSm = 0;

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	style = WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	HWND hWnd = ::CreateWindow(wnd_class.c_str(), NULL, style, 0, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
		

	if (!hWnd)
	{
		::MessageBox(0, L"Failed", L"Error", MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}

	hdc = ::GetDC(hWnd);
	MySetPixelFormat();

	ReleaseDC(hWnd, hdc);
	ShowWindow(hWnd, nCmdShow);

	if (!InitGL())
		::MessageBox(0, L"Failed", L"Error", MB_ICONEXCLAMATION | MB_OK);

	ReSizeGLScene(640, 480);

	rtri = 0.0f;
	rquad = 0.0f;
	return TRUE;
}

GLint MySetPixelFormat()
{
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),    // size of this pfd 
		1,                                // version number 
		PFD_DRAW_TO_WINDOW |              // support window 
		PFD_SUPPORT_OPENGL |              // support OpenGL 
		PFD_DOUBLEBUFFER,                 // double buffered 
		PFD_TYPE_RGBA,                    // RGBA type 
		24,                               // 24-bit color depth 
		0, 0, 0, 0, 0, 0,                 // color bits ignored 
		0,                                // no alpha buffer 
		0,                                // shift bit ignored 
		0,                                // no accumulation buffer 
		0, 0, 0, 0,                       // accum bits ignored 
		32,                               // 32-bit z-buffer     
		0,                                // no stencil buffer 
		0,                                // no auxiliary buffer 
		PFD_MAIN_PLANE,                   // main layer 
		0,                                // reserved 
		0, 0, 0                           // layer masks ignored 
	};

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

	::MessageBox(0, L"Sucess.", L"Error", MB_ICONEXCLAMATION | MB_OK);

	
	return 1;
}

bool InitGL(GLvoid)										// All setup for opengl goes here
{
	glShadeModel(GL_SMOOTH);							// Enable smooth shading
	glClearColor(0.3f, 0.4f, 0.1f, 0.5f);				// Black background
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

///////////////////////////////////////////////////////////////////////////////
// swap OpenGL frame buffers
///////////////////////////////////////////////////////////////////////////////


//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
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
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
