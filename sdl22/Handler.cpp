#include "Handler.h"

Handler::Handler(App* app)
{
	nsApp = app;
	relPathForFonts = PATH::current_path();
	nsInstructions.init(nsApp->getRenderer());

	std::filesystem::path path = app->getPath() / "music and sounds" / "Hit_Hurt2.wav";
	if (!std::filesystem::exists(path))
		LOG("Path doesnt exist!");
	else
	{
		sounds.appendSound(path);
		sounds.setVolumeSound(3);
	}
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
				if (keystate[SDL_SCANCODE_W] && yWS > 0) 
					yWS -= speedOfBlocks;
				if (keystate[SDL_SCANCODE_S] && yWS < 500) 
					yWS += speedOfBlocks;
				if (keystate[SDL_SCANCODE_UP] && yArrowUP_DOWN > 0) 
					yArrowUP_DOWN -= speedOfBlocks;
				if (keystate[SDL_SCANCODE_DOWN] && yArrowUP_DOWN < 501) 
					yArrowUP_DOWN += speedOfBlocks;
			}
			if (keystate[SDL_SCANCODE_P]) 
				play = !(play);
			if (keystate[SDL_SCANCODE_U]) 
				speedOfBall += 1;
			if (keystate[SDL_SCANCODE_D]) 
				speedOfBall -= 1;
			if (keystate[SDL_SCANCODE_I])
			{
				anotherWindow = !anotherWindow;
				if (anotherWindow)
					nsInstructions.init(nsApp->getRenderer());
			}
			if (keystate[SDL_SCANCODE_R])
			{
				speedOfBall = 4; 
				speedOfBlocks = 8;
				scoreForSpeed = 0;
				scoreOfLeft = 0;
				scoreOfRight = 0;
				nsFonts[1]->changeText(nsApp->getRenderer(), "SCORE: " + std::to_string(0));
				nsFonts[2]->changeText(nsApp->getRenderer(), "SCORE: " + std::to_string(0));
			}
			if (keystate[SDL_SCANCODE_C])
				glow = !glow;
		}
	}
}

void Handler::handleOutro()
{
	if (!anotherWindow)
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
		{
			nsFonts[0]->render(nsApp->getRenderer());
			nsEmptyEntities[3]->renderOnlyEdges(nsApp->getRenderer(), 255, 255, 255, 255);
			nsFonts[3]->render(nsApp->getRenderer());
		}
	}
	else
		nsInstructions.render(nsApp->getRenderer());
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
		counterForTimer = 3;
		nsFonts[4]->changeText(nsApp->getRenderer(), std::to_string(counterForTimer));
	}
	else
	{
		Uint32 timer = SDL_GetTicks() + 1000;

		//timer before the game
		while (counterForTimer > 0)
		{
			nsFonts[4]->render(nsApp->getRenderer());
			SDL_RenderPresent(nsApp->getRenderer());
			if (SDL_GetTicks() >= timer)
			{
				SDL_RenderClear(nsApp->getRenderer());
				nsFonts[4]->changeText(nsApp->getRenderer(), std::to_string(counterForTimer-=1));
				timer = SDL_GetTicks() + 1000;
			}
		}
		nsCircle->render(nsApp->getRenderer());

		static bool up = false;
		static bool side = true; // true - right,  false - left

		nsActions.movingCircle(nsApp->getRenderer(), *nsCircle, *nsGameZone, up, side, play, speedOfBall, glow);

		if (nsActions.isColliding(nsFirstRect->getRect(), nsCircle->getRect())) {
			if (side == false)
			{
				sounds.playChunk();
				nsFonts[1]->changeText(nsApp->getRenderer(), "SCORE: " + std::to_string(scoreOfLeft += 1));
				scoreForSpeed++;
			}
			side = true;
		}
		if (nsActions.isColliding(nsSecondRect->getRect(), nsCircle->getRect())) {
			if (side == true)
			{
				sounds.playChunk();
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
	nsFonts[0] = std::make_unique<FactoryOfFront>(nsApp->getRenderer(), "PRESS P TO PLAY!",
												  white, 30, relPathForFonts / "photos and ttf" / "Arial.ttf");
	nsEmptyEntities[0] = std::make_unique<FactoryOfRect>(nsApp->getRenderer());
	nsEmptyEntities[0]->setPosition(nsApp->getWindowsWidth() / 2 - 50, nsApp->getWindowsHeight() / 2 - 200);
	nsFonts[0]->fontIntoRect(nsEmptyEntities[0]->getRect());

	nsFonts[1] = std::make_unique<FactoryOfFront>(nsApp->getRenderer(), "SCORE: " + std::to_string(scoreOfLeft),
											      white, 30, relPathForFonts / "photos and ttf" / "Arial.ttf");
	nsEmptyEntities[1] = std::make_unique<FactoryOfRect>(nsApp->getRenderer());
	nsEmptyEntities[1]->setPosition(200, 10);
	nsFonts[1]->fontIntoRect(nsEmptyEntities[1]->getRect());

	nsFonts[2] = std::make_unique<FactoryOfFront>(nsApp->getRenderer(), "SCORE: " + std::to_string(scoreOfRight),
												 white, 30, relPathForFonts / "photos and ttf" / "Arial.ttf");
	nsEmptyEntities[2] = std::make_unique<FactoryOfRect>(nsApp->getRenderer());
	nsEmptyEntities[2]->setPosition(1000, 10);
	nsFonts[2]->fontIntoRect(nsEmptyEntities[2]->getRect());

	nsFonts[3] = std::make_unique<FactoryOfFront>(nsApp->getRenderer(), "Click on I if you wanna get hot-keys for the game!",
												  white,24, relPathForFonts / "photos and ttf" / "Arial.ttf");
	nsEmptyEntities[3] = std::make_unique<FactoryOfRect>(nsApp->getRenderer());
	nsEmptyEntities[3]->setPosition((1280/3)-60, 650);
	nsEmptyEntities[3]->setDimensions(600, 100);
	nsFonts[3]->fontIntoRect(nsEmptyEntities[3]->getRect());

	nsFonts[4] = std::make_unique<FactoryOfFront>(nsApp->getRenderer(), std::to_string(counterForTimer),
												  white, 30, relPathForFonts / "photos and ttf" / "Arial.ttf");
	nsEmptyEntities[4] = std::make_unique<FactoryOfRect>(nsApp->getRenderer());
	nsEmptyEntities[4]->setPosition(nsApp->getWindowsWidth() / 2 - 50, nsApp->getWindowsHeight() / 2 - 200);
	nsFonts[4]->fontIntoRect(nsEmptyEntities[4]->getRect());

}

