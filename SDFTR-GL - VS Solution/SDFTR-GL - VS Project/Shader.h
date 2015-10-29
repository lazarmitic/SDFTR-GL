#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GLEW/glew.h>

class Shader
{
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	~Shader();

	void Use();
	GLuint getProgram()
	{
		return shaderProgram;
	}


private:
	std::string vShaderCode;
	std::string fShaderCode;

	GLuint vertex;
	GLuint fragment;

	GLuint shaderProgram;

	std::string ReadShaderFromFile(const GLchar * shaderFilePath);
	GLuint CreateShader(GLenum shaderType);
	GLuint CreateProgram();
};

