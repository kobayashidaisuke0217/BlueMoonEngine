#pragma once
#include "Sphere.h"
#include "worldTransform.h"
#include "TextureManager.h"
#include <memory> 
#include "viewProjection.h"
#include "Sprite.h"
#include "Unit.h"
enum select {
	Selector,
	UNIT,
};
class Player
{
public:
	Player();

	void Init();
	void Update();
	void Draw(const ViewProjection& view);
	void Draw2D();
	void MoveLeft();
	void MoveRight();
	void Move(Vector2 velo);
	void SelectUnit();
	int GetSelectMode() {
		return selectMode_;
	}
	Unit* GetSelectUnit() { return selectedUnit_; }
private:float speed;
	WorldTransform worldTransform_;
	std::unique_ptr <Sphere> sphere_;
	std::unique_ptr<Sprite> sprite_;
	uint32_t texhandle_;
	Vector2 mapPos_;
	Transform SpriteTransform;
	Transform SpriteuvTransform;
	Unit* unit_;
	Unit* selectedUnit_;
	int selectMode_;
};

