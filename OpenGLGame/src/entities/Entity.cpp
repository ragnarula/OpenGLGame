#include "stdafx.h"
#include "Entity.h"


CEntity::CEntity() :
	Mesh(*this),
	LightSource(*this)
{
}


CEntity::~CEntity()
{
}

void CEntity::Tick(float DeltaTime)
{
	Mesh.Tick(DeltaTime);
	LightSource.Tick(DeltaTime);
}