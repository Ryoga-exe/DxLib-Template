#pragma once
#include "DxLib.h"

int  operator""_sec(const long double second);
int  operator""_min(const long double minute);
int  operator""_hr(const long double hour);

class Timer {
public:
    Timer();
    void Start();
    int  Elapse();
    int  GetStartTime() { return m_startTime; }
    bool Pause();
    bool Resume();
    bool TogglePause();

private:
    int  m_startTime, m_pausedTime;
    bool m_isPaused;
};