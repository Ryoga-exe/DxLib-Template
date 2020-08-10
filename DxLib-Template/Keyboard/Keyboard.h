#pragma once
#include "../Singleton/Singleton.h"

#define KEY(i) KEY_INPUT_ ## i

class Keyboard : public Singleton<Keyboard> {
    Keyboard();
    friend Singleton< Keyboard >;

public:
    enum class State {
        None,
        Pressed,
        Released,
        Held
    };

    bool Update(bool doDrawKeyCode = false);
    int  GetPressingCount(int keyCode);
    int  GetReleasingCount(int keyCode);
    State  GetStatus(int keyCode);

private:
    bool IsAvailableCode(int keyCode);

    static constexpr int KEY_NUM = 256;
    int m_keyPressingCount[KEY_NUM];
    int m_keyReleasingCount[KEY_NUM];
};