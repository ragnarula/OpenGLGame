#pragma once
#include "glm/glm.hpp"

struct CMaterialProperties
{
public:
	glm::vec4 ADSSh = glm::vec4(0.5, 0.5, 0.5, 16.0);
	GLuint DiffuseMap = 0;
	GLuint NormalMap = 0;
	bool UseDiffuseMap()
	{
		return DiffuseMap > 0;
	};
	bool UseNormalMap()
	{
		return NormalMap > 0;
	}
};