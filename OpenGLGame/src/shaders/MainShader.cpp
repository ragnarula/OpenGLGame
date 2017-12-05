#include "stdafx.h"
#include "MainShader.h"
#include "rendering/uniformnames.h"

CMainShader::CMainShader(const CShaderProperties & ShaderProperties) :
	m_ShaderProperties(ShaderProperties)
{
	SetUniformLocations();
}


CMainShader::~CMainShader()
{
}

void CMainShader::Bind()
{
	glUseProgram(m_ShaderProperties.Program);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, m_LightBuffer);
}

void CMainShader::Unbind()
{
	glUseProgram(0);
}

void CMainShader::SetUniformLocations()
{
	m_MVP = glGetUniformLocation(m_ShaderProperties.Program, U_MVP);
	m_MV = glGetUniformLocation(m_ShaderProperties.Program, U_MV);
	m_Norm = glGetUniformLocation(m_ShaderProperties.Program, U_NORM);
	m_DiffuseMap = glGetUniformLocation(m_ShaderProperties.Program, U_DIFFUSE_MAP);
	m_NormalMap = glGetUniformLocation(m_ShaderProperties.Program, U_NORMAL_MAP);
	m_UseDiffuseMap = glGetUniformLocation(m_ShaderProperties.Program, U_USE_DIFFUSE_MAP);
	m_UseNormalMap = glGetUniformLocation(m_ShaderProperties.Program, U_USE_NORMAL_MAP);
	m_NumLights = glGetUniformLocation(m_ShaderProperties.Program, U_NUM_LIGHTS);
	//m_Lights = glGetProgramResourceIndex(m_ShaderProperties.Program, GL_SHADER_STORAGE_BLOCK, U_LIGHTS_BUFFER);
	m_ADSSh = glGetUniformLocation(m_ShaderProperties.Program, U_MATERIAL_ADSSH);
}

void CMainShader::SetMatrices(const glm::mat4& Model, const glm::mat4& View, const glm::mat4& Projection)
{
	glm::mat4 MV = View * Model;
	glUniformMatrix4fv(m_MV, 1, GL_FALSE, (GLfloat*)&MV);

	glm::mat3 Normal = glm::transpose(glm::inverse(glm::mat3(MV)));
	glUniformMatrix3fv(m_Norm, 1, GL_FALSE, (GLfloat*) &Normal);

	glm::mat4 MVP = Projection * MV;
	glUniformMatrix4fv(m_MVP, 1, GL_FALSE, (GLfloat*) &MVP);
}

void CMainShader::SetLightBuffer(GLuint LightBuffer)
{
	m_LightBuffer = LightBuffer;
}

void CMainShader::SetLightProperties(std::vector<CLightProperties> Lights)
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_LightBuffer);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(CLightProperties) * Lights.size(), &Lights[0], GL_DYNAMIC_COPY);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	glUniform1ui(m_NumLights, Lights.size());
}

void CMainShader::SetAlbedoTexture(GLuint Texture)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
}

void CMainShader::SetMaterialProperties(CMaterialProperties & Material)
{
	glUniform4fv(m_ADSSh, 1, (GLfloat*) &Material.ADSSh);
	
	glUniform1i(m_DiffuseMap, 0);
	glUniform1i(m_NormalMap, 1);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Material.DiffuseMap);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, Material.NormalMap);

	glUniform1i(m_UseDiffuseMap, Material.UseDiffuseMap());
	glUniform1i(m_UseNormalMap, Material.UseNormalMap());
}