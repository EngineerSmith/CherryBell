#pragma once
#include <string>

namespace CherryBell
{
	class IO
	{
	public:
		static std::string ReadFile(const std::string& filepath);
	};
}