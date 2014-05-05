/* Space Marine - Edsel Apostol, Copyright 2013 */

#include "spm_bitmap_font.h"
#include "spm_surface.h"
#include "spm_camera.h"
#include "vector2f.h"

BitmapFont BitmapFont::GameFont;

BitmapFont::BitmapFont() 
{
	m_TilesX = 0;
	m_TilesY = 0;
	m_pSurface = NULL;
}

void BitmapFont::Load(char* filename, int tilesX, int tilesY)
{
	m_TilesX = tilesX;
	m_TilesY = tilesY;
	m_pSurface = Surface::OnLoad(filename);
	m_Width = m_pSurface->w / tilesX;
	m_Height = m_pSurface->h / tilesY;
	for (int x = 0; x < tilesX; ++x) {
		for (int y = 0; y < tilesY; ++y) {
			SDL_Rect& rect = m_RectsA[GetRectIdx(x, y)];
			rect.x = (x * m_Width);
			rect.y = (y * m_Height);
			rect.w = m_Width;
			rect.h = m_Height;
		}
	}
}

void BitmapFont::RenderString(SDL_Surface* screen, std::string str, int x, int y) 
{
	SDL_Rect location; 
	for (int i = 0; i < str.size(); ++i) {
		SDL_Rect* clip = &m_RectsA[str[i]];
		location.x = x + (i * m_Width);
		location.y = y;
		location.w = m_Width;
		location.h = m_Height;
		Surface::OnDraw(m_pSurface, clip, screen, &location);
	}
}

int BitmapFont::GetRectIdx(int x, int y) const
{
	return ((y * m_TilesX) + x);
}