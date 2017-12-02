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

int main(int argc, char *args[])
{
	CDisplay display(800, 600, "Game Window");
	display.Clear(255, 255, 255, 0);
	
	CGPULoader Loader;
	CMainShader MainShader(Loader.LoadProgram("res/shaders/MainShader"));
	CFixedCamera FixedCamera;
	FixedCamera.SetProjection(45.0f, 800.0f / 600.0f, 0.3f, 1000.0f);
	FixedCamera.SetView(glm::vec3(0.0, 0.0, 10.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

	std::vector<Vertex> vertices = {
		Vertex{ glm::vec3(-1.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec2() },
		Vertex{ glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec2() },
		Vertex{ glm::vec3(0.0, 2.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec2() },
	};

	auto MeshProps = Loader.LoadMesh(vertices);
	while (true)
	{
		display.Clear(255, 255, 34, 1);
		MainShader.Bind();
		MainShader.SetMatrices(glm::mat4(1), FixedCamera.GetViewMatrix(), FixedCamera.GetProjectionMatrix());
		glBindVertexArray(MeshProps.VAO);
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei) MeshProps.VertexCount);
		display.SwapBuffers();
	}
	return 0;
}

