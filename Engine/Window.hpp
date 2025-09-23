#pragma once

#include <windows.h>

namespace Engine
{

template<class DerivedType>
class Window
{
protected:
	HINSTANCE m_hInstance;
	HWND m_hWnd;

public:
	Window(PCWSTR windowName,
		   int width = CW_USEDEFAULT,
		   int height = CW_USEDEFAULT,
		   int x = CW_USEDEFAULT,
		   int y = CW_USEDEFAULT,
		   DWORD style = WS_OVERLAPPEDWINDOW,
		   DWORD exStyle = WS_EX_COMPOSITED);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void WaitMessage();
	void PollMessage();

protected:
	virtual void OnPaint(HDC hDC, PAINTSTRUCT ps) {}
	virtual void OnKeyDown(ULONGLONG key) {}
	virtual void OnKeyUp(ULONGLONG key) {}
	virtual void OnMouseButtonDown(UINT button) {}
	virtual void OnMouseButtonUp(UINT button) {}
	virtual void OnMouseMove(int x, int y) {}
	virtual void OnClose() {}
	virtual BOOL HandleOtherMessages(UINT msg) { return FALSE; }
};

}

#include "Window.cpp"