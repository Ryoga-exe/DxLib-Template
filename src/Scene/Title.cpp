#include "Title.h"

Title::Title(ISceneChanger* changer) : BaseScene(changer, DxLib::GetColor(255, 255, 255)) {
}

void Title::Initialize() {
}

void Title::Finalize() {
}

void Title::Update() {
}

void Title::Draw() {
    BaseScene::Draw();
}