#pragma once
#include "DirectXCommon.h"
#include "BlueMoon.h"
#include "SrvDescriptorHeap.h"
class CopyRender
{
private:
	DirectXCommon* directXCommon_;
	BlueMoon* bluemoon_;
	SrvDescriptorHeap* heap_;
	int index_;
public:
	void Init();
	void Draw();
};

