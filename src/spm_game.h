/* Space Marine - Edsel Apostol, Copyright 2013 */

#pragma once

#include "spm_entity.h"
#include "spm_timer.h"
#include "spm_player.h"
#include "SDL_mixer.h"

class Game
{
public:
    Game();
    ~Game();

    int Run();

    void HandleInput();
    void Update();
    void Render();
    void UpdateCamera(const Vector2f& pos);
    void DisplayFPS();
    void LimitFPS();

private:
    Uint32 m_ScreenFlags;
    Uint32 m_Frame;

    bool m_quit;

    double m_DeltaTime;
    Timer m_LoopTime;
    Timer m_Fps;
    Timer m_FpsCap;

    SDL_Surface* m_pScreen;
    SDL_Surface* m_pBackground;
    SDL_Event m_Event;
};
