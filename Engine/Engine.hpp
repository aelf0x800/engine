#pragma once

#include "Window.hpp"
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>

namespace Engine
{

using Microsoft::WRL::ComPtr;

class Engine : public Window<Engine>
{
private:
	ComPtr<ID3D12Device> m_device;
	ComPtr<IDXGISwapChain> m_swapChain;
	ComPtr<ID3D12CommandList> m_commandList;

	ID3D12Debug* m_debug0;

	bool m_isOpen;

public:
	Engine();
	~Engine();

	void Run();
	void OnClose();
};

}