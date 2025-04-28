#include <iostream>
#include <memory>

#include "Handler.h"
#include "App.h"
#include "Sounds.h"

int main(int argc, char* argv[]) {
	App* app = new App(SDL_WINDOW_SHOWN, "Pong", 100, 100, 1280, 750);
	Handler handler(app);
	Sounds sounds;
	
	std::filesystem::path path = app->getPath() / "music and sounds" / "01. The Journey Begins.mp3";
	if (!std::filesystem::exists(path))
		LOG("Path doesnt exist!");
	else
	{
		sounds.appendMusic(path);
		sounds.playMusic();
		sounds.setVolumeMusic(1);
	}
	
	app->setDelay(16);
	app->setActions(Type::LOOPBACK, [&handler] { handler.loopBack();      });
	app->setActions(Type::ACTIONS,  [&handler] { handler.handleActions(); });
	app->setActions(Type::OUTRO,    [&handler] { handler.handleOutro();   });
	app->startLoop();

	delete app;
	return 0;
}
