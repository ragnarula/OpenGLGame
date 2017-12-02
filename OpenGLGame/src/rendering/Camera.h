#pragma once

#include <glm/glm.hpp>

class ICamera
{
public:
	virtual glm::mat4 GetViewMatrix() = 0;
	virtual glm::mat4 GetProjectionMatrix() = 0;
};