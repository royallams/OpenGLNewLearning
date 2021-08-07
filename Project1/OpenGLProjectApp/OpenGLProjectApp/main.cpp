#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Windows Dimension
const GLint WIDTH = 800, HEIGHT = 800;
const float toRadians = 3.14159265f / 180.0f;

//GLuint VAO, VBO, shader, uniformXmove;// ACesss the GPU memory throught this pointers or ids.
GLuint VAO, VBO, shader, uniformModel;// ACesss the GPU memory throught this pointers or ids.

bool direction = true;
float trioffset = 0.0f;
float tri_max_offset = 0.7f;
float tri_increment = 0.0005f;

float cur_angle = 0.0f;

void CreateTriangle()
{
	// Data 
	GLfloat vertices[] = {
			-1.0f, -1.0f, 0.0f, //:Left bottom Corner
			1.0f, -1.0f, 0.0f, // Right Bottom Corner
			0.0f, 1.0f, 0.0f
	};

	// VAO Creation 
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//VBO Creation 
	glCreateBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Actual Data passing
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);// Keeping in a memory .. no modification to data later.. static

	// Telling where the vertex is located , with size and how to read it ?
	glVertexAttribPointer(0,3, GL_FLOAT, false, 0, 0);

	glEnableVertexAttribArray(0);// Enable the vertex array for use.


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


}

static const char* vShader = "					\n\
#version 330									\n\
layout (location=0) in vec3 pos;				\n\
uniform mat4 Model;				\n\
void main()										\n\
{												\n\
	gl_Position = Model*vec4(0.4*pos.x,0.4*pos.y,pos.z,1.0);	\n\
}												\n\
";

static const char* fShader = "					\n\
#version 330									\n\
out vec4 colour;								\n\
void main()										\n\
{												\n\
	colour = vec4(1.0,0.0,0.0,1.0);				\n\
}												\n\
";

void AddShader(GLint program, const char* shader_code, GLenum shader_type)
{
	GLint theshader = glCreateShader(shader_type);// Create new shader based on type

	const GLchar* thecode[1];// Only 1 array of pointer
	thecode[0] = shader_code;

	GLint code_length[1];
	code_length[0] = strlen(shader_code);

	glShaderSource(theshader, 1, thecode, code_length);
	glCompileShader(theshader);

	// Get Errors 
	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theshader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theshader, sizeof(eLog), NULL, eLog);
		printf("Shader Compilation Failed: %s , Type - %d \n", eLog, shader_type);
		return;
	}

	printf("Shader Compilation : Success");

	glAttachShader(program, theshader);


	return;
}

void CompileShaders()
{
	//Create shader program
	shader = glCreateProgram();

	if (!shader)
	{
		printf("Shader Program Creation :Failed");
		return;
	}

	AddShader(shader, vShader, GL_VERTEX_SHADER);
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);

	// Get Errors 
	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shader);// Linking the shader program

	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Shader Linking Failed: %s \n", eLog);
		return;
	}

	printf("Shader Linking : Success");

	glValidateProgram(shader);// Validate with the current context
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Shader Validation Failed: %s \n", eLog);
		return;
	}
	uniformModel = glGetUniformLocation(shader, "Model");

	printf("Shader Validation : Success");
}

int main()
{
	//Initialize GLFW
	if (!glfwInit())
	{
		printf("GLFW Initilisation Failed");
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window properties
	//OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Core profile = no backward compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);// if any old ones detected then it informs
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//Allow Forward compatibilty


	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH
		, HEIGHT, "Test Window", NULL, NULL);

	if (!mainWindow)
	{
		printf("GLFW mainwindow creation failed!");
		glfwTerminate();
		return 1;
	}

	// Get Buffer size information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set Context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	// Allow modern extension Features
	glewExperimental = GL_TRUE;


	if (glewInit() != GLEW_OK)
	{
		printf("GLEW Initialisation failed");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}


	// Setup  Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);

	CreateTriangle();
	CompileShaders();


	//Loop untill window closed

	while (!glfwWindowShouldClose(mainWindow))
	{
		// Get + Handle User Input Events
		glfwPollEvents();


		if (direction)
		{
			trioffset += tri_increment;
		}
		else
		{
			trioffset -= tri_increment;
		}


		if (abs(trioffset) >= tri_max_offset)
		{
			direction = !direction;
		}



		//Clear Window
		//glClearColor(1.0f,0.0f, 0.0f, 1.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glUseProgram(shader);


		cur_angle += 0.001f;
		if (cur_angle >= 360)
		{
			cur_angle -= 360;
		}

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(trioffset, 0.0f, 0.0f));
		model = glm::rotate(model, cur_angle * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(2.0f, 2.0f, 1.0f));

		//glUniform1f(uniformXmove, trioffset);
		glUniformMatrix4fv(uniformModel,1,GL_FALSE,glm::value_ptr(model));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(mainWindow);

	}






	return 0;
} 