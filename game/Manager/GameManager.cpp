#include "GameManager.h"
#include "../Scenes/TitleScene.h"

//コンストラクタ
GameManager::GameManager() {

}

void GameManager::Initialize() {

	currentGamaScene_ = new TitleScene();
	currentGamaScene_->Initialize();

}


void GameManager::Update() {
	currentGamaScene_->Update();
}

void GameManager::Draw() {
	currentGamaScene_->Draw();
}



void GameManager::ChangeScene(Iscene* newGameScene) {

	delete currentGamaScene_;
	currentGamaScene_ = newGameScene;

	currentGamaScene_->Initialize();
}


//デストラクタ
GameManager::~GameManager() {
	delete currentGamaScene_;

}
