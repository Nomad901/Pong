#pragma once
#include <iostream>
#include <memory>
#include <array>
#include <vector>
#include <utility>
#include <filesystem>

#include <SDL.h>

#include "FactoryOfFront.h"
#include "FactoryOfRect.h"
#include "App.h"
#include "Sounds.h"
#include "ActionsWithRectangle.h"

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
	std::vector<std::unique_ptr<FactoryOfFront>> nsFonts;
	std::array<std::unique_ptr<FactoryOfRect>, 3> nsEmptyEntities;
	ActionsWithRectangle nsActions;

	PATH::path relPathForFonts;

	int yWS{ 0 };
	int yArrowUP_DOWN{ 500 };
	
	int speedOfBlocks{ 8 };
	int speedOfBall{ 4 };
	
	int scoreOfLeft{ 0 };
	int scoreOfRight{ 0 };
	int scoreForSpeed{ 0 };
	
	int counterTimes{ 0 };
	
	bool play{ 0 };
};

