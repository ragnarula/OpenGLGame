#include "stdafx.h"
#include "MeshComponent.h"

CMeshComponent::CMeshComponent(const CMeshProperties & Mesh) : 
	m_MeshProperties(Mesh)
{
}


CMeshComponent::~CMeshComponent()
{
}

GLuint CMeshComponent::GetVAO() const
{
	return m_MeshProperties.m_VAO;
}

GLuint CMeshComponent::GetVBO() const
{
	return m_MeshProperties.m_VBO;
}

size_t CMeshComponent::GetVertexCount() const
{
	return m_MeshProperties.m_VertexCount;
}

bool CMeshComponent::IsIndexed() const
{
	return m_MeshProperties.m_VBO > -1;
}