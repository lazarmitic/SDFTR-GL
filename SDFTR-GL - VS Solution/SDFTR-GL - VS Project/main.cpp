#define GLEW_STATIC // If we want to link GLEW lib staticly we need to define this

#include <iostream>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

int main(int argc, char * argv[])
{
	std::cout << "Stage: GLEW initialized." << std::endl;

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

	/// Render loop
	while (!glfwWindowShouldClose(windowHandle))
	{
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