#include "Exception.hpp"
#include <windows.h>

namespace Engine
{

void Exception::ShowMessageBox() const noexcept { MessageBoxW(nullptr, m_errorString.c_str(), nullptr, MB_ICONERROR); }
void Exception::ShowDebugString() const noexcept { OutputDebugStringW(m_errorString.c_str()); }

std::wstring Exception::GetErrorString() const noexcept { return m_errorString; }
std::uint32_t Exception::GetErrorCode() const noexcept { return m_errorCode; }

WindowException::WindowException()
{
	m_errorCode = GetLastError();
	if (m_errorCode == 0)
	{
		m_errorString = L"Success";
		return;
	}

	LPWSTR rawInfo = nullptr;
	DWORD rawInfoSz = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
									 nullptr, m_errorCode, 0, rawInfo, 0, nullptr);
	if (rawInfo != nullptr && rawInfoSz != 0)
		m_errorString = std::wstring(rawInfo, rawInfoSz);
	else
		m_errorString = L"Failed to get the error message";
}

DirectXException::DirectXException()
{

}

}