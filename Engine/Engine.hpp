#pragma once

#include "Window.hpp"
#include <d3d11.h>
#include <dxgi1_6.h>

namespace Engine
{

class Engine : public Window<Engine>
{
private:
	ID3D11Device* m_device;
	IDXGISwapChain* m_swapChain;
	ID3D11DeviceContext* m_context;
	ID3D11RenderTargetView* m_target;

	bool m_isOpen;

public:
	Engine();
	~Engine();

	void Run();
	void OnClose();
};

}