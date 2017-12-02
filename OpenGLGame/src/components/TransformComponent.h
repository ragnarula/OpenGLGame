#pragma once

#include <glm/glm.hpp>

class CTransformComponent
{
public:
	glm::vec3 Position;
	glm::vec3 Scale;
	glm::vec3 Rotation;

	glm::mat4 GetMatrix(glm::mat4 Base = glm::mat4(1));
};

