#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
		GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity);

	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation,
					GLfloat diffuseIntensityLocation, GLfloat directionLocation);

	~Light();

private:
    glm::vec3 colour;// light Color
    GLfloat ambientIntensity;// Ambient Intensity

    glm::vec3 direction; // Diffuse Direction
    GLfloat diffuseIntensity;// Diffuse Intensity
};

