#include "MainWindow.h"

MainWindow::MainWindow()
{
	width = 800;
	height = 600;
}

MainWindow::MainWindow(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
}

int MainWindow::Initialize()
{
	// We know that in C++ the program execution starts from the main() function likewise GLFW initialization starts with this function().
	// Initialize GLFW
	if (!glfwInit())
	{
		printf("GLFW initialization failed");
		glfwTerminate();
		return 1;
	}

	// Set Windows Properties
	// Set the version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

	// Set no for backward compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Set ok for Forward Compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Creating a Window
	 mainWindow = glfwCreateWindow(width, height, "Main Window", NULL, NULL);


	if (!mainWindow)
	{
		printf("GLFW window creation failed");
		glfwTerminate();
		return 1;
	}

	//get the information of the buffer size
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//Set Context for Glew to Use
	glfwMakeContextCurrent(mainWindow);
	//-------------------------------------------------------------------------------

	// Allow modern extensions features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("GLEW Initialization failed");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
	}

	//Depth test
	glEnable(GL_DEPTH_TEST);

	// Setting up the viewport 
	glViewport(0, 0, bufferWidth, bufferHeight);
}

MainWindow::~MainWindow()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}