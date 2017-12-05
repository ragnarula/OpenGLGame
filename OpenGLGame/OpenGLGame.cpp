// OpenGLGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "rendering/Display.h"

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

#include "shaders/MainShader.h"
#include "rendering/GPULoader.h"
#include "rendering/Vertex.h"
#include "cameras/FixedCamera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "rendering/LightManager.h"

int main(int argc, char *args[])
{
	CDisplay display(800, 600, "Game Window");
	display.Clear(255, 255, 255, 0);
	
	CGPULoader Loader;
	CMainShader MainShader(Loader.LoadProgram("res/shaders/MainShader"));
	MainShader.SetLightBuffer(Loader.CreateShaderbuffer());

	CFixedCamera FixedCamera;
	CLightManager LightManager;

	FixedCamera.SetProjection(45.0f, 800.0f / 600.0f, 0.3f, 1000.0f);
	FixedCamera.SetView(glm::vec3(0.0, 3.0, 10.0), glm::vec3(0.0, 3.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

	std::vector<Vertex> TriangleVertices = {
		Vertex{ glm::vec3(-1.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec2(0,0) },
		Vertex{ glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec2(1,0) },
		Vertex{ glm::vec3(0.0, 2.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec2(0.5, 1) },
	};

	std::vector<Vertex> PlaneVertices = {
		Vertex{ glm::vec3(-1.0, 0.0, -1.0), glm::vec3(1.0, 0.0, 1.0), glm::vec3(0.0, 1.0, 0.0), glm::vec2(0, 0) },
		Vertex{ glm::vec3(-1.0, 0.0, 1.0), glm::vec3(1.0, 0.0, 1.0), glm::vec3(0.0, 1.0, 0.0), glm::vec2(0, 1.0) },
		Vertex{ glm::vec3(1.0, 0.0, -1.0), glm::vec3(1.0, 0.0, 1.0), glm::vec3(0.0, 1.0, 0.0), glm::vec2(1, 0) },
		Vertex{ glm::vec3(-1.0, 0.0, 1.0), glm::vec3(1.0, 0.0, 1.0), glm::vec3(0.0, 1.0, 0.0), glm::vec2(0, 1.0) },
		Vertex{ glm::vec3(1.0, 0.0, -1.0), glm::vec3(1.0, 0.0, 1.0), glm::vec3(0.0, 1.0, 0.0), glm::vec2(1.0, 0) },
		Vertex{ glm::vec3(1.0, 0.0, 1.0), glm::vec3(1.0, 0.0, 1.0), glm::vec3(0.0, 1.0, 0.0), glm::vec2(1.0, 1.0) },
	};
	glm::mat4 PlaneMatrix = glm::scale(glm::mat4(1), glm::vec3(10));

	auto TriangleMesh = Loader.LoadMesh(TriangleVertices);
	auto PlaneMesh = Loader.LoadMesh(PlaneVertices);

	LightManager.CreateLight(glm::vec4(1), glm::vec3(0.0, 3.0, 10.0), glm::vec3(1));
	LightManager.CreateLight(glm::vec4(1), glm::vec3(10.0, 10.0, 0.0), glm::vec3(1));

	CMaterialProperties Material;
	Material.ADSSh = glm::vec4(0.1, 0.7, 0.1, 320.0);
	Material.DiffuseMap = Loader.LoadTexture("res/textures/teal.png");

	while (true)
	{
		display.Clear(255, 255, 34, 1);
		MainShader.Bind();
		MainShader.SetLightProperties(LightManager.GetLights());
		MainShader.SetMaterialProperties(Material);

		MainShader.SetMatrices(glm::mat4(1), FixedCamera.GetViewMatrix(), FixedCamera.GetProjectionMatrix());
		glBindVertexArray(TriangleMesh.VAO);
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei) TriangleMesh.VertexCount);

		MainShader.SetMatrices(PlaneMatrix, FixedCamera.GetViewMatrix(), FixedCamera.GetProjectionMatrix());
		glBindVertexArray(PlaneMesh.VAO);
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei) PlaneMesh.VertexCount);
		
		display.SwapBuffers();
	}
	return 0;
}

