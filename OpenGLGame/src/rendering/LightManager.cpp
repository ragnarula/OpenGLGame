#include "stdafx.h"
#include "LightManager.h"


CLightManager::CLightManager()
{
}


CLightManager::~CLightManager()
{
}

size_t CLightManager::CreateLight(const glm::vec3 & Colour, const glm::vec3 & Position, const glm::vec3 & Direction, float Intensity)
{
	m_Lights.emplace_back(CLightProperties{ Colour, Position, Direction, Intensity });
	return m_Lights.size();
}

CLightProperties & CLightManager::GetLight(size_t LightNumber)
{
	return m_Lights[LightNumber];
}