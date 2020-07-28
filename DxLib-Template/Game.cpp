#include "Game.h"

bool Game::Initialize(const TCHAR* windowTitle) {
    if (m_system.Initialize(windowTitle)) return true;
    return false;
}
bool Game::Finalize() {
    m_system.Finalize();
    return false;
}
void Game::ProcessLoop() {
    while (SystemUpdate()) {
        Update();
        Draw();
        DxLib::DrawFormatString(0, 0, 0xffffff, L"%d", m_system.GetWindowSize().width);

        if (GetInputChar(TRUE) == ' ') {
            m_system.ToggleFullscreenMode();
        }
    }
}

bool Game::SystemUpdate() {
    return (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen());
}
bool Game::Update() {
    return false;
}
void Game::Draw() {
    
}