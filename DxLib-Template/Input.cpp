#include "Input.h"

bool input::Update(bool drawKeyCodeFlag) {
    Keyboard::Inst()->Update(drawKeyCodeFlag);
    Mouse::Inst()->Update();
    return false;
}