#include "cbpch.h"
#include "File.h"

#include <fstream>

namespace CherryBell {
	std::string IO::ReadFile(std::string_view filepath)
	{
		std::string fileContents;
		std::ifstream in(filepath.data(), std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1)
			{
				fileContents.resize(in.tellg());
				in.seekg(0, std::ios::beg);
				in.read(&fileContents[0], fileContents.size());
				in.close();
			}
			else
			{
				CB_CORE_ERROR("Could not read from file \"{0}\"", filepath);
			}
		}
		else
		{
			CB_CORE_ERROR("Could not open file \"{0}\"", filepath);
		}
		return fileContents;
	}
}
