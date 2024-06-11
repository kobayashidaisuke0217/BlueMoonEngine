#include "CopyRender.h"

void CopyRender::Init()
{
	directXCommon_ = DirectXCommon::GetInstance();
	bluemoon_ = BlueMoon::GetInstance();
	heap_ = SrvDescriptorHeap::GetInstance();
	//metaDataを元にSRVの設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャ
	srvDesc.Texture2D.MipLevels = 1;

	//SRVを作成するDescripterHeapの場所を決める
	heap_->SetCPUHandle(directXCommon_->GetSrvHeap().Get(), heap_->GetSizeSRV(),heap_->GetIndex() );//direct_->GetSrvHeap()->GetGPUDescriptorHandleForHeapStart();
	heap_->SetGPUHandle(directXCommon_->GetSrvHeap().Get(), heap_->GetSizeSRV(), heap_->GetIndex());
	//先頭はIMGUIが使ってるからその次を使う
	//textureSrvHandleCPU_[index].ptr += dirctXCommon_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	//textureSrvHandleGPU_[index].ptr += dirctXCommon_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	heap_->AddPtr(heap_->GetIndex(), D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	directXCommon_->GetDevice()->CreateShaderResourceView(directXCommon_->GetRndertextureResource(), &srvDesc, heap_->GetCPUHandle(heap_->GetIndex()));
	index_ = heap_->GetIndex();
	heap_->AddIndex();
}

void CopyRender::Draw()
{
	directXCommon_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	directXCommon_->GetCommandList()->SetGraphicsRootDescriptorTable(0, heap_->GetGPUHandle(index_));
	directXCommon_->GetCommandList()->DrawInstanced(3, 1, 0, 0);

}
