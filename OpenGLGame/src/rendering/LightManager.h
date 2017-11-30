#pragma once
#include <vector>
#include "LightProperties.h"
#include <glm/glm.hpp>

class CLightManager
{
	std::vector<CLightProperties> m_Lights;

public:
	CLightManager();
	~CLightManager();

	size_t CreateLight(const glm::vec3& Colour, const glm::vec3& Position, const glm::vec3& Direction, float Intensity);
	CLightProperties& GetLight(size_t LightNumber);
};

