/* Space Marine - Edsel Apostol, Copyright 2013 */

#pragma once

#include "spm_entity.h"

class Static : public Entity
{
public:
    Static();
	void Load(char* filename, int tilesX, int tilesY, int numframe, double frameRate);
};
