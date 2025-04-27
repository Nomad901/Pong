#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <filesystem>

#include "SDL_image.h"
#include "SDL.h"

class FactoryOfRect
{
public:
	FactoryOfRect(SDL_Renderer* pRenderer);
	FactoryOfRect(SDL_Renderer* pRenderer, uint8_t pR, uint8_t pG, uint8_t pB, uint8_t pA);
	FactoryOfRect(SDL_Renderer* pRenderer, std::filesystem::path& pPath);
	~FactoryOfRect() {	
		if (m_texture) {
			SDL_DestroyTexture(m_texture);
		}
	}

    void setDimensions(const int pW, const int pH);
	void setPosition(const int pX, const int pY);

	void render(SDL_Renderer* pRenderer) const {
		SDL_RenderCopy(pRenderer, m_texture, NULL, &m_rect);
	}

	inline SDL_Rect getRect()  const { return m_rect; }
	inline int GetPositionX()  const { return m_PosX; }
	inline int GetPositionY()  const { return m_PosY; }
	inline int GetDimensionW() const { return m_W; }
	inline int GetDimensionH() const { return m_H; }


private:
	SDL_Texture* m_texture{ nullptr };
	SDL_Rect m_rect;
	int m_PosX, m_PosY, m_W, m_H;
};

