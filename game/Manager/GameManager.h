#pragma once

#include "../Scenes/Iscene.h"


class GameManager {
public:

	//コンストラクタ
	GameManager();

	//初期化
	void Initialize();

	//シーンチェンジ
	void ChangeScene(Iscene* newGameScene);

	//更新
	void Update();

	//描画
	void Draw();

	//デストラクタ
	~GameManager();

private:

	//StatePatternに必要な変数
	Iscene* currentGamaScene_ = nullptr;




};