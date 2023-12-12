#include "Unit.h"
#include "Player.h"
void Unit::Init(int idref, Vector2 pos)
{
	id = idref;
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initialize({ 0.0f,0.0f,0.0f,0.0f }, { 64.0f,64.0f,0.0f,0.0f });
	texhandle_ = Texturemanager::GetInstance()->Load("Resource/circle.png");
	SpriteuvTransform =
	{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
	SpriteTransform = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	mapPos_ = pos;
	count_ = 0;
}

void Unit::Update()
{
	count_++;
	SpriteTransform.translate = { mapPos_.x * 64.0f,mapPos_.y * 64.0f,0.0f };
}

void Unit::Draw()
{

	sprite_->Draw(SpriteTransform, SpriteuvTransform, { 1.0f,1.0f,1.0f,1.0f }, texhandle_);

}

void Unit::Move(Vector2 velo)
{
	mapPos_.x += velo.x;
	mapPos_.y += velo.y;
}

void Unit::MoveEnd(Player* player)
{
	isSelected = false;
	
}

void Unit::MoveAI()
{
	if (count_ > 60) {
		mapPos_.x += 1.0f;
		count_ = 0;
	}
}
