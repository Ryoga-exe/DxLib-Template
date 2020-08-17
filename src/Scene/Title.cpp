#include "Title.h"

Title::Title(ISceneChanger* changer) : BaseScene(changer, DxLib::GetColor(255, 255, 255)) {
}

void Title::Initialize() {
}

void Title::Finalize() {
}

void Title::Update() {
    if (Keyboard::Inst()->GetStatus(KEY(ESCAPE)) == Keyboard::State::Pressed) {
        // m_sceneChanger->ChangeScene("Menu");
    }
}

void Title::Draw() {
    BaseScene::Draw();
}