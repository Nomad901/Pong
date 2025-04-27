#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Loger.h"

#define LOG(msg) Loger log(msg, __FILE__, __LINE__)

class FactoryOfFront
{
public:
	FactoryOfFront(SDL_Renderer* pRenderer, std::string pText, SDL_Color& pColor, int pSize, std::filesystem::path pPath);
	~FactoryOfFront() {
		TTF_Quit();
		TTF_CloseFont(m_Font);
	}

	void changeText(SDL_Renderer* pRenderer, std::string pText);
	void fontIntoRect(SDL_Rect pRect);
	
	void render(SDL_Renderer* pRenderer) {
		SDL_RenderCopy(pRenderer, m_Texture, nullptr, &m_Rect);
	}

private:
	TTF_Font* m_Font;
	SDL_Texture* m_Texture;
	SDL_Rect m_Rect;
	SDL_Color m_Color;
	std::string m_Text;
};

