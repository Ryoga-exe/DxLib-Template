#include "SceneManager.h"

SceneManager::SceneManager() : m_currentSceneIndex(0), m_changedTime(0), m_hasFinishedChanging(false) {
}

void SceneManager::Initialize() {
    if (m_scenes.empty() || m_names.empty()) return;
    m_currentSceneIndex = 0;
    for (auto scene : m_scenes) {
        scene->Initialize();
    }
    m_timer.Start();
    m_changedTime = m_timer.Elapse();
}

void SceneManager::Finalize() {
    for (auto scene : m_scenes) {
        scene->Finalize();
        delete scene;
    }
    m_scenes.clear();
    m_names.clear();
}

void SceneManager::Update() {
    if (m_scenes.empty()) return;
    if (m_currentSceneIndex >= m_scenes.size()) return;

    if (!m_nextScene.empty()) {
        int indexBuf = FindIndex(m_nextScene);
        if (indexBuf != -1) {
            m_scenes[m_currentSceneIndex]->Quit();

            m_currentSceneIndex = indexBuf;
            m_changedTime = m_timer.Elapse();

            m_nextScene.clear();
            m_scenes[m_currentSceneIndex]->Changed();
        }
    }
    m_scenes[m_currentSceneIndex]->Update();
}

void SceneManager::Draw() {
    if (m_scenes.empty()) return;
    m_scenes[m_currentSceneIndex]->Draw();
    m_hasFinishedChanging = DrawSceneChangeEffect(!m_nextScene.empty());
}

void SceneManager::ChangeScene(std::string nextScene) {
    m_nextScene = nextScene;
    m_changedTime = m_timer.Elapse();
}

int SceneManager::FindIndex(std::string str) {
    auto iter = std::find(m_names.begin(), m_names.end(), str);
    size_t index = std::distance(m_names.begin(), iter);
    if (index == m_names.size()) {
        return -1;
    }
    return index;
}

bool SceneManager::DrawSceneChangeEffect(bool isQuit) {
    SceneChangeEffect changeEffect = m_scenes[m_currentSceneIndex]->GetSceneChangeEffect();
    double values[2] = {};
    int blendMode[2] = {};
    RectSize winSize = DxSystem::Inst()->GetWindowSize();
    switch (changeEffect.effect) {
    case ChangeEffect::None:
        return isQuit;
    case ChangeEffect::Fade:
        GetDrawBlendMode(&blendMode[0], &blendMode[1]);
        values[0] = isQuit ? 0 : 255;
        values[1] = isQuit ? 255 : 0;
        DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)easing::ease(m_timer, m_changedTime, m_changedTime + changeEffect.time_ms, values[0], values[1], changeEffect.easing));
        DrawBg(changeEffect.color);
        DxLib::SetDrawBlendMode(blendMode[0], blendMode[1]);
        break;
    case ChangeEffect::Push: {
            float x1, y1, x2, y2;
            x1 = y1 = 0.f;
            x2 = (float)winSize.width;
            y2 = (float)winSize.height;
            if (changeEffect.direction % 2 == 0) {
                if (changeEffect.direction == 0) {
                    values[0] = isQuit ? 0 : winSize.width;
                    values[1] = isQuit ? winSize.width : 0;
                }
                else {
                    values[0] = isQuit ? winSize.width : 0;
                    values[1] = isQuit ? 0 : winSize.width;
                    x1 = (float)winSize.width;
                }
                x2 = (float)easing::ease(m_timer, m_changedTime, m_changedTime + changeEffect.time_ms, values[0], values[1], changeEffect.easing);
            }
            else {
                if (changeEffect.direction == 1) {
                    values[0] = isQuit ? 0 : winSize.height;
                    values[1] = isQuit ? winSize.height : 0;
                }
                else {
                    values[0] = isQuit ? winSize.height : 0;
                    values[1] = isQuit ? 0 : winSize.height;
                    y1 = (float)winSize.height;
                }
                y2 = (float)easing::ease(m_timer, m_changedTime, m_changedTime + changeEffect.time_ms, values[0], values[1], changeEffect.easing);
            }
            DrawBoxAA(x1, y1, x2, y2, changeEffect.color, TRUE);
        }
        break;
    default:
        break;
    }
    return m_changedTime + changeEffect.time_ms < m_timer.Elapse();
}