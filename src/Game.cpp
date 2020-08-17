#include "Game.h"
#include "Scene/Title.h"

bool Game::Initialize(const TCHAR* windowTitle) {
    $(DxSystem)->SetWindowSize({ 1280, 720 });

    m_sceneMgr.Add<Title>(u8"Title");

    if ($(DxSystem)->Initialize(windowTitle)) return true;
    m_sceneMgr.Initialize();
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
    m_sceneMgr.Update();
    return false;
}
void Game::Draw() {
    m_sceneMgr.Draw();
}