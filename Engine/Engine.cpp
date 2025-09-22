#include "Exception.hpp"
#include "Engine.hpp"
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

#define TRY(X) if (FAILED(X)) throw DirectXException();
#define RELEASE(X) if (X != nullptr) X->Release()

namespace Engine
{

Engine::Engine() : Window(L"Engine", 1600, 900),
                   m_device(nullptr),
                   m_swapChain(nullptr),
                   m_context(nullptr),
                   m_target(nullptr),
                   m_isOpen(false)
{
    DXGI_SWAP_CHAIN_DESC swapChainDesc =
    {
        .BufferDesc =
        {
            .Width = 0,
            .Height = 0,
            .RefreshRate =
            {
                .Numerator = 0,
                .Denominator = 0
            },
            .Format = DXGI_FORMAT_B8G8R8A8_UNORM,
            .ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
            .Scaling = DXGI_MODE_SCALING_UNSPECIFIED
        },
        .SampleDesc =
        {
            .Count = 1,
            .Quality = 0
        },
        .BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,
        .BufferCount = 1,
        .OutputWindow = m_hWnd,
        .Windowed = TRUE,
        .SwapEffect = DXGI_SWAP_EFFECT_DISCARD,
        .Flags = 0
    };

    TRY(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0,
                                  D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_device,
                                  nullptr, &m_context));
    m_isOpen = true;
}

Engine::~Engine()
{
    RELEASE(m_target);
    RELEASE(m_context);
    RELEASE(m_swapChain);
    RELEASE(m_device);
}

void Engine::Run()
{
    while (m_isOpen)
    {
        InvalidateRgn(m_hWnd, nullptr, TRUE);
        WaitMessage();
    }
}

void Engine::OnClose() { m_isOpen = false; }

}