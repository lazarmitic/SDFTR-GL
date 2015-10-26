#define GLEW_STATIC // If we want to link GLEW lib staticly we need to define this

#include <iostream>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

int main(int argc, char * argv[])
{
	std::cout << "Stage: Shader class implemented." << std::endl;

	/// GLFW Window initialization 
	int windowWidth = 800; 
	int windowHeight = 600;
	char * windowName = "Signed Distance Field Text Rendering";
	GLFWwindow *windowHandle;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	windowHandle = glfwCreateWindow(windowWidth, windowHeight, windowName, nullptr, nullptr);
	glfwMakeContextCurrent(windowHandle);
	///
	
	/// GLEW Initialization
	glewExperimental = GL_TRUE;
	glewInit();
	///

	/// OpenGL States
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glViewport(0, 0, windowWidth, windowHeight);
	///

	/// Render loop
	while (!glfwWindowShouldClose(windowHandle))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Render code goes here

		glfwSwapBuffers(windowHandle);
		glfwPollEvents();
	}
	///

	/// Free memory
	glfwDestroyWindow(windowHandle);
	///
	
	return 0;
}