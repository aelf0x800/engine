#include "Exception.hpp"
#include "Engine.hpp"

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
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferDesc.Width = 0;
    swapChainDesc.BufferDesc.Height = 0;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 0;
    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 1;
    swapChainDesc.OutputWindow = m_hWnd;
    swapChainDesc.Windowed = TRUE;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swapChainDesc.Flags = 0;

    D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0,
                                  D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_device,
                                  nullptr, &m_context);

    /*ID3D11Resource* backBuffer = nullptr;
    m_swapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&backBuffer));
    m_device->CreateRenderTargetView(backBuffer, nullptr, &m_target);
    RELEASE(backBuffer);*/

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
        WaitMessage();
    }
}

void Engine::OnClose() { m_isOpen = false; }

}