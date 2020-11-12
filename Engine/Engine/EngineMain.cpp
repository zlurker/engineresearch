#include <windows.h>        // Header File For Windows
#include <gl\gl.h>          // Header File For The OpenGL32 Library
#include <gl\glu.h>         // Header File For The GLu32 Library
#include "RenderSystem.h"
#include "InspectorSystem.h"
#include <thread>
#include "Procedure.h"

HDC         hDC = NULL;       // Private GDI Device Context
HGLRC       hRC = NULL;       // Permanent Rendering Context
HWND        hWnd = NULL;      // Holds Our Window Handle
HWND		mainWindow = NULL;
HINSTANCE   hInstance;      // Holds The Instance Of The Application
RenderSystem* rS;
InspectorSystem* iS;

bool    keys[256];          // Array Used For The Keyboard Routine
bool    active = TRUE;        // Window Active Flag Set To TRUE By Default
bool    fullscreen = TRUE;    // Fullscreen Flag Set To Fullscreen Mode By Default

//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);   // Declaration For WndProc
//LRESULT CALLBACK MainWindowProc(HWND, UINT, WPARAM, LPARAM);



HWND GenerateWindow(WNDCLASS wndclass, DWORD dwExStyle, DWORD dwStyle, int x, int y, int width, int height, HWND parent, int nCmdShow, LPVOID ctrl) {
	if (!RegisterClass(&wndclass))
		return NULL;

	HWND windowInst = CreateWindowEx(dwExStyle, wndclass.lpszClassName, NULL, dwStyle, x, y, width, height, parent, NULL, hInstance, ctrl);
	ShowWindow(windowInst, nCmdShow);
	UpdateWindow(windowInst);
	return windowInst;
}

/*int DrawGLScene(GLvoid)                                 // Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
	glLoadIdentity();                                   // Reset The Current Modelview Matrix
	glTranslatef(-1.5f, 0.0f, -6.0f);						// Move left 1.5 units and into the screen 6.0
	//glRotatef(rtri, 0.0f, 1.0f, 0.0f);						// Rotate the triangle on the y axis
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
	//glRotatef(rquad, 1.0f, 1.0f, 1.0f);					// Rotate the quad on the x axis
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

	return TRUE;                                        // Everything Went OK
}*/

GLvoid KillGLWindow(GLvoid)                             // Properly Kill The Window
{
	if (fullscreen)                                     // Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL, 0);                  // If So Switch Back To The Desktop
		ShowCursor(TRUE);                               // Show Mouse Pointer
	}

	if (hRC)                                            // Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))                 // Are We Able To Release The DC And RC Contexts?
		{
			//MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))                     // Are We Able To Delete The RC?
		{
			//MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;                                       // Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))                    // Are We Able To Release The DC
	{
		//MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;                                       // Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))                   // Are We Able To Destroy The Window?
	{
		//MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;                                      // Set hWnd To NULL
	}

	if (!UnregisterClass(L"OpenGL", hInstance))           // Are We Able To Unregister Class
	{
		// MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;                                 // Set hInstance To NULL
	}
}

/*  This Code Creates Our OpenGL Window.  Parameters Are:                   *
 *  title           - Title To Appear At The Top Of The Window              *
 *  width           - Width Of The GL Window Or Fullscreen Mode             *
 *  height          - Height Of The GL Window Or Fullscreen Mode            *
 *  bits            - Number Of Bits To Use For Color (8/16/24/32)          *
 *  fullscreenflag  - Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)   */

BOOL CreateGLWindow(int width, int height, int bits, int nCmdShow)
{

	WNDCLASS    wc;                     // Windows Class Structure
	DWORD       dwExStyle;              // Window Extended Style
	DWORD       dwStyle;                // Window Style
	RECT        WindowRect;             // Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;            // Set Left Value To 0
	WindowRect.right = (long)width;       // Set Right Value To Requested Width
	WindowRect.top = (long)0;             // Set Top Value To 0
	WindowRect.bottom = (long)height;     // Set Bottom Value To Requested Height

	//fullscreen = fullscreenflag;          // Set The Global Fullscreen Flag

	//hInstance = GetModuleHandle(NULL);                // Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW;   // Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)Win::WndProc;                    // WndProc Handles Messages
	wc.cbClsExtra = 0;                                    // No Extra Window Data
	wc.cbWndExtra = 0;                                    // No Extra Window Data
	wc.hInstance = hInstance;                            // Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);          // Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);          // Load The Arrow Pointer
	wc.hbrBackground = NULL;                                 // No Background Required For GL
	wc.lpszMenuName = NULL;                                 // We Don't Want A Menu
	wc.lpszClassName = L"OpenGL";                             // Set The Class Name

	/*if (!RegisterClass(&wc))                                    // Attempt To Register The Window Class
	{
		//MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                                           // Return FALSE
	}

	if (fullscreen)                                             // Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;                               // Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));   // Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);       // Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width;                // Selected Screen Width
		dmScreenSettings.dmPelsHeight = height;               // Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits;                 // Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		//if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		//{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			//if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
		   // {
				//fullscreen = FALSE;       // Windowed Mode Selected.  Fullscreen = FALSE
			//}
			//else
			//{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				//MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
			   // return FALSE;                                   // Return FALSE
			//}
		//}
	}

	if (fullscreen)                                             // Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;                              // Window Extended Style
		dwStyle = WS_POPUP;                                       // Windows Style
		ShowCursor(FALSE);                                      // Hide Mouse Pointer
	}
	else
	{
		//dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;           // Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;                            // Windows Style
	}*/

	//AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);     // Adjust Window To True Requested Size
	dwStyle =  WS_CHILD | WS_BORDER;

	GenerateWindow(
		wc,
		0,
		dwStyle,
		0,
		0,                               // Window Position
		WindowRect.right - WindowRect.left,   // Calculate Window Width
		WindowRect.bottom - WindowRect.top,   // Calculate Window Height
		mainWindow,
		nCmdShow,
		(LPVOID)rS);

	// Create The Window
/*if (!(hWnd = CreateWindowEx(0,                          // Extended Style For The Window
	L"OpenGL",                           // Class Name
	NULL,                              // Window Title
	dwStyle |                           // Defined Window Style
	WS_CHILD |
	WS_CLIPSIBLINGS,                    // Required Window Style
	0, 0,                               // Window Position
	WindowRect.right - WindowRect.left,   // Calculate Window Width
	WindowRect.bottom - WindowRect.top,   // Calculate Window Height
	mainWindow,                               // No Parent Window
	NULL,                               // No Menu
	hInstance,                          // Instance
	NULL)))                             // Dont Pass Anything To WM_CREATE
{
	//KillGLWindow();                             // Reset The Display
	//MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
	::MessageBox(0, L"Exiting.", L"Error", MB_ICONEXCLAMATION | MB_OK);
	return FALSE;                               // Return FALSE
}

//ShowWindow(hWnd, nCmdShow);
//UpdateWindow(hWnd);
::MessageBox(0, L"Completed.", L"Error", MB_ICONEXCLAMATION | MB_OK);*/
	return TRUE;                                    // Success
}




void CreateInspectorSystem(int nCmdShow) {
	iS = new InspectorSystem();

	WNDCLASS    wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;   // Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)Win::InspectorSystemProc;                    // WndProc Handles Messages
	wc.cbClsExtra = 0;                                    // No Extra Window Data
	wc.cbWndExtra = 0;                                    // No Extra Window Data
	wc.hInstance = hInstance;                            // Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);          // Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);          // Load The Arrow Pointer
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);                                 // No Background Required For GL
	wc.lpszMenuName = NULL;                                 // We Don't Want A Menu
	wc.lpszClassName = L"InspectorWindow";

	RECT        WindowRect;             // Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;            // Set Left Value To 0
	WindowRect.right = (long)400;       // Set Right Value To Requested Width
	WindowRect.top = (long)0;             // Set Top Value To 0
	WindowRect.bottom = (long)600;     // Set Bottom Value To Requested Height

	HWND inspectorWindow = GenerateWindow(wc, 0, WS_CHILD | WS_BORDER, 640, 0, WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top, mainWindow, nCmdShow, NULL);
	SetWindowTextA(inspectorWindow, "Transform");

	HWND tb = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 56, 10, 50, 18, inspectorWindow, 0, hInstance, 0);
	SetFocus(tb);
	//CreateWindow(L"BUTTON", 0, WS_CHILD | WS_VISIBLE, 70, 70, 80, 25, inspectorWindow, 0, hInstance, 0);
	iS->SetTextBox(tb);
	iS->StartInspectorThread();
}


int WINAPI WinMain(HINSTANCE   hInstance,          // Instance
	HINSTANCE   hPrevInstance,      // Previous Instance
	LPSTR       lpCmdLine,          // Command Line Parameters
	int         nCmdShow)           // Window Show State
{
	MSG     msg;                                    // Windows Message Structure
	BOOL    done = FALSE;                             // Bool Variable To Exit Loop



	// Ask The User Which Screen Mode They Prefer
	//if (MessageBox(NULL, "Would You Like To Run In Fullscreen Mode?", "Start FullScreen?", MB_YESNO | MB_ICONQUESTION) == IDNO)
	//{
	fullscreen = FALSE;                           // Windowed Mode

	rS = new RenderSystem(640, 480);

	WNDCLASS    wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;   // Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)Win::MainWindowProc;                    // WndProc Handles Messages
	wc.cbClsExtra = 0;                                    // No Extra Window Data
	wc.cbWndExtra = 0;                                    // No Extra Window Data
	wc.hInstance = hInstance;                            // Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);          // Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);          // Load The Arrow Pointer
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);                                 // No Background Required For GL
	wc.lpszMenuName = NULL;                                 // We Don't Want A Menu
	wc.lpszClassName = L"MainWindow";

	mainWindow = GenerateWindow(
		wc,
		0,
		WS_CLIPSIBLINGS |                   // Required Window Style
		WS_CLIPCHILDREN |
		WS_OVERLAPPEDWINDOW,                    // Required Window Style
		0, 0,                               // Window Position
		1000,   // Calculate Window Width
		600,   // Calculate Window Height
		NULL,                               // No Parent Window
		nCmdShow, NULL);// Set The Class Name

	/*if (!RegisterClass(&wc))                                    // Attempt To Register The Window Class
	{
		//MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                                           // Return FALSE
	}

	mainWindow = CreateWindowEx(0,                          // Extended Style For The Window
		L"MainWindow",                           // Class Name
		L"Test",                              // Window Title                          // Defined Window Style
		WS_CLIPSIBLINGS |                   // Required Window Style
		WS_CLIPCHILDREN |
		WS_OVERLAPPEDWINDOW,                    // Required Window Style
		0, 0,                               // Window Position
		1000,   // Calculate Window Width
		600,   // Calculate Window Height
		NULL,                               // No Parent Window
		NULL,                               // No Menu
		hInstance,                          // Instance
		NULL);
	//}

	ShowWindow(mainWindow, nCmdShow);
	UpdateWindow(mainWindow);*/

	/*HWND subWindow = CreateWindowEx(0,                          // Extended Style For The Window
		L"MainWindow",                           // Class Name
		L"Sub",                              // Window Title                          // Defined Window Style
		WS_OVERLAPPEDWINDOW |WS_CHILD,                  // Required Window Style
		0, 0,                               // Window Position
		1000,   // Calculate Window Width
		600,   // Calculate Window Height
		mainWindow,                               // No Parent Window
		NULL,                               // No Menu
		hInstance,                          // Instance
		NULL);

	ShowWindow(subWindow, nCmdShow);
	UpdateWindow(subWindow);*/
	// Create Our OpenGL Window
	if (!CreateGLWindow(640, 480, 16, nCmdShow))
	{
		return 0;                                   // Quit If Window Was Not Created
	}

	CreateInspectorSystem(nCmdShow);

	//ShowWindow(hWnd, SW_SHOW);
	while (!done)                                    // Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))   // Is There A Message Waiting?
		{
			if (msg.message == WM_QUIT)               // Have We Received A Quit Message?
			{
				done = TRUE;                          // If So done=TRUE
			}
			else                                    // If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);             // Translate The Message
				DispatchMessage(&msg);              // Dispatch The Message
			}
		}
		else                                        // If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if (active)                             // Program Active?
			{
				if (keys[VK_ESCAPE])                // Was ESC Pressed?
				{
					done = TRUE;                      // ESC Signalled A Quit
				}
				else                                // Not Time To Quit, Update Screen
				{
					//DrawGLScene();                  // Draw The Scene
					//SwapBuffers(hDC);         // Swap Buffers (Double Buffering)
				}
			}

			if (keys[VK_F1])                        // Is F1 Being Pressed?
			{
				keys[VK_F1] = FALSE;                  // If So Make Key FALSE
				//KillGLWindow();                     // Kill Our Current Window
				fullscreen = !fullscreen;             // Toggle Fullscreen / Windowed Mode
				// Recreate Our OpenGL Window
				//if (!CreateGLWindow(640, 480, 16,nCmdShow))
				//{
					//return 0;                       // Quit If Window Was Not Created
				//}
			}
		}
	}

	::MessageBox(0, L"Exiting.", L"Error", MB_ICONEXCLAMATION | MB_OK);
	// Shutdown
	//KillGLWindow();                                 // Kill The Window
	return (msg.wParam);                            // Exit The Program
}