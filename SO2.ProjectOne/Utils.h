#pragma once
#include <memory>
#include <windows.h>
#include <cstdarg>

namespace Utils
{
	int print_log(const char* format, ...)
	{
		static char s_printf_buf[1024];
		va_list args;
		va_start(args, format);
		vsnprintf_s(s_printf_buf, sizeof(s_printf_buf), format, args);
		va_end(args);
		OutputDebugStringA(s_printf_buf);
		return 0;
	}

	int random_in_range(const int min, const int max)
	{
		return (rand() % (max - min + 1) + min);
	}
}
