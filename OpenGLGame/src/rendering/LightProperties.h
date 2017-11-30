#pragma once
#include <glm/glm.hpp>

struct CLightProperties
{
	glm::vec3 Colour;
	glm::vec3 Position;
	glm::vec3 Direction;
	float Intensity;
};