#pragma once
#include "rendering/LightManager.h"
#include "components/TransformComponent.h"
#include "components/WorldObject.h"

class CLightComponent
{
	CWorldObject& m_Owner;
	size_t m_LightNumber = -1;
	CLightManager* m_LightManager = nullptr;
	
public:
	CTransformComponent Transform;
public:

	CLightComponent(CWorldObject& Owner);
	~CLightComponent();
	void Initialise(const glm::vec3 & Colour, float Intensity, CLightManager* LightManager);

	CLightProperties& GetLight();
	void Tick(float DeltaTime);
};

