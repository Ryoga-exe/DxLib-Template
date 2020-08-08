#pragma once
#include "Keyboard/Keyboard.h"
#include "Mouse/Mouse.h"

namespace input {
    bool Update(bool drawKeyCodeFlag) {
        Keyboard::Inst()->Update(drawKeyCodeFlag);
        Mouse::Inst()->Update();
        return false;
    }
}