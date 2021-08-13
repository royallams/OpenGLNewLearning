#pragma once

#include "stdio.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Window
{
public:
	Window();

	Window(GLint windowWidth, GLint windowHeight);

	int Initialise();

	GLint getBufferWidth() { return bufferWidth; }
	GLint getBufferHeight() { return bufferHeight; }

	bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

	bool* getsKeys() { return keys; }
	GLfloat getXChange();
	GLfloat getYChange();

	void swapBuffers() { glfwSwapBuffers(mainWindow); }

	~Window();

private:
	GLFWwindow* mainWindow;// GLFW mainwindow object pointer.

	GLint width, height;// Size of the window
	GLint bufferWidth, bufferHeight;// Provide this buffer to the Opengl.Get it from GLFW.

	bool keys[1024];//  Get the key strokes from the window. Pressed : true, Released : False

	GLfloat lastX;// Previous X position of mouse
	GLfloat lastY;// Previous Y position of mouse
	GLfloat xChange;// How much x position has changed?
	GLfloat yChange;// How much Y position has changed?
	bool mouseFirstMoved;//Check if the mouse has just entered the screen. avoid randomness.

	void createCallbacks();// Create both callbacks for keyboard and the mouse.
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);// All Key stroker handle further
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);// All Mouse movement handle further
};