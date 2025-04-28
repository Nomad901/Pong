#pragma once
#include <iostream>
#include <memory>
#include <array>
#include <vector>
#include <utility>
#include <filesystem>
#include <chrono>
#include <thread>

#include <SDL.h>

#include "FactoryOfFront.h"
#include "FactoryOfRect.h"
#include "App.h"
#include "Sounds.h"
#include "ActionsWithRectangle.h"
#include "instructions.h"

#define PATH std::filesystem

class Handler
{
public:
	Handler(App* app);
	~Handler() { delete nsApp; }

	void handleOutro();
	void handleActions();
	void loopBack();

private:
	void setRectangles();
	void setFonts();
	void gameRender();

	App* nsApp;
	std::unique_ptr<FactoryOfRect> nsGameZone, nsFirstRect, nsSecondRect, nsCircle;
	std::unique_ptr<Sounds> nsSounds;
	std::array<std::unique_ptr<FactoryOfFront>, 5> nsFonts;
	std::array<std::unique_ptr<FactoryOfRect>, 5> nsEmptyEntities;
	ActionsWithRectangle nsActions;
	Instructions nsInstructions;
	Sounds sounds;

	PATH::path relPathForFonts;

	int yWS{ 0 };
	int yArrowUP_DOWN{ 500 };
	
	int speedOfBlocks{ 8 };
	int speedOfBall{ 4 };
	
	int scoreOfLeft{ 0 };
	int scoreOfRight{ 0 };
	int scoreForSpeed{ 0 };
	
	int counterTimes{ 0 };

	int counterForTimer{ 3 };

	bool play{ false };
	bool anotherWindow{ false };
	bool glow{ true };
};

