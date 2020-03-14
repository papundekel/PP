#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>
#include <string_view>

namespace fs = std::filesystem;

class header
{
	std::ofstream file;

public:
	header(const std::string name)
		: file()
	{
		auto fullname = name + ".hpp";
		std::remove(fullname.c_str());
		file.open(fullname);
		file << "#pragma once\n";
	}

	void include(const std::string& filename)
	{
		file << "#include \"" << filename << "\"\n";
	}
};

void create_header(const fs::path& path)
{
	header h(path.filename().string());

	for (auto&& entry : fs::recursive_directory_iterator(path))
	{
		if (entry.is_regular_file())
		{
			auto path = entry.path();
			if (path.extension() == ".hpp")
			{
				h.include(path.string());
			}
		}
	}
}

int main()
{
	auto path = fs::current_path();

	header h(path.filename().string());

	for (auto&& entry : fs::directory_iterator(path))
	{
		if (entry.is_directory())
		{
			auto path = entry.path();
			create_header(path);
			h.include(path.string() + ".hpp");
		}
	}

	return 0;
}
	