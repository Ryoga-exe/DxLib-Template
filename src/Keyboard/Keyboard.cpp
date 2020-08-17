#include "Keyboard.h"
#include "DxLib.h"

Keyboard::Keyboard() {
    memset(m_keyPressingCount, 0, sizeof(m_keyPressingCount));
    memset(m_keyReleasingCount, 0, sizeof(m_keyReleasingCount));
}

bool Keyboard::Update(bool doDrawKeyCode) {
    char nowKeyStatus[KEY_NUM];
    int counting = 0;
    DxLib::GetHitKeyStateAll(nowKeyStatus);
    for (int i = 0; i < KEY_NUM; i++) {
        if (nowKeyStatus[i] != 0) {
            if (m_keyReleasingCount[i] > 0) {
                m_keyReleasingCount[i] = 0;
            }
            m_keyPressingCount[i]++;
            if (doDrawKeyCode) {
                DxLib::DrawFormatString(0, 16 * counting, 0xffffff, u8"%d", i);
                counting++;
            }
        }
        else {
            if (m_keyPressingCount[i] > 0) {
                m_keyPressingCount[i] = 0;
            }
            m_keyReleasingCount[i]++;
        }
    }
    return true;
}

int Keyboard::GetPressingCount(int keyCode) {
    if (!Keyboard::IsAvailableCode(keyCode)) return -1;
    return m_keyPressingCount[keyCode];
}

int Keyboard::GetReleasingCount(int keyCode) {
    if (!Keyboard::IsAvailableCode(keyCode)) return -1;
    return m_keyReleasingCount[keyCode];
}

Keyboard::State Keyboard::GetStatus(int keyCode) {
    if (!Keyboard::IsAvailableCode(keyCode)) return State::None;
    if (Keyboard::GetPressingCount(keyCode) == 1) return State::Pressed;
    if (Keyboard::GetPressingCount(keyCode) > 1) return State::Held;
    if (Keyboard::GetReleasingCount(keyCode) == 1) State::Released;
    return State::None;
}

bool Keyboard::IsAvailableCode(int keyCode) {
    if (!(0 <= keyCode && keyCode < KEY_NUM)) return false;
    return true;
}