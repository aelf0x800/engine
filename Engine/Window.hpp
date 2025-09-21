#pragma once

#include "Exception.hpp"
#include <windows.h>
#include <windowsx.h>

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

template<class DerivedType>
Window<DerivedType>::Window(PCWSTR windowName, int width, int height, int x, int y,
							DWORD style, DWORD exStyle)
{
	m_hInstance = GetModuleHandleW(NULL);

	WNDCLASS wndClass = {};
	wndClass.lpfnWndProc = DerivedType::WndProc;
	wndClass.hInstance = m_hInstance;
	wndClass.lpszClassName = windowName;
	if (!RegisterClassW(&wndClass))
		throw WindowException();

	m_hWnd = CreateWindowExW(exStyle, windowName, windowName, style, x, y,
							 width, height, NULL, NULL, m_hInstance, this);
	if (m_hWnd == nullptr)
		throw WindowException();

	ShowWindow(m_hWnd, SW_SHOW);
}

template<class DerivedType>
LRESULT CALLBACK Window<DerivedType>::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	DerivedType* derivedType = NULL;

	if (msg == WM_NCCREATE)
	{
		CREATESTRUCT* create = (CREATESTRUCT*)lParam;
		derivedType = (DerivedType*)create->lpCreateParams;
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)derivedType);

		derivedType->m_hWnd = hWnd;
	}
	else
	{
		derivedType = (DerivedType*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	}

	if (derivedType)
	{
		switch (msg)
		{
		case WM_PAINT:
			{
				PAINTSTRUCT ps = {};
				HDC hDC = BeginPaint(hWnd, &ps);
				derivedType->OnPaint(hDC, ps);
				EndPaint(hWnd, &ps);
			}
			return TRUE;

		case WM_KEYDOWN: derivedType->OnKeyDown(wParam); return TRUE;
		case WM_KEYUP: derivedType->OnKeyUp(wParam); return TRUE;

		case WM_LBUTTONDOWN: derivedType->OnMouseButtonDown(VK_LBUTTON); return TRUE;
		case WM_MBUTTONDOWN: derivedType->OnMouseButtonDown(VK_MBUTTON); return TRUE;
		case WM_RBUTTONDOWN: derivedType->OnMouseButtonDown(VK_RBUTTON); return TRUE;
		case WM_LBUTTONUP: derivedType->OnMouseButtonUp(VK_LBUTTON); return TRUE;
		case WM_MBUTTONUP: derivedType->OnMouseButtonUp(VK_MBUTTON); return TRUE;
		case WM_RBUTTONUP: derivedType->OnMouseButtonUp(VK_RBUTTON); return TRUE;
		case WM_MOUSEMOVE:
			{
				int x = GET_X_LPARAM(lParam);
				int y = GET_Y_LPARAM(lParam);
				derivedType->OnMouseMove(x, y);
			}
			return TRUE;

		case WM_CLOSE:
			{
				derivedType->OnClose();
				PostQuitMessage(0);
			}
			return TRUE;

		default: if (derivedType->HandleOtherMessages(msg)) return TRUE;
		}
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

template<class DerivedType>
void Window<DerivedType>::WaitMessage()
{
	MSG msg = {};
	GetMessageW(&msg, NULL, 0, 0);
	TranslateMessage(&msg);
	DispatchMessageW(&msg);
}

template<class DerivedType>
void Window<DerivedType>::PollMessage()
{
	MSG msg = {};
	PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE);
	TranslateMessage(&msg);
	DispatchMessageW(&msg);
}

}