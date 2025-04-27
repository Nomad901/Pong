#include <iostream>
#include <memory>

#include "Handler.h"
#include "App.h"

int main(int argc, char* argv[]) {
	App* app = new App(SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, "Pong", 100, 100, 1280, 750);
	Handler handler(app);

	app->setDelay(16);
	app->setActions(Type::LOOPBACK, [&handler] { handler.loopBack();      });
	app->setActions(Type::ACTIONS,  [&handler] { handler.handleActions(); });
	app->setActions(Type::OUTRO,    [&handler] { handler.handleOutro();   });
	app->startLoop();

	delete app;
	return 0;
}

/*
TODO: 
	1. when game is running - make speed of ball and of platformes a little bit faster
	2. create kinda second window, where an user can find an information abt hot keys
	3. in this window implement: increasing speed, turn on/off - scores/showing speed of smth, invisible nsCircle(lines) or filled nsCircle 
	
	SPECIAL:
	i wanna create another window where an user can look at instructions about controling(typeshi u - increate speed of the ball and so on)
	and then when an user will shut the window up he will meet a timer, which will be going 3 seconds, after that game will be resumed


*/