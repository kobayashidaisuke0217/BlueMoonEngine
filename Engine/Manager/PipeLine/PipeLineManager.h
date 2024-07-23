#pragma once
#include <string>

#include <dxgidebug.h>
#include "../../MyUtility/combert.h"
#include <cassert>

#include <dxcapi.h>

#pragma comment(lib,"dxcompiler.lib")
enum BlemdMode
{
	//ブレンド無し
	BlendModeNone,

	//通常ブレンド
	BlendModeNormal,

	//加算ブレンド
	BlendModeAdd,

	//減算ブレンド
	BlendModeSubtract,

	//乗算ブレンド
	BlendModeMultiply,

	//スクリーンブレンド
	BlendModeScreen,
};

class PipelineManager final
{
private:

	PipelineManager() = default;

	~PipelineManager() = default;

public:
	static PipelineManager* GetInstance();

	PipelineManager(const PipelineManager& pipelineManager) = delete;

	PipelineManager& operator=(const PipelineManager& pipelineManager) = delete;


	IDxcBlob* CompileShader(
		const std::wstring& filePath,
		const wchar_t* profile
	);

	void InitializeDXC();

private:
	//DXC
	IDxcUtils* dxcUtils_ = nullptr;
	IDxcCompiler3* dxcCompiler_ = nullptr;
	IDxcIncludeHandler* includeHandler_ = nullptr;
};

