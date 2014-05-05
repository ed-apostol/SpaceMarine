/* Space Marine - Edsel Apostol, Copyright 2013 */

#pragma once

#include "SDL_mixer.h"
#include <vector>

class SoundFX
{
public:
	static enum {
		SND_BG = 0,
		SND_HIT,
		SND_MAX
	};
	SoundFX();
	~SoundFX();
	void Load(char* file);
	void Play(int ch, int loops);
	static SoundFX* GameSoundsList;
private:
	Mix_Chunk* m_pSound;
};