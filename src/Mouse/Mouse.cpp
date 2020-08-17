#include "Mouse.h"
#include "DxLib.h"
#include <math.h>

Mouse::Mouse() : m_buttonPressingCount(), m_buttonReleasingCount(), m_x(), m_y() {
}

bool Mouse::Update() {
    int nowButtonState = DxLib::GetMouseInput();
    DxLib::GetMousePoint(&m_x, &m_y);
    for (int i = 0; i < KEY_NUM; i++) {
        if ((nowButtonState >> i) & 1) {
            if (m_buttonReleasingCount[i] > 0) {
                m_buttonReleasingCount[i] = 0;
            }
            m_buttonPressingCount[i]++;
        }
        else {
            if (m_buttonPressingCount[i] > 0) {
                m_buttonPressingCount[i] = 0;
            }
            m_buttonReleasingCount[i]++;
        }
    }
    return true;
}

int Mouse::GetPressingCount(int keyCode) {
    if (!isAvailableCode(keyCode)) {
        return -1;
    }
    return m_buttonPressingCount[keyCode];
}

int Mouse::GetReleasingCount(int keyCode) {
    if (!isAvailableCode(keyCode)) {
        return -1;
    }
    return m_buttonReleasingCount[keyCode];
}

bool Mouse::IsMouseHoverRect(int x1, int y1, int x2, int y2) {
    int _x1 = x1, _y1 = y1, _x2 = x2, _y2 = y2;
    if (x1 > x2) {
        _x1 = x2;
        _x2 = x1;
    }
    if (y1 > y2) {
        _y1 = y2;
        _y2 = y1;
    }
    if (_x1 < m_x && _x2 > m_x && _y1 < m_y && _y2 > m_y) {
        return true;
    }
    return false;
}

bool Mouse::IsMouseHoverCircle(int x, int y, int r) {
    if (r > sqrt(pow(m_x - x, 2) + pow(m_y - y, 2))) {
        return true;
    }
    return false;
}

bool Mouse::isAvailableCode(int keyCode) {
    if (!(0 <= keyCode && keyCode < KEY_NUM)) {
        return false;
    }
    return true;
}