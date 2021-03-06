﻿#pragma once
#include "../BaseScene/BaseScene.h"

class Title : public BaseScene {
public:
    Title(ISceneChanger* changer);
    void Initialize() override;
    void Finalize() override;
    void Update() override;
    void Draw() override;
};