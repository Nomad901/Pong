#include "FactoryOfRect.h"

FactoryOfRect::FactoryOfRect(SDL_Renderer* pRenderer)
{
	SDL_Surface* surface = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, SDL_ALPHA_OPAQUE);
	m_texture = SDL_CreateTextureFromSurface(pRenderer, surface);
	SDL_FreeSurface(surface);
	m_rect = { 0, 0, 100, 100 };
	m_PosX = 0; m_PosY = 0;
	m_W = 100; m_H = 100;
}

FactoryOfRect::FactoryOfRect(SDL_Renderer* pRenderer, uint8_t pR, uint8_t pG, uint8_t pB, uint8_t pA)
{
	m_rect = { 0, 0, 100, 100 };
	SDL_Surface* surface = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_FillRect(surface, nullptr, SDL_MapRGBA(surface->format, pR, pG, pB, pA));
	m_texture = SDL_CreateTextureFromSurface(pRenderer, surface);
	SDL_FreeSurface(surface);
	m_PosX = 0; m_PosY = 0;
	m_W = 100; m_H = 100;
}

FactoryOfRect::FactoryOfRect(SDL_Renderer* pRenderer, std::filesystem::path& pPath)
{
	SDL_Surface* surface = IMG_Load(pPath.string().c_str());
	m_texture = SDL_CreateTextureFromSurface(pRenderer, surface);
	SDL_FreeSurface(surface);
	m_rect = { 0, 0, 100, 100 };
	m_PosX = 0; m_PosY = 0;
	m_W = 100; m_H = 100;
}

void FactoryOfRect::setDimensions(const int pW, const int pH)
{
	m_rect.w = pW; m_W = pW;
	m_rect.h = pH; m_H = pH;
}

void FactoryOfRect::setPosition(const int pX, const int pY)
{
	m_rect.x = pX; m_PosX = pX;
	m_rect.y = pY; m_PosY = pY;
}
