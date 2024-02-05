#pragma once
#include "Iscene.h"
#include "Input.h"
#include "model.h"
#include "worldTransform.h"
#include "ViewProjection.h"
class TitleScene:public Iscene
{
private:
	int count;
public:
	~TitleScene()override;
	 void Initialize() override;

	 void Update() override;

	 void Draw() override;
	 void Finalize()override;
private:
	Input* input=nullptr;
	BlueMoon* blueMoon_;
	DirectXCommon* directXCommon_;
	WorldTransform worldTransformModel_[2];
	Model* model_;
	ViewProjection viewProjection_;
};

