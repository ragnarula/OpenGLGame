#pragma once

#include <glm/glm.hpp>

class CTransformComponent
{
	glm::mat4 m_Transform;

public:
	CTransformComponent();
	~CTransformComponent();

	void Translate(glm::vec3 Translation);
	void Scale(glm::vec3 Axis);
	void Rotate(float Degrees, glm::vec3 Axis);

	glm::mat4 GetTransform() const;
};

