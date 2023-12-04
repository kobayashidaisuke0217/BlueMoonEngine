#pragma once
#include "Sphere.h"
#include "worldTransform.h"
#include "TextureManager.h"
#include <memory> 
#include "viewProjection.h"
class Player
{
public:
	Player();

	void Init();
	void Update();
	void Draw(const ViewProjection& view);

	void MoveLeft();
	void MoveRight();
	
private:
	WorldTransform worldTransform_;
	std::unique_ptr <Sphere> sphere_;
	float speed;
	uint32_t texhandle_;
};

