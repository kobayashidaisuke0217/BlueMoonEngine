#include "Player.h"

Player::Player()
{
}

void Player::Init()
{
	sphere_ = std::make_unique<Sphere>();
	sphere_->Initialize();
	speed = 0.2f;
	worldTransform_.Initialize();
	texhandle_= Texturemanager::GetInstance()->Load("Resource/uvChecker.png");
}

void Player::Update()
{

	
	worldTransform_.UpdateMatrix();
}

void Player::Draw(const ViewProjection& view)
{
	sphere_->Draw({ 1.0f,1.0f,1.0f,1.0f }, worldTransform_, texhandle_, view);
}

void Player::MoveLeft()
{
	worldTransform_.translation_.x = worldTransform_.translation_.x-speed;
}

void Player::MoveRight()
{
	worldTransform_.translation_.x = worldTransform_.translation_.x + speed;
}
