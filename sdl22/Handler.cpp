#include "Handler.h"

Handler::Handler(App* app)
{
	nsApp = app;
	nsFonts.reserve(3);
	relPathForFonts = PATH::current_path();
}

void Handler::handleActions()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			nsApp->stopLoop();
		}
		if (event.type == SDL_MOUSEWHEEL) {
			if (event.wheel.y > 0)
				speedOfBlocks++;
			if (event.wheel.y < 0)
				speedOfBlocks--;
		}

		const Uint8* keystate = SDL_GetKeyboardState(nullptr);
		if (event.type == SDL_KEYDOWN) {
			if (play == 1) {
				if (keystate[SDL_SCANCODE_W] && yWS > 0) yWS -= speedOfBlocks;
				if (keystate[SDL_SCANCODE_S] && yWS < 500) yWS += speedOfBlocks;
				if (keystate[SDL_SCANCODE_UP] && yArrowUP_DOWN > 0) yArrowUP_DOWN -= speedOfBlocks;
				if (keystate[SDL_SCANCODE_DOWN] && yArrowUP_DOWN < 501) yArrowUP_DOWN += speedOfBlocks;
			}
			if (keystate[SDL_SCANCODE_P]) play = !(play);
			if (keystate[SDL_SCANCODE_U]) speedOfBall += 1;
			if (keystate[SDL_SCANCODE_D]) speedOfBall -= 1;
		}
	}
}

void Handler::handleOutro()
{
	nsGameZone->render(nsApp->getRenderer());

	gameRender();
	
	// speed will be getting bigger while game is running
	if (scoreForSpeed % 6 == 0) {
		speedOfBall++;
		scoreForSpeed++;
	}

	nsFirstRect->render(nsApp->getRenderer());
	nsFirstRect->setPosition(85 / 2 + (85 / 5), yWS);

	nsSecondRect->render(nsApp->getRenderer());
	nsSecondRect->setPosition(static_cast<const int>(nsApp->getWindowsWidth() / 2 + (nsApp->getWindowsWidth() / 2.4) - 15),
		yArrowUP_DOWN);

	if (!play)
		nsFonts[0]->render(nsApp->getRenderer());
}

void Handler::loopBack() {
	setRectangles();
	setFonts();
}

void Handler::gameRender()
{
	if (!play) {
		nsCircle->render(nsApp->getRenderer());
		nsCircle->setPosition(1280 / 2, 720 / 2);
		filledCircleColor(nsApp->getRenderer(), 1280 / 2, 720 / 2, 20, 0xFFFFFFFF);
		nsActions.setPosX(1280 / 2);
		nsActions.setPosY(720 / 2);
	}
	else
	{
		nsCircle->render(nsApp->getRenderer());

		static bool up = false;
		static bool side = true; // true - right,  false - left

		nsActions.movingCircle(nsApp->getRenderer(), *nsCircle, *nsGameZone, up, side, play, speedOfBall);

		if (nsActions.isColliding(nsFirstRect->getRect(), nsCircle->getRect())) {
			if (side == false)
			{
				nsFonts[1]->changeText(nsApp->getRenderer(), "SCORE: " + std::to_string(scoreOfLeft += 1));
				scoreForSpeed++;
			}
			side = true;
		}
		if (nsActions.isColliding(nsSecondRect->getRect(), nsCircle->getRect())) {
			if (side == true)
			{
				nsFonts[2]->changeText(nsApp->getRenderer(), "SCORE: " + std::to_string(scoreOfRight += 1));
				scoreForSpeed++;
			}
			side = false;
		}
		nsFonts[1]->render(nsApp->getRenderer());
		nsFonts[2]->render(nsApp->getRenderer());
	}
}
void Handler::setRectangles()
{
	nsGameZone = std::make_unique<FactoryOfRect>(nsApp->getRenderer());
	nsGameZone->setPosition(50, 0);
	nsGameZone->setDimensions(1200, 750);

	nsFirstRect = std::make_unique<FactoryOfRect>(nsApp->getRenderer(), 255, 255, 255, 255);
	nsFirstRect->setDimensions(50, 250);

	nsSecondRect = std::make_unique<FactoryOfRect>(nsApp->getRenderer(), 255, 255, 255, 255);
	nsSecondRect->setDimensions(50, 250);

	nsCircle = std::make_unique<FactoryOfRect>(nsApp->getRenderer());
	nsCircle->setPosition(1280 - 20, 720 - 3);
	nsCircle->setDimensions(10, 10);
}
void Handler::setFonts()
{
	SDL_Color white{ 255,255,255,255 };
	nsFonts.emplace_back(std::make_unique<FactoryOfFront>(nsApp->getRenderer(), "PRESS P TO PLAY!",
		white, 30, relPathForFonts / "photos and ttf" / "Arial.ttf"));
	nsEmptyEntities[0] = std::make_unique<FactoryOfRect>(nsApp->getRenderer());
	nsEmptyEntities[0]->setPosition(nsApp->getWindowsWidth() / 2 - 50, nsApp->getWindowsHeight() / 2 - 200);
	nsFonts[0]->fontIntoRect(nsEmptyEntities[0]->getRect());

	nsFonts.emplace_back(std::make_unique<FactoryOfFront>(nsApp->getRenderer(), "SCORE: " + std::to_string(scoreOfLeft),
		white, 30, relPathForFonts / "photos and ttf" / "Arial.ttf"));
	nsEmptyEntities[1] = std::make_unique<FactoryOfRect>(nsApp->getRenderer());
	nsEmptyEntities[1]->setPosition(200, 10);
	nsFonts[1]->fontIntoRect(nsEmptyEntities[1]->getRect());

	nsFonts.emplace_back(std::make_unique<FactoryOfFront>(nsApp->getRenderer(), "SCORE: " + std::to_string(scoreOfRight),
		white, 30, relPathForFonts / "photos and ttf" / "Arial.ttf"));
	nsEmptyEntities[2] = std::make_unique<FactoryOfRect>(nsApp->getRenderer());
	nsEmptyEntities[2]->setPosition(1000, 10);
	nsFonts[2]->fontIntoRect(nsEmptyEntities[2]->getRect());
}

