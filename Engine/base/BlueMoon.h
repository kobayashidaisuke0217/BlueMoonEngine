#pragma once

#include "../../game/Manager/GameManager.h"
#include "WinApp.h"
#include "DirectXCommon.h"

class BlueMoon final
{
private:

	//コンストラクタ
	BlueMoon() = default;

	//デストラクタ
	~BlueMoon();

public:

	//インスタンス
	static BlueMoon* GetInstance();

	BlueMoon(const BlueMoon& bluemoon) = delete;

	BlueMoon& operator=(const BlueMoon& blueMoon) = delete;

public:

	void Run();

private:

	void Initialize();

	void BeginFrame();

	void Update();

	void Draw();

	void EndFrame();

	void Release();

private:

	GameManager* gameManager_ = nullptr;
};