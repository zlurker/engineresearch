#pragma once
#include <windows.h>        // Header File For Windows
#include <gl\gl.h>          // Header File For The OpenGL32 Library
#include <gl\glu.h> 

class RenderSystem {
public:
	RenderSystem(HDC hdcHandle);
	~RenderSystem();

	//void SetUpGL();
	void Render();
	void Draw(GLvoid);
	void SwapBuffers();

	HDC hdc;
};