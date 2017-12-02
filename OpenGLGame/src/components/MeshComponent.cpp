#include "stdafx.h"
#include "MeshComponent.h"
#include "components/WorldObject.h"

CMeshComponent::CMeshComponent(CWorldObject& Owner) :
	m_Owner(Owner),
	m_MeshProperties({0, 0, 0})
{
}


CMeshComponent::~CMeshComponent()
{
}

GLuint CMeshComponent::GetVAO() const
{
	return m_MeshProperties.VAO;
}

GLuint CMeshComponent::GetVBO() const
{
	return m_MeshProperties.VBO;
}

size_t CMeshComponent::GetVertexCount() const
{
	return m_MeshProperties.VertexCount;
}

bool CMeshComponent::IsIndexed() const
{
	return m_MeshProperties.VBO > -1;
}

void CMeshComponent::Initialise(const CMeshProperties & Mesh)
{
	m_MeshProperties = Mesh;
}

void CMeshComponent::Tick(float DeltaTime)
{
}