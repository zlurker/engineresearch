// GameEngine.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "GameEngine.h"
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <thread>

// Review again later
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

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

bool setPixelFormat(HDC hdc, int colorBits, int depthBits, int stencilBits);
int findPixelFormat(HDC hdc, int colorBits, int depthBits, int stencilBits);
void iniGL();
void initLights();
void setViewport(int w, int h);
void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ);
void render();
int DrawGLScene(GLvoid);


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void swapBuffers()
{
	::SwapBuffers(hdc);
}

int DrawGLScene(GLvoid)                                 // Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
	glLoadIdentity();                                   // Reset The Current Modelview Matrix
	return TRUE;                                        // Everything Went OK
}

void render() {
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		glClearColor(0.5f, 0.3f, 0.4f, 1);                       // background color
		glClear(GL_COLOR_BUFFER_BIT);

		setViewport(800, 400);

		//glClear(GL_COLOR_BUFFER_BIT);

		// save the initial ModelView matrix before modifying ModelView matrix
		glPushMatrix();

		// tramsform camera
		glTranslatef(0, 0, 20);
		glRotatef(30, 1, 0, 0);   // pitch
		glRotatef(40, 0, 1, 0);   // heading

		// draw a triangle
		glBegin(GL_TRIANGLES);
		glNormal3f(0, 0, 1);
		glColor3f(1, 0, 0);
		glVertex3f(3, -2, 0);
		glColor3f(0, 1, 0);
		glVertex3f(0, 2, 0);
		glColor3f(0, 0, 1);
		glVertex3f(-3, -2, 0);
		glEnd();

		glPopMatrix();
		//if (DrawGLScene() == 0)
			//::MessageBox(0, L"Error with draw", L"Error", MB_ICONEXCLAMATION | MB_OK);
		swapBuffers();
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


	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAMEENGINE));

	MSG msg;

	std::thread thread(render);

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
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMEENGINE));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_GAMEENGINE);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	wcex.style = CS_OWNDC;

	return RegisterClassExW(&wcex);
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
	HWND hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, szWindowClass, szTitle, style, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	//CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	//CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);


	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	hdc = ::GetDC(hWnd);
	if (!setPixelFormat(hdc, 32, 24, 8))
	{
		::MessageBox(0, L"Cannot set a suitable pixel format.", L"Error", MB_ICONEXCLAMATION | MB_OK);
		::ReleaseDC(hWnd, hdc);                     // remove device context
		return false;
	}

	if (!(hglrc = ::wglCreateContext(hdc))) {
		::MessageBox(0, L"hglrc not set up.", L"Error", MB_ICONEXCLAMATION | MB_OK);
	}
	//::ReleaseDC(hWnd, hdc);

	if (!::wglMakeCurrent(hdc, hglrc)) {
		::MessageBox(0, L"make current not setup.", L"Error", MB_ICONEXCLAMATION | MB_OK);
	}

	iniGL();
	RECT rect;

	::GetClientRect(hWnd, &rect);
	//::MessageBox(0, L"Set Rect.", L"Error", MB_ICONEXCLAMATION | MB_OK);

	//::MessageBox(0, L"Set Viewport.", L"Error", MB_ICONEXCLAMATION | MB_OK);


	//while (true);

	return TRUE;
}

void setViewport(int w, int h) {// set viewport to be the entire window
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// set perspective viewing frustum
	float aspectRatio = (float)w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)(w) / h, 0.1f, 20.0f); // FOV, AspectRatio, NearClip, FarClip

	// switch to modelview matrix in order to set scene
	glMatrixMode(GL_MODELVIEW);
}

void iniGL() {
	glShadeModel(GL_SMOOTH);                        // shading mathod: GL_SMOOTH or GL_FLAT
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);          // 4-byte pixel alignment

	// enable /disable features
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	//glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	//glEnable(GL_TEXTURE_2D);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);

	// track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glClearColor(0.5f, 0.3f, 0.4f, 1);                       // background color
	glClear(GL_COLOR_BUFFER_BIT);
	glClearStencil(0);                              // clear stencil buffer
	glClearDepth(1.0f);

	
	glDepthFunc(GL_LEQUAL);

	initLights();
	setCamera(0, 0, 10, 0, 0, 0);
}

void initLights()
{
	// set up light colors (ambient, diffuse, specular)
	GLfloat lightKa[] = { .2f, .2f, .2f, 1.0f };      // ambient light
	GLfloat lightKd[] = { .7f, .7f, .7f, 1.0f };      // diffuse light
	GLfloat lightKs[] = { 1, 1, 1, 1 };               // specular light
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);

	// position the light
	float lightPos[4] = { 0, 0, 20, 1 }; // positional light
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glEnable(GL_LIGHT0);                            // MUST enable each light source after configuration
}

///////////////////////////////////////////////////////////////////////////////
// set camera position and lookat direction
///////////////////////////////////////////////////////////////////////////////
void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(posX, posY, posZ, targetX, targetY, targetZ, 0, 1, 0); // eye(x,y,z), focal(x,y,z), up(x,y,z)
}

bool setPixelFormat(HDC hdc, int colorBits, int depthBits, int stencilBits)
{
	PIXELFORMATDESCRIPTOR pfd;

	// find out the best matched pixel format
	int pixelFormat = findPixelFormat(hdc, colorBits, depthBits, stencilBits);
	if (pixelFormat == 0)
		return false;

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
int findPixelFormat(HDC hdc, int colorBits, int depthBits, int stencilBits)
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
