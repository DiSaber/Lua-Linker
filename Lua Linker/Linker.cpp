#include "Linker.h"

bool Linker::Link(const fs::path &folderPath) {
	const std::ifstream entryFile{ folderPath / "main.lua" };

	if (!entryFile) {
		return false;
	}

	std::ostringstream mainSS{};
	mainSS << entryFile.rdbuf();
	std::string mainFile{ mainSS.str() };

	for (auto &file : fs::directory_iterator{ folderPath }) {
		const fs::path &filepath = file.path();

		if (filepath.has_filename() && filepath.filename() != "main.lua" && filepath.filename() != "final.lua") {
			const std::string filename{ filepath.filename().string() };

			if (filename.substr(filename.find(".") + 1, std::string::npos) != "lua") {
				continue;
			}

			const std::string includeName{ "-- include " + filename };
			const std::size_t includeLocation = mainFile.find(includeName);

			if (includeLocation == std::string::npos) {
				continue;
			}

			std::cout << "Linking: " << filename << std::endl;

			const std::ifstream linkingFile{ filepath };

			if (!linkingFile) {
				return false;
			}

			std::ostringstream linkSS{};
			linkSS << linkingFile.rdbuf();
			const std::string linkFile{ linkSS.str() };

			mainFile.replace(includeLocation, includeName.size(), linkFile);
		}
	}

	std::ofstream outputFile{ folderPath / "final.lua", std::ofstream::out | std::ofstream::trunc };

	if (!outputFile) {
		return false;
	}

	outputFile << mainFile;

	return true;
}
