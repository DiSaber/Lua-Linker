#include "Linker.h"

bool Linker::Link(const fs::path &folderPath)
{
	fs::path entrypoint(folderPath / "main.lua");

	std::ifstream entryFile(entrypoint);

	if (!entryFile) {
		return false;
	}

	std::ostringstream mainSS;
	mainSS << entryFile.rdbuf();
	std::string mainFile(mainSS.str());

	for (auto &file : fs::directory_iterator(folderPath)) {
		const fs::path &filepath = file.path();

		if (filepath.has_filename() && filepath.filename() != "main.lua" && filepath.filename() != "final.lua") {
			const std::string filename(filepath.filename().string());

			if (filename.substr(filename.find(".") + 1, std::string::npos) != "lua") {
				continue;
			}

			std::string includeName{ "-- include " + filename };
			const std::size_t loc = mainFile.find(includeName);

			if (loc == std::string::npos) {
				continue;
			}

			std::cout << "Linking: " << filename << std::endl;

			std::ifstream linkingFile(filepath);

			if (!linkingFile) {
				return false;
			}

			std::ostringstream linkSS;
			linkSS << linkingFile.rdbuf();
			std::string linkFile(linkSS.str());

			mainFile.replace(loc, includeName.size(), linkFile);
		}
	}

	fs::path outputPath(folderPath / "final.lua");

	if (fs::is_regular_file(outputPath)) {
		fs::remove(outputPath);
	}

	std::ofstream outputFile(outputPath);

	if (!outputFile) {
		return false;
	}

	outputFile << mainFile;

	return true;
}
