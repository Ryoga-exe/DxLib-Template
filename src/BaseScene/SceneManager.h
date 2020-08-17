#pragma once
#include "ISceneChanger.h"
#include "BaseScene.h"
#include <vector>
#include <string>

class SceneManager : public ISceneChanger, Task {
public:
    SceneManager();
    void Initialize() override;
    void Finalize() override;
    void Update() override;
    void Draw() override;

    void ChangeScene(std::string nextScene) override;
    template <typename T>
    T Add(std::string name);

private:
    int FindIndex(std::string str);
    bool DrawSceneChangeEffect(bool isQuit);

    std::vector<BaseScene*> m_scenes;
    std::vector<std::string> m_names;
    std::string m_nextScene;
    std::size_t m_currentSceneIndex;

    bool m_hasFinishedChanging;
    Timer m_timer;
    int   m_changedTime;
};