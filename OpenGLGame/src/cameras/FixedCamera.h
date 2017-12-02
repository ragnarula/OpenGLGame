#pragma once
#include "rendering/Camera.h"
#include <glm/glm.hpp>

class CFixedCamera : public ICamera
{
	glm::mat4 m_Projection;
	glm::mat4 m_View;

public:
	CFixedCamera();
	~CFixedCamera();

	void SetProjection(float FOV, float Aspect, float ZNear, float ZFar);
	void SetView(glm::vec3 Eye, glm::vec3 Target, glm::vec3 Up);

	glm::mat4 GetViewMatrix() override;
	glm::mat4 GetProjectionMatrix() override;
};

