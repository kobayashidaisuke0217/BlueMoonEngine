#include "BlueMoon.h"

#include "../Manager/PipeLine/PipeLineManager.h"
#include "../base/ImGuiManger.h"
#include "Input.h"
#include "TextureManager.h"
#include "SrvDescriptorHeap.h"
#include "Audio.h"
#include "GlobalVariables.h"

BlueMoon* BlueMoon::GetInstance()
{
	static BlueMoon instance;

	return &instance;
}

void BlueMoon::Initialize()
{
	const wchar_t* titleBarName = L"BlueMoon";

	const int WINDOW_SIZE_WIDTH_ = 1280;
	const int WINDOW_SIZE_HEIGHT_ = 720;
	WinApp* winApp = WinApp::GetInstance();
	//ウィンドウ
	winApp->CreateGameWindow(titleBarName, WINDOW_SIZE_WIDTH_, WINDOW_SIZE_HEIGHT_);

	//DirectX
	DirectXCommon::GetInstance()->Initialize();

	SrvDescriptorHeap::GetInstance()->Initialize();

	//ImGuiManager
	ImGuiManager::GetInstance()->Initialize();

	//Input
	Input::GetInstance()->Initialize(winApp);

	//TextureManager
	 TextureManager::GetInstance()->Initialize();

	//Audio
	Audio::GetInstance()->Initialize();

	GlovalVariables::GetInstance()->LoadFiles();

	//GameManager
	gameManager_ = new GameManager();
	gameManager_->Initialize();
}

void BlueMoon::BeginFrame()
{
	DirectXCommon::GetInstance()->BeginFrame();
	SrvDescriptorHeap::GetInstance()->PreDraw();
	ImGuiManager::GetInstance()->BeginFrame();
}

void BlueMoon::Update()
{
	GlovalVariables::GetInstance()->GetInstance()->Update();

	ImGuiManager::GetInstance()->Update();

	Input::GetInstance()->Update();

	gameManager_->Update();
}

void BlueMoon::Draw()
{
	ImGuiManager::GetInstance()->PreDraw();
	ImGuiManager::GetInstance()->Draw();

	gameManager_->Draw();
}


void BlueMoon::EndFrame()
{
	ImGuiManager::GetInstance()->EndFrame();
	DirectXCommon::GetInstance()->EndFrame();
}

void BlueMoon::Run()
{
	Initialize();

	MSG msg{};

	////メインループ
	//ウィンドウの✕ボタンが押されるまでループ
	while (true) {
		// メッセージ処理
		if (WinApp::GetInstance()->Procesmessage()) {
			break;
		}
		
			BeginFrame();

			Update();

			Draw();

			EndFrame();
		
	}

	Release();
}

void BlueMoon::Release()
{
	

	TextureManager::GetInstance()->Release();

	//ImGuiManger::GetInstance()->Release();

	DirectXCommon::GetInstance()->Release();

	
}

BlueMoon::~BlueMoon()
{
	delete gameManager_;
}
