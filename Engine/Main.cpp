#define WIN32_LEAN_AND_MEAN

#include "Engine.hpp"
#include "Exception.hpp"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      [[maybe_unused]] _In_opt_ HINSTANCE hPrevInstance,
                      [[maybe_unused]] _In_ LPWSTR lpCmdLine,
                      _In_ int nCmdShow)
{
    try
    {
        Engine::Engine e;
        e.Run();
    }
    catch (Engine::WindowException we)
    {
        we.ShowMessageBox();
    }

    return 0;
}