#pragma once
#include"Sprite.h"
#include "mymath.h"
#include "TextureManager.h"
class Player;
class Unit
{
public:
	Unit() = default;
	void Init(int idref,Vector2 pos);
	void Update();
	void Draw();
	void Move(Vector2 velo);
	void MoveEnd(Player* player);
	Vector2 GetPos() {
		return mapPos_;
	}
	bool GetSelect() { return isSelected; }
	void SetSelect() { isSelected = true; }
	void MoveAI();
	
private:
	std::unique_ptr<Sprite> sprite_;
	uint32_t texhandle_;
	Vector2 mapPos_;
	Transform SpriteTransform;
	Transform SpriteuvTransform;
	bool isSelected = false;
	uint32_t id;
	int count_;
};

