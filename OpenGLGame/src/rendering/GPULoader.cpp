#include "stdafx.h"
#include "GPULoader.h"
#include <iostream>
#include "Vertex.h"
#include "freeimage/FreeImage.h"
#include <string>
#include <iostream>
#include <fstream>

CGPULoader::CGPULoader() = default;

CGPULoader::~CGPULoader() {
	if (!m_vbos.empty())
	{
		glDeleteBuffers((GLsizei)m_vbos.size(), &m_vbos[0]);
		std::cout << "Deleted " << m_vbos.size() << " VBOs\n";
	}


	if (!m_vaos.empty())
	{
		glDeleteVertexArrays((GLsizei)m_vaos.size(), &m_vaos[0]);
		std::cout << "Deleted " << m_vaos.size() << " VAOs\n";

	}

	if (!m_textures.empty())
	{
		glDeleteTextures((GLsizei)m_textures.size(), &m_textures[0]);
		std::cout << "Deleted " << m_textures.size() << " Textures\n";
	}

	if (!m_programs.empty())
	{
		for (auto Shader : m_programs)
		{
			glDetachShader(Shader.Program, Shader.FragmentShader);
			glDeleteShader(Shader.FragmentShader);

			glDetachShader(Shader.Program, Shader.VertexShader);
			glDeleteShader(Shader.VertexShader);

			glDeleteProgram(Shader.Program);
		}
		std::cout << "Deleted " << m_programs.size() << " Shaders\n";
	}

}

CMeshProperties CGPULoader::LoadIndexedMesh(std::vector<Vertex> &Vertices, std::vector<unsigned int> &Indices) {
	GLuint vao = GenerateVAO();
	glBindVertexArray(vao);

	GLuint vertexVbo = GenerateVBO();
	BufferVertexData(Vertices, vertexVbo);

	GLuint indexVbo = GenerateVBO();
	BufferIndexData(Indices, indexVbo);

	// Unbind VAO
	glBindVertexArray(0);

	return { vao, indexVbo, Indices.size() };
}

void CGPULoader::BufferIndexData(const std::vector<unsigned int> &Indices, GLuint VBO) const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO);

	// Buffer index data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), &Indices[0], GL_STATIC_DRAW);

	// Unbind VBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void CGPULoader::BufferVertexData(const std::vector<Vertex> &Vertices, GLuint VBO) const {
	// Buffer Data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);

	// Enable position attrib
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

	// Enable colour attrib
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) sizeof(glm::vec3));

	// Enable norm attrib
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *)(sizeof(glm::vec3) * 2));

	// Enable uv attrib
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *)(sizeof(glm::vec3) * 3));

	// Unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint CGPULoader::GenerateVBO() {// create and bind vbo
	GLuint vbo;
	glGenBuffers(1, &vbo);
	m_vbos.push_back(vbo);
	return vbo;
}

GLuint CGPULoader::GenerateVAO() {
	GLuint vao;
	glGenVertexArrays(1, &vao);
	m_vaos.push_back(vao);
	return vao;
}

GLuint CGPULoader::LoadTexture(const std::string &FileName) {
	GLuint id = GenerateTexture();
	BufferImageData2d(FileName, id);
	SetupTexture(id);
	return id;
}

void CGPULoader::SetupTexture(GLuint id) const {
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void CGPULoader::BufferImageData2d(const std::string &FileName, GLuint Id) const {
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(FileName.c_str(), 0);
	FIBITMAP* temp = FreeImage_Load(format, FileName.c_str());

	FIBITMAP* image = FreeImage_ConvertTo32Bits(temp);
	FreeImage_Unload(temp);

	int w = FreeImage_GetWidth(image);
	int h = FreeImage_GetHeight(image);

	std::cout << "Loaded Texture " << FileName;
	std::cout << " Width: " << w << " Height: " << h << "\n";

	char* data = (char*)FreeImage_GetBits(image);

	glBindTexture(GL_TEXTURE_2D, Id);
	// upload
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	// free
	FreeImage_Unload(image);

	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint CGPULoader::GenerateTexture() {
	GLuint textureId;
	glGenTextures(1, &textureId);
	m_textures.push_back(textureId);
	return textureId;
}

CMeshProperties CGPULoader::LoadMesh(std::vector<Vertex> &Vertices) {
	GLuint vao = GenerateVAO();
	glBindVertexArray(vao);

	GLuint vertexVbo = GenerateVBO();
	BufferVertexData(Vertices, vertexVbo);
	return { vao, (GLuint) -1, Vertices.size() };
}


CShaderProperties CGPULoader::LoadProgram(const std::string & FileName)
{
	GLuint Program = glCreateProgram();
	GLuint VertexShader = CreateShader(LoadShader(FileName + ".vert.glsl"), GL_VERTEX_SHADER);
	GLuint FragmentShader = CreateShader(LoadShader(FileName + ".frag.glsl"), GL_FRAGMENT_SHADER);

	glAttachShader(Program, VertexShader);
	glAttachShader(Program, FragmentShader);

	glLinkProgram(Program);
	CheckShaderError(Program, GL_LINK_STATUS, true, "Error linking shader program");

	glValidateProgram(Program);
	CheckShaderError(Program, GL_LINK_STATUS, true, "Invalid shader program");

	CShaderProperties props{ Program, VertexShader, FragmentShader };
	m_programs.push_back(props);
	return props;
}


std::string CGPULoader::LoadShader(const std::string & FileName)
{
	std::ifstream file;
	file.open(FileName);

	std::string output;
	std::string line;

	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
			output.append(line);
			output.append("\n");
		}
	}
	else {
		std::cerr << "Unable to load shader: " << FileName << std::endl;
	}

	return output;
}

GLuint CGPULoader::CreateShader(const std::string & text, unsigned int type)
{
	GLuint shader = glCreateShader(type);

	if (shader == 0) {
		std::cerr << "Error compiling shader type: " << type << std::endl;
	}

	const GLchar* p = text.c_str();
	const GLint length = text.length();

	glShaderSource(shader, 1, &p, &length);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");

	return shader;
}

void CGPULoader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string & errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram) {
		glGetProgramiv(shader, flag, &success);
	}
	else {
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE) {
		if (isProgram) {
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else {
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

