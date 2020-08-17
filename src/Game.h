#pragma once
#include "DxSystem.h"
#include "BaseScene/SceneManager.h"

class Game {
public:
    bool Initialize(const TCHAR* windowTitle);
    bool Finalize();
    void ProcessLoop();
private:
    bool SystemUpdate();
    bool Update();
    void Draw();

    SceneManager m_sceneMgr;
};