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
	m_Albedo = glGetUniformLocation(m_ShaderProperties.Program, U_ALBEDO);
	m_Lights = glGetUniformLocation(m_ShaderProperties.Program, U_LIGHTS);
	m_NumLights = glGetUniformLocation(m_ShaderProperties.Program, U_NUM_LIGHTS);
}

void CMainShader::SetMatrices(glm::mat4 Model, glm::mat4 View, glm::mat4 Projection)
{
	glm::mat4 MV = View * Model;
	glUniformMatrix4fv(m_MV, 1, GL_FALSE, (GLfloat*)&MV);

	glm::mat3 Normal = glm::transpose(glm::inverse(glm::mat3(MV)));
	glUniformMatrix4fv(m_Norm, 1, GL_FALSE, (GLfloat*)&Normal);

	glm::mat4 MVP = Projection * MV;
	glUniformMatrix4fv(m_MVP, 1, GL_FALSE, (GLfloat*)&MVP);
}