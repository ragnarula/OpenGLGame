#include "stdafx.h"
#include "TransformComponent.h"
#include "glm/gtc/matrix_transform.hpp"


glm::mat4 CTransformComponent::GetMatrix(glm::mat4 Base)
{
	Base = glm::translate(Base, Position);
	Base = glm::rotate(Base, Rotation.x, glm::vec3(1.0, 0.0, 0.0));
	Base = glm::rotate(Base, Rotation.y, glm::vec3(0.0, 1.0, 0.0));
	Base = glm::rotate(Base, Rotation.z, glm::vec3(0.0, 0.0, 1.0));
	Base = glm::scale(Base, Scale);
	return Base;
}