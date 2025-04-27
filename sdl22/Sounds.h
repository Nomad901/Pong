#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_mixer.h>

class Sounds
{
public:
	Sounds(std::string pPathMusic, std::string pPathSound);
	~Sounds();

	void setVolumeSound(int pVolume);
	void setVolumeMusic(int pVolume);

	void playMusic();
	void playChunk();

	void stopPlayingMusic();

private:
	Mix_Chunk* m_Chunk;
	Mix_Music* m_Music;

};

