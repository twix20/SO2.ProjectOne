#pragma once
#include <windows.h>
#include <cstdarg>
#include <random>

namespace Utilss
{
	inline int print_log(const char* format, ...)
	{
		static char s_printf_buf[1024];
		va_list args;
		va_start(args, format);
		vsnprintf_s(s_printf_buf, sizeof(s_printf_buf), format, args);
		va_end(args);
		OutputDebugStringA(s_printf_buf);
		return 0;
	}


	inline int random_in_range(const int min, const int max)
	{
		std::random_device r;
		std::default_random_engine e1(r());

		const std::uniform_int_distribution<int> uniform_dist(min, max);
		const auto result = uniform_dist(e1);

		return result;
	}
}
