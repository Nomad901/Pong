#include "ActionsWithRectangle.h"

SDL_bool ActionsWithRectangle::isColliding(SDL_Rect pFromRect, SDL_Rect pToRect)
{
	return SDL_HasIntersection(&pFromRect, &pToRect);
}

void ActionsWithRectangle::movingCircle(SDL_Renderer* pRenderer, FactoryOfRect& pCircle,
										FactoryOfRect& pGameZone, bool& movingUp, bool& movingRight, 
										bool& isPlaying, int& pSpeedOfBall)
{
	const int radius = 20;
	const int speed = pSpeedOfBall;

	if (movingRight) {
		if (!movingUp) {
			m_posX += speed;
			m_posY += speed;
		}
		else {
			m_posX += speed;
			m_posY -= speed;
		}
	}
	else {
		if (movingUp) {
			m_posX -= speed;
			m_posY -= speed;
		}
		else {
			m_posX -= speed;
			m_posY += speed;
		}
	}

	pCircle.setPosition(m_posX, m_posY);
	circleRGBA(pRenderer, m_posX, m_posY, radius+5, 255, 255, 255, 255);
	
	if (m_posY <= 0) movingUp = false;
	if (m_posY >= pGameZone.GetDimensionH()) movingUp = true;

	if (m_posX <= 50 || m_posX >= pGameZone.GetDimensionW() + 5)
		isPlaying = false;
}


