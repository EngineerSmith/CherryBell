#include "cbpch.h"
#include "File.h"

#include <fstream>

namespace CherryBell {
	std::string IO::ReadFile(const std::string& filepath)
	{
		std::string fileContents;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			fileContents.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&fileContents[0], fileContents.size());
			in.close();
		}
		else
		{
			CB_CORE_ERROR("Could not open file \"{0}\"", filepath);
		}
		return fileContents;
	}
}