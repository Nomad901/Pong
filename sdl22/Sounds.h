#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_mixer.h>
#include <filesystem>

class Sounds
{
public:
	Sounds() = default;
	Sounds(std::string pPathMusic, std::string pPathSound);
	~Sounds();

	void setVolumeSound(int pVolume);
	void setVolumeMusic(int pVolume);

	void appendMusic(const std::filesystem::path& pPath);
	void appendSound(const std::filesystem::path& pPath);

	void playMusic();
	void playChunk();

	void stopPlayingMusic();

private:
	Mix_Chunk* m_Chunk;
	Mix_Music* m_Music;

};

