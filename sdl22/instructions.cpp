#include "instructions.h"

void Instructions::init(SDL_Renderer* pRenderer)
{
	path = std::filesystem::current_path();

	auto createAll = [&](int size, SDL_Color& color, std::vector<std::string> text)
		{
			labels.clear(); rects.clear();
			labels.reserve(text.size());
			rects.reserve(text.size());
			
			int position = 10;  
			for (const auto& str : text) {
				labels.emplace_back(std::make_unique<FactoryOfFront>(
					pRenderer, str, color, size,
					path / "photos and ttf" / "Arial.ttf"));

				rects.emplace_back(std::make_unique<FactoryOfRect>(pRenderer));
				rects.back()->setPosition(1280 / 2, position);
				position += 30;
			}
		};

	SDL_Color white = { 255,255,255,255 };
	createAll(24, white,
		{ "Press U in order to increase speed of your ball. Press D in order to slow down the ball" ,
		  "Wheel up - increase speed of the platforms. Wheel down - decrease speed of the platforms" ,
		  "Press R in order to reset scores/speed" ,
		  "Press C in order to color your ball in full white and vice versa." });
}

void Instructions::render(SDL_Renderer* pRenderer)
{
	if (!labels.empty() && !rects.empty())
	{
		for (size_t i = 0; i < labels.size() - 1; ++i)
		{
			labels[i]->fontIntoRect(rects[i]->getRect());
			labels[i]->render(pRenderer);
		}
	}
}
