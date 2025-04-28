#include "App.h"

App::App(int pFlags, std::string pNameOfWindow, const int pX, const int pY, const int pW, const int pH)
	: m_r{ 0 }, m_g{ 0 }, m_b{ 0 }, m_a{ SDL_ALPHA_OPAQUE },
	m_delay{ 16 },
	m_isRunning{ SDL_TRUE },
	m_windowW{ pW },
	m_windowH{ pH }
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		LOG("Couldn't initialize SDL video / audio: " + std::string(SDL_GetError()));
	if (IMG_Init(IMG_INIT_PNG) == 0)
		LOG("Couldn't initialize PNG support: " + std::string(SDL_GetError()));
	if (IMG_Init(IMG_INIT_JPG) == 0)
		LOG("Couldn't initialize JPG support: " + std::string(SDL_GetError()));

	m_window = SDL_CreateWindow(pNameOfWindow.c_str(), pX, pY, pW, pH, pFlags);
	if (!m_window)
		LOG("Couldn't create window: " + std::string(SDL_GetError()));

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (!m_renderer)
		LOG("Couldn't create renderer: " + std::string(SDL_GetError()));
}

void App::setDimensionOfWindow(const int pW, const int pH)
{
	SDL_SetWindowSize(m_window, pW, pH);
}

void App::setPositionOfWindow(const int pX, const int pY)
{
	SDL_SetWindowPosition(m_window, pX, pY);
}

void App::setRgbOfWindow(uint8_t pR, uint8_t pG, uint8_t pB, uint8_t pA)
{
	m_r = pR;
	m_g = pG;
	m_b = pB;
	m_a = pA;
}

void App::setDelay(int pDelay)
{
	m_delay = pDelay;
}

void App::setActions(Type pType, std::function<void(void)> pFunc)
{
	auto it = m_mapOfFunc.find(pType);
	if (it == m_mapOfFunc.end())
		m_mapOfFunc[pType] = nullptr;
	m_mapOfFunc[pType] = pFunc;
}

void App::startLoop()
{
	m_mapOfFunc[Type::LOOPBACK]();
	while (m_isRunning) {
		Uint32 start = SDL_GetTicks();

		SDL_GetMouseState(&m_mouseX, &m_mouseY);

		m_mapOfFunc[Type::ACTIONS]();

		SDL_SetRenderDrawColor(m_renderer, m_r, m_g, m_b, m_a);
		SDL_RenderClear(m_renderer);

		m_mapOfFunc[Type::OUTRO]();

		SDL_RenderPresent(m_renderer);

		Uint32 elapsedTime = SDL_GetTicks() - start;
		if (elapsedTime < static_cast<Uint32>(m_delay))
			SDL_Delay(m_delay - elapsedTime);
		else
			SDL_Delay(m_delay);
	}
}

void App::stopLoop()
{
	m_isRunning = SDL_FALSE;
}
