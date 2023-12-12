#include "Player.h"

Player::Player()
{
}

void Player::Init()
{
	sphere_ = std::make_unique<Sphere>();
	sphere_->Initialize();
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initialize({ 0.0f,0.0f,0.0f,0.0f }, { 64.0f,64.0f,0.0f,0.0f });
	speed = 0.2f;
	worldTransform_.Initialize();
	texhandle_= Texturemanager::GetInstance()->Load("Resource/uvChecker.png");
	SpriteuvTransform =
	{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
	SpriteTransform = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	mapPos_ = { 0.0f,0.0f };

	for (int i = 0; i < 5; i++) {
		unit_[i] = new Unit;
		unit_[i]->Init(i,{i+i+1.0f,i+1.0f});
	}
}

void Player::Update()
{
	SpriteTransform.translate = { mapPos_.x * 64.0f,mapPos_.y * 64.0f,0.0f };
	for (int i = 0; i < 5; i++) {
		unit_[i]->Update();
	}
	for (int i = 0; i < 5; i++) {
		if (unit_[i]->GetSelect()) {
			selectedUnit_ = unit_[i];
			selectMode_ = UNIT;
			break;
		}
		else {
			selectMode_ = Selector;
			selectedUnit_ = nullptr;
		}

	}
	if (selectedUnit_) {
		mapPos_ = selectedUnit_->GetPos();
	}
	worldTransform_.UpdateMatrix();
}

void Player::Draw(const ViewProjection& view)
{
	
	//sphere_->Draw({ 1.0f,1.0f,1.0f,1.0f }, worldTransform_, texhandle_, view);
}

void Player::Draw2D()
{
	sprite_->Draw(SpriteTransform, SpriteuvTransform, { 1.0f,1.0f,1.0f,1.0f }, texhandle_);
	for (int i = 0; i < 5; i++) {
		unit_[i]->Draw();
	}
}

void Player::MoveLeft()
{
	worldTransform_.translation_.x = worldTransform_.translation_.x-speed;
	mapPos_.x-= 1.0f;
}
void Player::MoveRight()
{
	worldTransform_.translation_.x = worldTransform_.translation_.x + speed;
    mapPos_.x += 1.0;
}

void Player::Move(Vector2 velo)
{

	mapPos_.x += velo.x;
	mapPos_.y += velo.y;
}

void Player::SelectUnit()
{
	for (int i = 0; i < 5; i++) {
		if (unit_[i]->GetPos().x == mapPos_.x && unit_[i]->GetPos().y == mapPos_.y) {
			unit_[i]->SetSelect();
			selectMode_ = UNIT;
			break;
		}
	}

}
