#include <iostream>
#include "Linker.h"

int main()
{
	std::cout << (Linker::Link(fs::path{ "./" }) ? "File Linking Completed" : "File Linking Failed") << std::endl;
	std::cin.get();
	return 0;
}
