#pragma once
#include "gl/glew.h"
#include "rendering/MeshProperties.h"

class CMeshComponent
{
	CMeshProperties m_MeshProperties;
	bool m_IsIndexed;

public:
	CMeshComponent(const CMeshProperties& Mesh);
	~CMeshComponent();

	GLuint GetVAO() const;
	GLuint GetVBO() const;
	size_t GetVertexCount() const;
	bool IsIndexed() const;
};

