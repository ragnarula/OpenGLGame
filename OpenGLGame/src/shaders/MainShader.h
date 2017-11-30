#pragma once
#include "gl/glew.h"
#include "glm/glm.hpp"
#include <vector>
#include "rendering\LightProperties.h"
#include "rendering/ShaderProperties.h"

class CMainShader
{
	CShaderProperties m_ShaderProperties;

	GLint m_MVP;
	GLint m_MV;
	GLint m_Norm;

	GLint m_Albedo;

	GLint m_Lights;
	GLint m_NumLights;

	void SetUniformLocations();
	
public:
	CMainShader(const CShaderProperties& ShaderProperties);
	~CMainShader();

	void Bind();
	void Unbind();

	void SetMatrices(glm::mat4 Model, glm::mat4 View, glm::mat4 Projection);
	void SetLightProperties(std::vector<CLightProperties> Lights);

};

