#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>
#include <filesystem>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Loger.h"

#define LOG(msg) Loger log(msg, __FILE__, __LINE__)

enum class Type{ACTIONS, LOOPBACK, OUTRO};
class App
{
public:
	App(int pFlags, std::string pNameOfWindow, const int pX, const int pY, const int pW, const int pH);
	~App() {
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		IMG_Quit();
		SDL_Quit();
	}

	void setDimensionOfWindow(const int pW, const int pH);
	void setPositionOfWindow(const int pX, const int pY);
	void setRgbOfWindow(uint8_t pR, uint8_t pG, uint8_t pB, uint8_t pA);

	void setDelay(int pDelay);
	void setActions(Type pType, std::function<void(void)> pFunc);
	void startLoop();
	void stopLoop();
	
	std::filesystem::path getPath() const	 { return std::filesystem::current_path();  }
	inline int getMousePosX() const          { return m_mouseX;							}
	inline int getMousePosY() const          { return m_mouseY;							}
	inline int getWindowsWidth() const       { return m_windowW;						}
	inline int getWindowsHeight() const      { return m_windowH;						}
	inline SDL_Window* getWindow() const     { return m_window;							}
	inline SDL_Renderer* getRenderer() const { return m_renderer;						}
	inline SDL_bool loopIsRunning() const    { return m_isRunning;						}
	
private:
	SDL_Renderer* m_renderer;
	SDL_Window* m_window;
	SDL_bool m_isRunning; 
	int m_mouseX, m_mouseY;
	int m_delay;
	int m_windowW,m_windowH;
	uint8_t m_r, m_g, m_b, m_a;
	std::unordered_map<Type, std::function<void(void)>> m_mapOfFunc;
};

