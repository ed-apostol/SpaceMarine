/* Space Marine - Edsel Apostol, Copyright 2013 */

#include "spm_surface.h"

// TODO: rewrite

Surface::Surface()
{
}

SDL_Surface* Surface::OnLoad(char* File)
{
    SDL_Surface* Surf_Temp = NULL;
    SDL_Surface* Surf_Return = NULL;

    if((Surf_Temp = IMG_Load(File)) == NULL) {
        return NULL;
    }

    Surf_Return = SDL_DisplayFormatAlpha(Surf_Temp);
    SDL_FreeSurface(Surf_Temp);

    return Surf_Return;
}

bool Surface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H)
{
    if(Surf_Dest == NULL || Surf_Src == NULL) {
        return false;
    }

    SDL_Rect DestR;

    DestR.x = X;
    DestR.y = Y;

    SDL_Rect SrcR;

    SrcR.x = X2;
    SrcR.y = Y2;
    SrcR.w = W;
    SrcR.h = H;

    SDL_BlitSurface(Surf_Src, &SrcR, Surf_Dest, &DestR);

    return true;
}

bool Surface::OnDraw(SDL_Surface* Surf_Src, SDL_Rect* clip, SDL_Surface* Surf_Dest, SDL_Rect* location)
{
    if(Surf_Dest == NULL || Surf_Src == NULL) {
        return false;
    }

    SDL_BlitSurface(Surf_Src, clip, Surf_Dest, location);

    return true;
}
