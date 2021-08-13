#include "Window.h"

Window::Window()
{
	// take the defaults 
	width = 800;
	height = 600;

	// Make Keys all 0 
	for(size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
	
	// Intiallly there is no change so default to 0
	xChange = 0.0f;
	yChange = 0.0f;
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
	// Take user defined size 
	width = windowWidth;
	height = windowHeight;

	// Initiliaze 0 
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
	
	// No change initially
	xChange = 0.0f;
	yChange = 0.0f;
}

int Window::Initialise()
{
	// GLFW Start , if failed return,
	if (!glfwInit())
	{
		printf("Error Initialising GLFW");
		glfwTerminate();
		return 1;
	}

	// Setup GLFW Windows Properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core Profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow forward compatiblity
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the window
	mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
	if (!mainWindow)
	{
		printf("Error creating GLFW window!");
		glfwTerminate();
		return 1;
	}

	// Get buffer size information
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set the current context
	glfwMakeContextCurrent(mainWindow);

	// Handle Key + Mouse Input
	createCallbacks();
	//glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);// If we dont want to see the cursor.

	// Allow modern extension access
	glewExperimental = GL_TRUE;


	// OPen GL wrangler starts
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		printf("Error: %s", glewGetErrorString(error));
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	// Create Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);// Pass buffer sizes to the OpenGL

	glfwSetWindowUserPointer(mainWindow, this);// This will tell the glfw to enable callbacks for mainwindow. otherwise the static function has no idea of the object
}

void Window::createCallbacks()
{
	// For Keyboard 
	glfwSetKeyCallback(mainWindow, handleKeys);// Which window?, Which callback function?
	// For Mouse
	glfwSetCursorPosCallback(mainWindow, handleMouse);
}

GLfloat Window::getXChange()
{
	// Once you take the changes , then reset 
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	// Once you take the changes , then reset 
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	// Get the window that we passed earlier.
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	// If it is escape pressed then close 
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)// if pressed
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	// If pressed then, put the value true , else false.
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
		}
	}
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	// Take the window which we passed earlier.
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	// IF it is just the first move, the only take the current position. 
	// No change for now.
	// Make it false.
	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}


	theWindow->xChange = xPos - theWindow->lastX;// new postion - previous position
	theWindow->yChange = theWindow->lastY - yPos;// previous y - last y, Done opposite. Gives best result
	//theWindow->yChange = yPos - theWindow->lastY;// previous y - last y, Done opposite. Gives best result

	// Back up the current position.
	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);// Destroy the mainwindow memory
	glfwTerminate();// Stop the GLFW context.
}
