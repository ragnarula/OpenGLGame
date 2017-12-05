#pragma once
#include "gl/glew.h"
#include "glm/glm.hpp"
#include <vector>
#include "rendering/LightProperties.h"
#include "rendering/ShaderProperties.h"
#include "rendering/MaterialProperties.h"

class CMainShader
{
	CShaderProperties m_ShaderProperties;
	GLuint m_LightBuffer;

	GLint m_MVP;
	GLint m_MV;
	GLint m_Norm;

	GLint m_DiffuseMap;
	GLint m_NormalMap;
	GLint m_UseDiffuseMap;
	GLint m_UseNormalMap;
	GLint m_ADSSh;


	GLint m_Lights;
	GLint m_NumLights;

	void SetUniformLocations();
	
public:
	CMainShader(const CShaderProperties& ShaderProperties);
	~CMainShader();

	void Bind();
	void Unbind();

	void SetMatrices(const glm::mat4& Model, const glm::mat4& View, const glm::mat4& Projection);
	void SetLightBuffer(GLuint LightBuffer);
	void SetLightProperties(std::vector<CLightProperties> Lights);
	void SetAlbedoTexture(GLuint Texture);
	void SetMaterialProperties(CMaterialProperties& Material);
};

