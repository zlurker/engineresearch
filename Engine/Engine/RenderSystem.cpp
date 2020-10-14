#include "RenderSystem.h"

RenderSystem::RenderSystem(HDC hdcHandle) :hdc(hdcHandle) {

}

RenderSystem::~RenderSystem() {

}

void RenderSystem::Render() {
	while (true) {
		Draw();
		SwapBuffers();
	}
}

void RenderSystem::Draw(GLvoid) {
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
}

void RenderSystem::SwapBuffers() {
	::SwapBuffers(hdc);
}