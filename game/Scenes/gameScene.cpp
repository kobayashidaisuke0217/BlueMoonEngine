#include "gameScene.h"


GameScene::~GameScene()
{
	
}

void GameScene::Initialize()
{
	blueMoon_ = BlueMoon::GetInstance();

	directXCommon_ = DirectXCommon::GetInstance();

	textureManager_ = Texturemanager::GetInstance();

	viewProjection_.Initialize();
	

	sphere_ = new Sphere();
	sphere_->Initialize();

	model_[0] = Model::CreateModelFromObj("Resource", "fence.obj");
	model_[1] = new Model();
	model_[1]->Initialize("Resource", "plane.obj");
	for (int i = 0; i < 2; i++) {
		modelMaterial_[i] = { 1.0f,1.0f,1.0f,1.0f };
	}
	triangle_ = new Triangle();
	triangle_->Initialize();
	for (int i = 0; i < 2; i++) {
		worldTransformtriangle_[i].Initialize();
	}
	worldTransformModel_.Initialize();
	sprite_ = new Sprite();
	sprite_->Initialize(  spritedataLeftTop_, spritedataRightDown_);
	particle_ = new Particle();
	particle_->Initialize();
	particle2_ = new Particle();
	particle2_->Initialize();
	triangleIsAlive_ = false;
	spriteIsAlive_ = true;
	sphereIsAlive_ = false;
	modelIsAlive_ = true;
	particleTransform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	particleuvTransform =
	{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
	GlovalVariables* globalVariables{};
	globalVariables = GlovalVariables::GetInstance();
	blendCount_ = 0;
	const char* groupName = "Player";
	GlovalVariables::GetInstance()->CreateGroup(groupName);
	globalVariables->AddItem(groupName, "Test", 90.0f);
	globalVariables->AddItem(groupName, "Translation", worldTransformtriangle_[0].translation_);
	ApplyGlobalVariables();

	
}

void GameScene::Update()
{
	
	worldTransformtriangle_[0].UpdateMatrix();
	worldTransformtriangle_[1].UpdateMatrix();
	worldTransformModel_.UpdateMatrix();
	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();

	ImGui::Begin("Scene");

	ImGui::DragFloat3("translate", &worldTransformtriangle_[0].translation_.x, 0.1f);
	ImGui::DragFloat3("scale", &worldTransformtriangle_[0].scale_.x, 0.1f);
	ImGui::DragFloat3("rotate", &worldTransformtriangle_[0].rotation_.x, 0.1f);
	ImGui::DragFloat4("color", &spriteMaterial.x, 0.1f);

	ImGui::InputInt("blendCount", &blendCount_);
	ImGui::InputInt("SceneNum", &sceneNum);
	if (sceneNum > 1) {
		sceneNum = 1;
	}
	ImGui::End();
}


void GameScene::Draw()
{
	
	//3D描画準備
	blueMoon_->ModelPreDraw();
	Draw3D();
	//2D描画準備
	blueMoon_->SpritePreDraw();
	Draw2D();
}

void GameScene::Draw3D()
{
	blueMoon_->ModelPreDraw();
	
	
	blueMoon_->PariclePreDraw();

	particle_->Draw(worldTransformtriangle_[0], viewProjection_, {1.0f,1.0f,1.0f,1.0f}, monsterBallResourceNum);
	particle2_->Draw(worldTransformtriangle_[1], viewProjection_, { 1.0f,1.0f,1.0f,1.0f }, monsterBallResourceNum);


	blueMoon_->ModelPreDrawWireFrame();
	
	
}

void GameScene::ApplyGlobalVariables()
{
	GlovalVariables* globalVariables = GlovalVariables::GetInstance();

	const char* groupName = "Player";

}

void GameScene::Draw2D() {
	blueMoon_->SetBlendMode(blendCount_);

	if (spriteIsAlive_ ) {
		sprite_->Draw(spriteTransform_, SpriteuvTransform, spriteMaterial, monsterBallResourceNum);


}
void GameScene::Finalize()
{
	
}

