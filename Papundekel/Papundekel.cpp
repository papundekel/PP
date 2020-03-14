#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>

namespace fs = std::filesystem;

void create_header(const fs::path& path)
{
	auto filename = path.filename().string() + ".hpp";

	std::remove(filename.c_str());

	std::ofstream file(filename);

	file << "#pragma once\n";

	for (auto&& entry : fs::recursive_directory_iterator(path))
	{
		if (entry.is_regular_file())
		{
			auto path = entry.path();
			if (path.extension().string() == ".hpp")
			{
				file << "#include \"" << path.string() << "\"\n";
			}
		}
	}
}

int main()
{
	for (auto&& entry : fs::directory_iterator(fs::current_path()))
		if (entry.is_directory())
			create_header(entry.path());

	return 0;
}
	