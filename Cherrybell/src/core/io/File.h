#pragma once
#include <string>

namespace CherryBell
{
	class IO
	{
	public:
		static std::string ReadFile(std::string_view filepath);
	};
}