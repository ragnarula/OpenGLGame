#pragma once
#include <SDL2/SDL.h>
#include <string>

class CDisplay {
public:
	CDisplay(int width, int height, const std::string& title);

	void Clear(float r, float g, float b, float a);
	void Clear(int r, int g, int b, float a);

	void SwapBuffers();

	virtual ~CDisplay();
private:
	void operator=(const CDisplay& display) {}
	CDisplay(const CDisplay& display) {}

	SDL_Window* m_window;
	SDL_GLContext m_glContext;

};
