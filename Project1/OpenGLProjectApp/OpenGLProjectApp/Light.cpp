#include "Light.h"

Light::Light()
{
    // Any RGB color for AMbient light
    colour = glm::vec3(1.0f, 1.0f, 1.0f);
    // 0 means low 1 means high
    ambientIntensity = 1.0f;

    // Y axis fro top to bottom ..
	direction = glm::vec3(0.0f, -1.0f, 0.0f);

    // Low intensity
	diffuseIntensity = 0.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
	GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity)
{
    //User Defined values.
    colour = glm::vec3(red, green, blue);
	ambientIntensity = aIntensity;

	direction = glm::vec3(xDir, yDir, zDir);
	diffuseIntensity = dIntensity;
}

void Light::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation,
	GLfloat diffuseIntensityLocation, GLfloat directionLocation)
{
    // Getting locations from the shader and connecting with values.
	glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);

	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}

Light::~Light()
{
}
