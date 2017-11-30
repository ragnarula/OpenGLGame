#include "stdafx.h"
#include "TransformComponent.h"
#include "glm/gtc/matrix_transform.hpp"


CTransformComponent::CTransformComponent()
{
}


CTransformComponent::~CTransformComponent()
{
}

void CTransformComponent::Translate(glm::vec3 Translation)
{
	m_Transform = glm::translate(m_Transform, Translation);
}

void CTransformComponent::Scale(glm::vec3 Axis)
{
	m_Transform = glm::scale(m_Transform, Axis);
}

void CTransformComponent::Rotate(float Degrees, glm::vec3 Axis)
{
	m_Transform = glm::rotate(m_Transform, glm::radians(Degrees), Axis);
}

glm::mat4 CTransformComponent::GetTransform() const
{
	return m_Transform;
}
