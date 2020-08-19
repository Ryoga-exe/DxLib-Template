#pragma once
#include "DxLib.h"

int  operator""_sec(const long double second);

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