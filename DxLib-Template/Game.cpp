#include "Game.h"

bool Game::Initialize(const TCHAR* windowTitle) {
    $(DxSystem)->SetWindowSize({ 1280, 720 });
    if ($(DxSystem)->Initialize(windowTitle)) return true;
    return false;
}
bool Game::Finalize() {
    $(DxSystem)->Finalize();
    return false;
}
void Game::ProcessLoop() {
    while (SystemUpdate()) {
        Update();
        Draw();
    }
}

bool Game::SystemUpdate() {
    $(DxSystem)->Update();
    input::Update();
    return (!DxLib::ScreenFlip() && !DxLib::ProcessMessage() && !DxLib::ClearDrawScreen());
}
bool Game::Update() {
    return false;
}
void Game::Draw() {
}