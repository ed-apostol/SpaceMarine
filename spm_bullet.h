/* Space Marine - Edsel Apostol, Copyright 2013 */

#pragma once

#include "spm_entity.h"

class Bullet : public Entity
{
public:
    Bullet();
	Bullet(const Bullet& bullet);
    void Load(char* filename, int tilesX, int tilesY, int numframe, double frameRate);
    void Update(double m_DeltaTime);
    void Render(SDL_Surface* m_pScreen);
};
