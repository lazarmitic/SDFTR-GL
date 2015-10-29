#define GLEW_STATIC // If we want to link GLEW lib staticly we need to define this

#include <iostream>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

/// Keyboard event function
bool keys[256];
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS)
		keys[key] = true;
	if (action == GLFW_RELEASE)
		keys[key] = false;
}
///

int main(int argc, char * argv[])
{
	std::cout << "Stage: Rendering font map." << std::endl;

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

	glfwSetKeyCallback(windowHandle, key_callback);
	///
	
	/// GLEW Initialization
	glewExperimental = GL_TRUE;
	glewInit();
	///

	/// OpenGL States
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glViewport(0, 0, windowWidth, windowHeight);
	///

	/// Shader set-up
	Shader shader("vertexShader.vs", "fragmentShader.fs");

	shader.Use();
	///

	/// Quad set-up
	GLfloat vertices[] = {
		//Position x-y-z       //Texture coordinates x-y
		-0.5f, -0.5f,  0.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.0f,   1.0f, 0.0f,
		-0.5f,  0.5f,  0.0f,   0.0f, 1.0f,
		-0.5f,  0.5f,  0.0f,   0.0f, 1.0f,
		 0.5f, -0.5f,  0.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.0f,   1.0f, 1.0f
	};

	GLuint VBO, VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO
	glBindVertexArray(0); // Unbind VAO
	///

	/// Font map texture set-up
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("highres.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	///

	/// Text Map transformation variables
	float scale = 1.0;
	float angle = 0.0;
	glm::mat4 trans;
	///

	/// Get uniform locations
	GLuint transformLoc = glGetUniformLocation(shader.getProgram(), "transform");
	GLint loc = glGetUniformLocation(shader.getProgram(), "scale");
	///

	/// Render loop
	while (!glfwWindowShouldClose(windowHandle))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Render code goes here

		/// Transform Text Map
		if (keys[GLFW_KEY_W]) scale += 0.0006;
		if (keys[GLFW_KEY_S]) scale -= 0.0006;

		if (keys[GLFW_KEY_A]) angle += 0.006;
		if (keys[GLFW_KEY_D]) angle -= 0.006;

		trans = glm::mat4(1);
		trans = glm::scale(trans, glm::vec3(scale, scale, 1));
		trans = glm::rotate(trans, glm::radians(angle), glm::vec3(0.0, 0.0, 1.0));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		glUniform1f(loc, scale);
		///

		/// Draw quad
		glBindTexture(GL_TEXTURE_2D, texture);
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