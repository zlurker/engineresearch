#include "RenderSystem.h"

RenderSystem::RenderSystem(int w, int h) : width(w), height(h) {
	pos = new int[3];
	pos[0] = 0;
	pos[1] = 0;
	pos[2] = 0;
}

RenderSystem::~RenderSystem() {

}

GLvoid RenderSystem::ReSizeGLScene(GLsizei width, GLsizei height)     // Resize And Initialize The GL Window
{
	if (height == 0)                                      // Prevent A Divide By Zero By
	{
		height = 1;                                       // Making Height Equal One
	}

	glViewport(0, 0, width, height);                       // Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
	glLoadIdentity();                                   // Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);                         // Select The Modelview Matrix
	glLoadIdentity();                                   // Reset The Modelview Matrix
}

void RenderSystem::SetHandle(HWND handle) {
	wHandle = handle;
	//::MessageBox(0, L"Handle set.", L"Error", MB_ICONEXCLAMATION | MB_OK);
}

int RenderSystem::InitGL(GLvoid)                                      // All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);                            // Enable Smooth Shading
	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);               // Black Background
	glClearDepth(1.0f);                                 // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);                             // The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Really Nice Perspective Calculations
	return TRUE;                                        // Initialization Went OK
}


int RenderSystem::GetPos(int c) {
	std::lock_guard<std::mutex> lock(lock);
	return pos[c];
}

void RenderSystem::SetPos(int x, int c) {
	std::lock_guard<std::mutex> lock(lock);
	pos[c] = x;
}

bool RenderSystem::RenderSetUp() {

	GLuint      PixelFormat;            // Holds The Results After Searching For A Match

	static  PIXELFORMATDESCRIPTOR pfd =              // pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),              // Size Of This Pixel Format Descriptor
		1,                                          // Version Number
		PFD_DRAW_TO_WINDOW |                        // Format Must Support Window
		PFD_SUPPORT_OPENGL |                        // Format Must Support OpenGL
		PFD_DOUBLEBUFFER,                           // Must Support Double Buffering
		PFD_TYPE_RGBA,                              // Request An RGBA Format
		24,                                       // Select Our Color Depth
		0, 0, 0, 0, 0, 0,                           // Color Bits Ignored
		0,                                          // No Alpha Buffer
		0,                                          // Shift Bit Ignored
		0,                                          // No Accumulation Buffer
		0, 0, 0, 0,                                 // Accumulation Bits Ignored
		32,                                         // 16Bit Z-Buffer (Depth Buffer)  
		0,                                          // No Stencil Buffer
		0,                                          // No Auxiliary Buffer
		PFD_MAIN_PLANE,                             // Main Drawing Layer
		0,                                          // Reserved
		0, 0, 0                                     // Layer Masks Ignored
	};

	if (!(hdc = GetDC(wHandle)))                         // Did We Get A Device Context?
	{
		//KillGLWindow();                             // Reset The Display
		//MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                               // Return FALSE
	}



	if (!(PixelFormat = ChoosePixelFormat(hdc, &pfd))) // Did Windows Find A Matching Pixel Format?
	{
		//KillGLWindow();                             // Reset The Display
		//MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                               // Return FALSE
	}

	if (!SetPixelFormat(hdc, PixelFormat, &pfd))       // Are We Able To Set The Pixel Format?
	{
		//KillGLWindow();                             // Reset The Display
		//MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                               // Return FALSE
	}

	if (!(hrc = wglCreateContext(hdc)))               // Are We Able To Get A Rendering Context?
	{
		//KillGLWindow();                             // Reset The Display
		//MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                               // Return FALSE
	}

	if (!wglMakeCurrent(hdc, hrc))                    // Try To Activate The Rendering Context
	{
		//KillGLWindow();                             // Reset The Display
		//MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                               // Return FALSE
	}

	//ShowWindow(wHandle, SW_SHOW);                       // Show The Window
	SetForegroundWindow(wHandle);                      // Slightly Higher Priority
	SetFocus(wHandle);                                 // Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);                   // Set Up Our Perspective GL Screen

	if (!InitGL())                                  // Initialize Our Newly Created GL Window
	{
		//KillGLWindow();                             // Reset The Display
		//MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                               // Return FALSE
	}

	return TRUE;
}

void RenderSystem::Render() {
	RenderSetUp();

	//::MessageBox(0, L"Set up completed.", L"Error", MB_ICONEXCLAMATION | MB_OK);
	while (true) {
		Draw();
		SwapBuffers();
	}
}

void RenderSystem::BeginLoop() {
	//RenderSetUp();
	//Render();

	//::MessageBox(0, L"Thread split off.", L"Error", MB_ICONEXCLAMATION | MB_OK);
	renderThread = std::thread(&RenderSystem::Render, this);
	//RenderSetUp();
	//while (1) {
		//Draw();
		//SwapBuffers();
	//}
}

void RenderSystem::Draw(GLvoid) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
	//glLoadIdentity();                                   // Reset The Current Modelview Matrix
	/*glTranslatef(-1.5f, 0.0f, -6.0f);						// Move left 1.5 units and into the screen 6.0
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
	glEnd();		*/									// Done drawing the pyramid
	glLoadIdentity();									// Reset the current modelview matrix
	glTranslatef(GetPos(0), GetPos(1), GetPos(2));						// Move right 1.5 units and into the screen 7.0
	glRotatef(20, 20, 20, 1.0f);					// Rotate the quad on the x axis 
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
}

void RenderSystem::SwapBuffers() {
	::SwapBuffers(hdc);
}