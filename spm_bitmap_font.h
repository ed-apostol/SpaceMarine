/* Space Marine - Edsel Apostol, Copyright 2013 */

#pragma once

#include "SDL.h"
#include <string>

class BitmapFont
{
public:
	BitmapFont();
	void Load(char* filename, int tilesX, int tilesY);
	void RenderString(SDL_Surface* screen, std::string str, int x, int y);
	static BitmapFont GameFont;
private:
	int m_TilesX;
	int m_TilesY;
	int m_Width;
	int m_Height;
	int GetRectIdx(int x, int y) const;
	SDL_Surface* m_pSurface;
	SDL_Rect m_RectsA[256];
};
