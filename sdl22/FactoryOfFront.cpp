#include "FactoryOfFront.h"

FactoryOfFront::FactoryOfFront(SDL_Renderer* pRenderer, std::string pText, SDL_Color& pColor, int pSize, std::filesystem::path pPath)
{
	if (TTF_Init() == -1)
		LOG("Couldnt initialize TTF: " + std::string(TTF_GetError()));

	m_Font = TTF_OpenFont(pPath.string().c_str(), pSize);
	if (!m_Font)
		LOG("Couldnt itialize the path or the font: " + std::string(TTF_GetError()));

	this->m_Text = pText;
	m_Color = pColor;

	SDL_Surface* surface = TTF_RenderText_Solid(m_Font, m_Text.c_str(), m_Color);
	if (!surface)
		LOG("Couldnt initialize the surface: " + std::string(TTF_GetError()));

	m_Texture = SDL_CreateTextureFromSurface(pRenderer, surface);
	if (!m_Texture)
		LOG("Problem is texture: " + std::string(SDL_GetError()));

	SDL_FreeSurface(surface);
}

void FactoryOfFront::changeText(SDL_Renderer* pRenderer, std::string pText)
{
	SDL_Surface* surface = TTF_RenderText_Solid(m_Font, pText.c_str(), m_Color);
	m_Texture = SDL_CreateTextureFromSurface(pRenderer, surface);
	SDL_FreeSurface(surface);
}

void FactoryOfFront::fontIntoRect(SDL_Rect pRect)
{
	int textWidth, textHeight;
	TTF_SizeText(m_Font, m_Text.c_str(), &textWidth, &textHeight);
	m_Rect = { pRect.x + (pRect.w - textWidth) / 2, pRect.y + (pRect.h - textHeight) / 2, textWidth, textHeight };
}
