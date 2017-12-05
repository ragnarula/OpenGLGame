#include "stdafx.h"
#include "LightManager.h"


CLightManager::CLightManager()
{
}


CLightManager::~CLightManager()
{
}

size_t CLightManager::CreateLight(const glm::vec4 & Colour, const glm::vec3 & Position, const glm::vec3 & Direction)
{
	m_Lights.emplace_back(CLightProperties{ Colour, glm::vec4(Position, 1.0), glm::vec4(Direction, 1.0) });
	return m_Lights.size();
}

CLightProperties & CLightManager::GetLight(size_t LightNumber)
{
	return m_Lights[LightNumber];
}

std::vector<CLightProperties>& CLightManager::GetLights()
{
	return m_Lights;
}