#include "stdafx.h"
#include "FixedCamera.h"
#include <glm/ext.hpp>

CFixedCamera::CFixedCamera()
{
}


CFixedCamera::~CFixedCamera()
{
}

void CFixedCamera::SetProjection(float FOV, float Aspect, float ZNear, float ZFar)
{
	m_Projection = glm::perspective(FOV, Aspect, ZNear, ZFar);
}

void CFixedCamera::SetView(glm::vec3 Eye, glm::vec3 Target, glm::vec3 Up)
{
	m_View = glm::lookAt(Eye, Target, Up);
}

glm::mat4 CFixedCamera::GetViewMatrix()
{
	return m_View;
}

glm::mat4 CFixedCamera::GetProjectionMatrix()
{
	return m_Projection;
}