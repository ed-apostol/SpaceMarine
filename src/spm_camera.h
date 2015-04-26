/* Space Marine - Edsel Apostol, Copyright 2013 */

#pragma once

#include "SDL.h"
#include "spm_defines.h"
#include "vector2f.h"

class Camera
{
public:
    Camera();
    void Update(const Vector2f& pos);
    SDL_Rect m_Rect;
    static Camera GameCam;
};

