#pragma once
#include <vector>
#include <gl/glew.h>
#include "rendering/MeshProperties.h"
#include "rendering/Vertex.h"
#include "rendering/ShaderProperties.h"

class CGPULoader {
	std::vector<GLuint> m_vaos;
	std::vector<GLuint> m_vbos;
	std::vector<GLuint> m_textures;
	std::vector<CShaderProperties> m_programs;

	GLuint GenerateVAO();
	GLuint GenerateVBO();
	GLuint GenerateTexture();
	void BufferVertexData(const std::vector<Vertex> &Verticies, GLuint VBO) const;
	void BufferIndexData(const std::vector<unsigned int> &Indices, GLuint VBO) const;
	void BufferImageData2d(const std::string &FileName, GLuint Id) const;
	void SetupTexture(GLuint Id) const;
	GLuint CreateShader(const std::string &text, unsigned int type);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string &errorMessage);
	std::string LoadShader(const std::string& FileName);

public:
	CGPULoader();
	~CGPULoader();

	CMeshProperties LoadIndexedMesh(std::vector<Vertex> &Vertices, std::vector<unsigned int> &Indices);
	CMeshProperties LoadMesh(std::vector<Vertex> &Vertices);
	GLuint LoadTexture(const std::string& FileName);
	GLuint CreateShaderbuffer();
	
	CShaderProperties LoadProgram(const std::string &fileName);
};