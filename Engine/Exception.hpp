#pragma once

#include <string>

namespace Engine
{

class Exception
{
protected:
	std::wstring m_errorString;
	std::uint32_t m_errorCode;

public:
	void ShowMessageBox() const noexcept;
	void ShowDebugString() const noexcept;

	std::wstring GetErrorString() const noexcept;
	std::uint32_t GetErrorCode() const noexcept;
};

class WindowException : public Exception
{
public:
	WindowException();
};

class DirectXException : public Exception
{
public:
	DirectXException();
};

}