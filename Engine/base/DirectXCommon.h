#pragma once
#include "WinApp.h"
#include "combert.h"
#include "../Math/MyMath.h"

#include <cassert>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <dxgidebug.h>

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dxcompiler.lib")

#include <wrl.h>
#include <chrono>


using Microsoft::WRL::ComPtr;

struct SwapChain {
	ComPtr<IDXGISwapChain4> pSwapChain;
	ComPtr<ID3D12Resource> pResource[2];
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
};

//リークチェッッカー
struct D3DResourceLeakChecker
{
	~D3DResourceLeakChecker()
	{
		ComPtr<IDXGIDebug1>debug;
		if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&debug))))
		{
			debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
			debug->ReportLiveObjects(DXGI_DEBUG_APP, DXGI_DEBUG_RLO_ALL);
			debug->ReportLiveObjects(DXGI_DEBUG_D3D12, DXGI_DEBUG_RLO_ALL);

		}
	}
};

class DirectXCommon final
{
private:

	DirectXCommon() = default;

	~DirectXCommon() = default;

public:

	static DirectXCommon* GetInstance();

	DirectXCommon(const DirectXCommon& directXSetup) = delete;

	DirectXCommon& operator=(const DirectXCommon& directXSetup) = delete;

	 ComPtr<ID3D12DescriptorHeap> GenarateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);

private:

 ComPtr<ID3D12Resource> CreateDepthStencilTextureResource(const int32_t width, const int32_t height);

#pragma region Init
	 void GenerateFactory();

	 void SelectAdapter();

	 void GenerateDevice();

	 void ErrorWarning();

	 void GenerateCommand();

	 void GenerateSwapChain();

	 void CreateDescriptorHeap();

	 void PullResourcesFromSwapChain();

	 void SetRTV();

	 void GenarateViewport();

	 void GenerateScissor();
#pragma endregion

private:

	 void InitializeFPS();

	 void UpdateFPS();

public:

	 void Initialize();

	ComPtr<ID3D12Resource> CreateBufferResource(size_t sizeInBytes);

	void BeginFrame();

	void EndFrame();

	void Release();

	void CheckRelease();

#pragma region アクセッサ
	ComPtr<ID3D12Device> GetDevice() { return device_; }

	ComPtr<ID3D12GraphicsCommandList> GetCommandList() { return DirectXCommon::GetInstance()->commandList_; }

	ComPtr<ID3D12DescriptorHeap> GetRtvDescriptorHeap() { return  rtvDescriptorHeap_; }
	ComPtr<ID3D12DescriptorHeap> GetDsvDescriptorHeap() { return  dsvDescriptorHeap_; }


	D3D12_RENDER_TARGET_VIEW_DESC GetRtvDesc() { return rtvDesc_; }

	SwapChain GetswapChain() { return DirectXCommon::GetInstance()->swapChain; }
#pragma endregion

private:
	int32_t kClientWidth_;
	int32_t kClientHeight_;

	HWND hwnd_;

	ComPtr<IDXGIFactory7> dxgiFactory_ = nullptr;
	ComPtr<IDXGIAdapter4> useAdapter_ = nullptr;
	ComPtr<ID3D12Device> device_ = nullptr;

	ComPtr<ID3D12GraphicsCommandList> commandList_ = nullptr;
	ComPtr<ID3D12CommandQueue> commandQueue_ = nullptr;
	ComPtr<ID3D12CommandAllocator> commandAllocator_ = nullptr;

	UINT backBufferIndex_;

	ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap_ = nullptr;
	ComPtr<ID3D12DescriptorHeap> dsvDescriptorHeap_ = nullptr;

	ComPtr<ID3D12Resource> depthStencilResource_ = nullptr;

	SwapChain swapChain = {};

	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc_{};
	D3D12_CPU_DESCRIPTOR_HANDLE rtvStartHandle_;
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles_[2] = {};
	D3D12_DESCRIPTOR_HEAP_DESC rtvDescriptorHeapDesc_{};

	D3D12_RESOURCE_BARRIER barrier_{};

	ComPtr<ID3D12Fence> fence_ = nullptr;

	uint64_t fenceValue_ = 0;
	HANDLE fenceEvent_ = nullptr;

	ComPtr<ID3D12Debug1> debugController_ = nullptr;

	D3D12_VIEWPORT viewport_{};
	D3D12_RECT scissorRect_{};

	std::chrono::steady_clock::time_point reference_;
};