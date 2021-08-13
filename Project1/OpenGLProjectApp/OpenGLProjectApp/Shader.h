#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL\glew.h>

class Shader
{
public:
	Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);// Directly take String codes	
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);// Take String from file.

	std::string ReadFile(const char* fileLocation);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();

	void UseShader();
	void ClearShader();

	~Shader();

private:
	GLuint shaderID, uniformProjection, uniformModel, uniformView;

	// Create program , add code, compile, link , Update model , projection , view IDs.
	void CompileShader(const char* vertexCode, const char* fragmentCode);// Compile the code 
	
	// Take shader code and compilte it .. and add it to the shader program
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);// Add and link it to the shader program 
};

