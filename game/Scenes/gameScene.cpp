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
	viewProjection_.translation_ = { 0.0f,0.0f,-5.0f };
	uvResourceNum = textureManager_->Load("Resource/uvChecker.png");
	monsterBallResourceNum = textureManager_->Load("Resource/monsterBall.png");
	BlackResourceNum = textureManager_->Load("Resource/circle.png");
	material[0] = { 1.0f,1.0f,1.0f,1.0f };
	material[1] = { 1.0f,1.0f,1.0f,1.0f };
	spritedataLeftTop_ = { 0.0f,0.0f,0.0f,1.0f };
	spritedataRightDown_ = { 320.0f,180.0f,0.0f,1.0f };
	spriteTransform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	spriteMaterial = { 1.0f,1.0f,1.0f,1.0f };
	sphereMaterial_ = { 1.0f,1.0f,1.0f,1.0f };
	SpriteuvTransform =
	{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
	
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
	particle_->Initialize(10);
	particle2_ = new Particle();
	particle2_->Initialize(13);
	triangleIsAlive_ = false;
	spriteIsAlive_ = true;
	sphereIsAlive_ = false;
	modelIsAlive_ = true;
	particleCo = 30;
	emitter_.transform = worldTransformtriangle_[0].GetTransform();
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
//////////////////////////////////////////////////////////////////////////////////////////////////////
	player_ = std::make_unique<Player>();
	inputhandler_ = std::make_unique<Inputhandler>();
	
	inputhandler_->AssignMoveLeftCommandToPressKeyA();
	inputhandler_->AssignMoveRightCommandToPressKeyD();
	
	player_->Init();
}

void GameScene::Update()
{
	bool Isparticle = false;
	
	command_ = inputhandler_->HandleInput();
	if (this->command_) {
		command_->Exec(*player_.get());
	}
	
	player_->Update();
	particle_->Update();
	particle2_->Update();
	worldTransformModel_.UpdateMatrix();
	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();
	ImGui::Begin("camera");
	ImGui::DragFloat3("translate", &viewProjection_.translation_.x, 0.1f);
	ImGui::DragFloat3("rotate", &viewProjection_.rotation_.x, 0.1f);
	ImGui::DragInt("parcount", &particleCo);
	ImGui::Checkbox("par", &Isparticle);
	ImGui::End();
	ImGui::Begin("Scene");
	ImGui::DragFloat3("translate", &emitter_.transform.translate.x, 0.1f);
	ImGui::DragFloat3("scale", &emitter_.transform.scale.x, 0.1f);
	ImGui::DragFloat3("rotate", &emitter_.transform.rotate.x, 0.1f);
	ImGui::DragFloat4("color", &spriteMaterial.x, 0.1f);
	ImGui::InputInt("blendCount", &blendCount_);
	ImGui::InputInt("SceneNum", &sceneNum);
	if (sceneNum > 1) {
		sceneNum = 1;
	}
	ImGui::End();
	if (Isparticle) {
		particle_->AddParticle(emitter_, particleCo);
	}
	Isparticle = false;
	worldTransformtriangle_[0].UpdateMatrix();
	worldTransformtriangle_[1].UpdateMatrix();
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
	
	//sphere_->Draw(sphereMaterial_, worldTransformtriangle_[1], monsterBallResourceNum, viewProjection_);
	player_->Draw(viewProjection_);
	blueMoon_->PariclePreDraw();
	particle_->Draw( viewProjection_, {1.0f,1.0f,1.0f,1.0f}, BlackResourceNum);
	//particle2_->Draw(worldTransformtriangle_[1].GetTransform(), viewProjection_, { 1.0f,1.0f,1.0f,1.0f }, BlackResourceNum);

	blueMoon_->ModelPreDrawWireFrame();
	
		//sphere_->Draw(sphereMaterial_, worldTransformtriangle_[0], monsterBallResourceNum, viewProjection_);
	
	
}

void GameScene::ApplyGlobalVariables()
{
	GlovalVariables* globalVariables = GlovalVariables::GetInstance();

	const char* groupName = "Player";
	//worldTransformtriangle_[0].translation_ = globalVariables->GetVector3Value(groupName, "Translation");
}

void GameScene::Draw2D() {
	blueMoon_->SetBlendMode(blendCount_);
	if (spriteIsAlive_ ) {
		sprite_->Draw(spriteTransform_, SpriteuvTransform, spriteMaterial, monsterBallResourceNum);
	
	}

}
void GameScene::Finalize()
{
	delete particle2_;
	delete particle_;
	delete sphere_;
	delete  sprite_;
	delete triangle_;
	for (int i = 0; i < 2; i++) {
		delete model_[i];

	}
	
}

