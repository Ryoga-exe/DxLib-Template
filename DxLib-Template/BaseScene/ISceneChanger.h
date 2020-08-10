#pragma once
#include <string>

class ISceneChanger {
public:
    virtual ~ISceneChanger() = 0;
    virtual void ChangeScene(std::string nextScene) = 0;
};