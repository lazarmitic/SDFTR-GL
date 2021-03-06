#include "Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	vShaderCode = ReadShaderFromFile(vertexPath);
	fShaderCode = ReadShaderFromFile(fragmentPath);

	vertex = CreateShader(GL_VERTEX_SHADER);
	fragment = CreateShader(GL_FRAGMENT_SHADER);

	shaderProgram = CreateProgram();
}

Shader::~Shader()
{
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::Use()
{
	glUseProgram(shaderProgram);
}

std::string Shader::ReadShaderFromFile(const GLchar * shaderFilePath)
{
	std::string shaderCode;
	std::ifstream shaderFile;

	shaderFile.exceptions(std::ifstream::badbit);
	try
	{
		shaderFile.open(shaderFilePath);
		std::stringstream shaderStream;

		shaderStream << shaderFile.rdbuf();
		
		shaderFile.close();
		
		shaderCode = shaderStream.str();
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	return shaderCode;
}

GLuint Shader::CreateShader(GLenum shaderType)
{
	const GLchar *code;
	if(shaderType == GL_VERTEX_SHADER) code = vShaderCode.c_str();
	if(shaderType == GL_FRAGMENT_SHADER) code = fShaderCode.c_str();

	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &code, NULL);
	glCompileShader(shader);

	GLint success;
	GLchar infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n\n" << infoLog << std::endl;
	}

	return shader;
}

GLuint Shader::CreateProgram()
{
	GLuint shaderProgram;

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertex);
	glAttachShader(shaderProgram, fragment);
	glLinkProgram(shaderProgram);

	GLint success;
	GLchar infoLog[512];

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n\n" << infoLog << std::endl;
	}

	return shaderProgram;
}
