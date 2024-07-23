#include "PipeLineManager.h"

IDxcBlob* PipelineManager::CompileShader(const std::wstring& filePath, const wchar_t* profile)
{
	return nullptr;
}

void PipelineManager::InitializeDXC()
{
	//dxcCompilerを初期化

	HRESULT hr{};


	hr = DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&dxcUtils_));
	assert(SUCCEEDED(hr));

	hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&dxcCompiler_));
	assert(SUCCEEDED(hr));

	//現時点でincludeはしないが、includeに対応


	hr = dxcUtils_->CreateDefaultIncludeHandler(&includeHandler_);
	assert(SUCCEEDED(hr));
}
