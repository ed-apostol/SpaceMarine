/* Space Marine - Edsel Apostol, Copyright 2013 */

#include "spm_soundfx.h"

SoundFX* SoundFX::GameSoundsList;

SoundFX::SoundFX()
{
	m_pSound = NULL;
}

SoundFX::~SoundFX()
{
	if (m_pSound) Mix_FreeChunk(m_pSound);
}

void SoundFX::Load(char* file)
{
	m_pSound = Mix_LoadWAV(file);	
	if (!m_pSound)
	{
		fprintf(stderr, "SDL_mixer Error: %s\n", Mix_GetError());
		exit(1);
	}
}

void SoundFX::Play(int ch, int loops)
{
	if (Mix_PlayChannel(ch, m_pSound, loops) < 0)
	{
		fprintf(stderr, "SDL_mixer Error: %s\n", Mix_GetError());
	}
}
