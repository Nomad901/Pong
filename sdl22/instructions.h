#pragma once
#include <iostream>
#include <vector>
#include <filesystem>

#include <SDL.h>

#include "FactoryOfFront.h"	
#include "FactoryOfRect.h"
#include "App.h"

class Instructions
{
public:
	void init(SDL_Renderer* pRenderer);
	void render(SDL_Renderer* pRenderer);

private:
	std::vector<std::unique_ptr<FactoryOfFront>> labels;
	std::vector<std::unique_ptr<FactoryOfRect>> rects;
	std::filesystem::path path;
};

