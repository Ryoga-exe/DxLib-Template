#include "Input.h"

bool input::Update(bool drawKeyCodeFlag) {
    $(Keyboard)->Update(drawKeyCodeFlag);
    $(Mouse)->Update();
    return false;
}