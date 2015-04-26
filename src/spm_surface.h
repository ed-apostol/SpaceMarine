/* Space Marine - Edsel Apostol, Copyright 2013 */

#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Surface
{
public:
    Surface();
    static SDL_Surface* OnLoad(char* File);
    static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H);
    static bool OnDraw(SDL_Surface* Surf_Src, SDL_Rect* clip, SDL_Surface* Surf_Dest, SDL_Rect* location);
};
