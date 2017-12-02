#pragma once

#include "components/MeshComponent.h"
#include "components/LightComponent.h"
#include "components/WorldObject.h"

class CEntity : public CWorldObject
{
public:
	CMeshComponent Mesh;
	CLightComponent LightSource;

	CEntity();
	~CEntity();

	void Tick(float DeltaTime);
};

