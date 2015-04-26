/* Space Marine - Edsel Apostol, Copyright 2013 */

#pragma once

class Timer
{
public:
    Timer();
    void Start();
    void Stop();
    void Pause();
    void Unpause();

    double GetTicks();
    bool IsStarted();
    bool IsPaused();
private:
    double m_StartTicks;
    double m_PausedTicks;
    bool m_Paused;
    bool m_Started;
};
