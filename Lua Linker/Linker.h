#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <cstddef>

namespace fs = std::filesystem;

class Linker {
public:
	static bool Link(const fs::path &folderPath);
};
