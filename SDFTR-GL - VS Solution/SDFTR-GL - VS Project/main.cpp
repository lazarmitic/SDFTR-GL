#define GLEW_STATIC // If we want to link GLEW lib staticly we need to define this

#include <iostream>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

int main(int argc, char * argv[])
{
	std::cout << "Stage: Rendering simple quad." << std::endl;

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

	/// Quad set-up
	GLfloat vertices[] = {
		-0.5f, -0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f,
		-0.5f,  0.5f,  0.0f,
		-0.5f,  0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f,
		 0.5f,  0.5f,  0.0f
	};

	GLuint VBO, VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO
	glBindVertexArray(0); // Unbind VAO
	///

	/// Shader set-up
	Shader shader("vertexShader.vs", "fragmentShader.fs");

	shader.Use();
	///

	/// Render loop
	while (!glfwWindowShouldClose(windowHandle))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Render code goes here

		/// Draw quad
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		///

		glfwSwapBuffers(windowHandle);
		glfwPollEvents();
	}
	///

	/// Free memory
	glfwDestroyWindow(windowHandle);
	///
	
	return 0;
}