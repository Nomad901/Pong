#include "Sounds.h"

Sounds::Sounds(std::string pPathMusic, std::string pPathSound)
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	m_Music = Mix_LoadMUS(pPathMusic.c_str());
	m_Chunk = Mix_LoadWAV(pPathSound.c_str());
}

Sounds::~Sounds()
{
	Mix_FreeMusic(m_Music);
	Mix_FreeChunk(m_Chunk);
	Mix_CloseAudio();
}

void Sounds::setVolumeSound(int pVolume)
{
	Mix_VolumeChunk(m_Chunk, pVolume);
}

void Sounds::setVolumeMusic(int pVolume)
{
	Mix_VolumeMusic(pVolume);
}

void Sounds::appendMusic(const std::filesystem::path& pPath)
{
	m_Music = Mix_LoadMUS(pPath.string().c_str());
}

void Sounds::appendSound(const std::filesystem::path& pPath)
{
	m_Chunk = Mix_LoadWAV(pPath.string().c_str());
}

void Sounds::playMusic()
{
	Mix_PlayMusic(m_Music, -1);
}

void Sounds::playChunk()
{
	Mix_PlayChannel(-1, m_Chunk, 0);
}

void Sounds::stopPlayingMusic()
{
	Mix_PlayMusic(m_Music, 0);
}
