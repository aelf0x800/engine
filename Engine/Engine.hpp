#pragma once

#include "Window.hpp"
#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <wrl.h>

namespace Engine
{

class Engine : public Window<Engine>
{
private:
	Microsoft::WRL::ComPtr<ID3D12Device> m_device;
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain;
	Microsoft::WRL::ComPtr<ID3D12CommandList> m_commandList;

	Microsoft::WRL::ComPtr<ID3D12Debug> m_debug0;
	Microsoft::WRL::ComPtr<ID3D12Debug1> m_debug1;

	bool m_isOpen;

public:
	Engine();
	~Engine();

	void Run();
	void OnClose();
};

}