#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "FactoryOfRect.h"

#include "SDL.h"
#include "SDL2_gfxPrimitives.h"

class ActionsWithRectangle
{
public:
	ActionsWithRectangle() = default;
	~ActionsWithRectangle() = default;

	SDL_bool isColliding(SDL_Rect pFromRect, SDL_Rect pToRect);
	void movingCircle(SDL_Renderer* pRenderer, FactoryOfRect& pCircle,
					  FactoryOfRect& pGameZone, bool& movingUp, bool& movingRight,
					  bool& isPlaying, int& pSpeedOfBall, bool glow);

	void setPosX(int pPosX) { m_posX = pPosX; }
	void setPosY(int pPosY) { m_posY = pPosY; }

private:
	SDL_Rect m_firstRect;
	SDL_Rect m_secondRect;
	int m_posX{ 1280 / 2 };
	int m_posY{ 720 / 2 };
}; 



