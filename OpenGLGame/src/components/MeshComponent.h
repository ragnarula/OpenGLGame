#pragma once
#include "gl/glew.h"
#include "rendering/MeshProperties.h"
#include "components/WorldObject.h"

class CMeshComponent
{
	CWorldObject& m_Owner;
	
	CMeshProperties m_MeshProperties;
	bool m_IsIndexed;

public:
	CMeshComponent(CWorldObject& Owner);
	~CMeshComponent();
	
	CTransformComponent Transform;

	void Initialise(const CMeshProperties& Mesh);
	GLuint GetVAO() const;
	GLuint GetVBO() const;
	size_t GetVertexCount() const;
	bool IsIndexed() const;

	void Tick(float DeltaTime);
};

