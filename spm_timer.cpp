/* Space Marine - Edsel Apostol, Copyright 2013 */

#include "spm_timer.h"
#include "SDL.h"

Timer::Timer()
{
    m_StartTicks = 0;
    m_PausedTicks = 0;
    m_Paused = false;
    m_Started = false;
}

void Timer::Start()
{
    m_Started = true;
    m_Paused = false;
    m_StartTicks = (double)SDL_GetTicks();
}

void Timer::Stop()
{
    m_Started = false;
    m_Paused = false;
}

void Timer::Pause()
{
    if( ( m_Started == true ) && ( m_Paused == false ) ) {
        m_Paused = true;
        m_PausedTicks = (double)SDL_GetTicks() - m_StartTicks;
    }
}

void Timer::Unpause()
{
    if( m_Paused == true ) {
        m_Paused = false;
        m_StartTicks = (double)SDL_GetTicks() - m_PausedTicks;
        m_PausedTicks = 0;
    }
}

double Timer::GetTicks()
{
    if( m_Started == true ) {
        if( m_Paused == true ) {
            return m_PausedTicks;
        } else {
            return (double)SDL_GetTicks() - m_StartTicks;
        }
    }
    return 0;
}

bool Timer::IsStarted()
{
    return m_Started;
}

bool Timer::IsPaused()
{
    return m_Paused;
}
