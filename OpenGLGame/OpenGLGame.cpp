// OpenGLGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "rendering/Display.h"

#include <SDL2/SDL.h>
#include <iostream>

#include "shaders/MainShader.h"
#include "rendering/GPULoader.h"

int main(int argc, char *args[])
{
	CDisplay display(800, 600, "Game Window");
	display.Clear(255, 255, 255, 0);
	
	CGPULoader Loader;

	CMainShader MainShader(Loader.LoadProgram("res/shaders/MainShader"));

	return 0;
}

