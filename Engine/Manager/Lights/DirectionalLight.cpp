#include "DirectionalLight.h"
#include "ImguiManger.h"
DirectionalLight* DirectionalLight::GetInstance()
{
	static DirectionalLight instance;
	return &instance;
}
void DirectionalLight::Initialize()
{
	directXCommon_ = DirectXCommon::GetInstance();

	Resource = directXCommon_->CreateBufferResource(directXCommon_->GetDevice().Get(), sizeof(DirectionalLightData));
	Resource.Get()->Map(0, nullptr, reinterpret_cast<void**>(&directionalLightData));
	directionalLightData->color = { 1.0f,1.0f,1.0f,1.0f };
	directionalLightData->direction = { 0.0f,-1.0f,0.0f };
	directionalLightData->intensity = 1.0f;
}

void DirectionalLight::Update()
{
	ImGui::Begin("Light");
	ImGui::DragFloat3("Direction", &directionalLightData->direction.x, 0.1f);
	ImGui::End();
	directionalLightData->direction = Normalise(directionalLightData->direction);
}
