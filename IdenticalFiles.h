#pragma once

class IdenticalFiles
{
private:
	std::vector<std::string> readDirectoryAt(std::string directory);
	std::vector<std::string> readDirectoryAt();
public:
	std::vector<std::string> userInput(IdenticalFiles& dirController);
};