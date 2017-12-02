#include "stdafx.h"
#include "LightComponent.h"
#include "rendering/LightManager.h"
#include "components/WorldObject.h"

CLightComponent::CLightComponent(CWorldObject& Owner) :
	m_Owner(Owner)
{
}

CLightComponent::~CLightComponent()
{
}

void CLightComponent::Initialise(const glm::vec3 & Colour, float Intensity, CLightManager * LightManager)
{
	m_LightManager = LightManager;
	
	glm::mat4 TotalTransform = m_Owner.Transform.GetMatrix() * Transform.GetMatrix();

	glm::vec3 Position = glm::vec3(TotalTransform * glm::vec4(0.0, 0.0, 0.0, 1.0));
	glm::vec3 Direction = glm::vec3(TotalTransform * glm::vec4(0.0, 0.0, -1.0, 1.0));
	
	m_LightNumber = LightManager->CreateLight(Colour, Position, Direction, Intensity);
}

CLightProperties & CLightComponent::GetLight()
{
	return m_LightManager->GetLight(m_LightNumber);
}

void CLightComponent::Tick(float DeltaTime)
{

	if (!m_LightManager) { return; }

	glm::mat4 TotalTransform = m_Owner.Transform.GetMatrix() * Transform.GetMatrix();

	glm::vec3 Position = glm::vec3(TotalTransform * glm::vec4(0.0, 0.0, 0.0, 1.0));
	glm::vec3 Direction = glm::vec3(TotalTransform * glm::vec4(0.0, 0.0, -1.0, 1.0));

	auto& LightProperties = m_LightManager->GetLight(m_LightNumber);

	LightProperties.Position = Position;
	LightProperties.Direction = Direction;
}