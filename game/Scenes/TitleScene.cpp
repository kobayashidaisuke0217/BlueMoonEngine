#include "TitleScene.h"
#include "ImGuiManger.h"

TitleScene::~TitleScene()
{
}
void TitleScene::Initialize()
{	
	blueMoon_ = BlueMoon::GetInstance();

	directXCommon_ = DirectXCommon::GetInstance();
	input = Input::GetInstance();
	count = 0;
	model_ = Model::CreateModelFromObj("Resource", "axis.obj");
	worldTransformModel_[0].Initialize();
	worldTransformModel_[1].Initialize();
	worldTransformModel_[0].translation_.x = 5.0f;
	worldTransformModel_[1].translation_.x = -5.0f;
	viewProjection_.Initialize();
}

void TitleScene::Update()
{
	
	ImGui::Begin("SceneManager");
	ImGui::InputInt("SceneNum", &sceneNum);
	ImGui::Text("count %d",count);
	ImGui::End();
	ImGui::Begin("camera");
	ImGui::DragFloat3("translate", &viewProjection_.translation_.x, 0.1f);
	ImGui::DragFloat3("rotate", &viewProjection_.rotation_.x, 0.1f);
	ImGui::End();
	ImGui::Begin("object");
	ImGui::DragFloat3("1_tranlate", &worldTransformModel_[0].translation_.x, 0.1f);
	ImGui::DragFloat3("1_rotate", &worldTransformModel_[0].rotation_.x, 0.1f);
	ImGui::DragFloat3("1_scale", &worldTransformModel_[0].scale_.x, 0.1f);
	ImGui::DragFloat3("2_tranlate", &worldTransformModel_[1].translation_.x, 0.1f);
	ImGui::DragFloat3("2_rotate", &worldTransformModel_[1].rotation_.x, 0.1f);
	ImGui::DragFloat3("2_scale", &worldTransformModel_[1].scale_.x, 0.1f);
	ImGui::End();
	if (input->PushKey(DIK_SPACE)) {
		sceneNum = GAME_SCENE;
		count++;
	}
	
	if (sceneNum < 0) {
		sceneNum = 0;
		
	}
	worldTransformModel_[0].UpdateMatrix();
	worldTransformModel_[1].UpdateMatrix();
	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();
	
}

void TitleScene::Draw()
{
	blueMoon_->ModelPreDrawWireFrame();
	model_->Draw(worldTransformModel_[0], viewProjection_);
	blueMoon_->ModelPreDraw();
	model_->Draw(worldTransformModel_[1], viewProjection_);
}

void TitleScene::Finalize()
{
}
