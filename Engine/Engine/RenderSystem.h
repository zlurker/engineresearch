#pragma once
#include <windows.h>        // Header File For Windows
#include <gl\gl.h>          // Header File For The OpenGL32 Library
#include <gl\glu.h> 

class RenderSystem {
public:
	RenderSystem(HWND handle,int w, int h);
	~RenderSystem();

	//void SetUpGL();
	GLvoid ReSizeGLScene(GLsizei width, GLsizei height);
	int InitGL(GLvoid);
	bool RenderSetUp();
	void Render();
	void Draw(GLvoid);
	void SwapBuffers();
	int width;
	int height;

	HWND wHandle;
	HDC hdc;
	HGLRC hrc;
};