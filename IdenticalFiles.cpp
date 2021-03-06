#include "stdafx.h"

int main()
{   
	IdenticalFiles userAgent;
	DirectoryManager dirManager;
	std::vector<std::string> vectorOfStrings = userAgent.userInput(userAgent);
	dirManager.removeUniqueFilesFromVector(vectorOfStrings);
	dirManager.outputFilesAndDirectories(vectorOfStrings);
	return 0;
}
std::vector<std::string> IdenticalFiles::userInput(IdenticalFiles& dirController)
{
	std::cout << "Please enter directory path, press enter for directory of program.\n";
	std::string directoryPath;
	getline(std::cin, directoryPath);
	if (std::experimental::filesystem::exists(directoryPath))
	{
		try
		{
			return dirController.readDirectoryAt(directoryPath);
		}
		catch (const std::exception&)
		{
			std::cout << "\nInvalid path, using program directory.";
			return dirController.readDirectoryAt();
		}
	}
	else
	{
		return dirController.readDirectoryAt();
	}
}
std::vector<std::string> IdenticalFiles::readDirectoryAt(std::string directory)
{
	DirectoryManager dirReader;
	std::vector<std::string> vectorOfStrings;
	return dirReader.findAllFilesInDirectory(vectorOfStrings, directory);
}
std::vector<std::string> IdenticalFiles::readDirectoryAt()
{
	TCHAR buffer[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, buffer);
	char directory[260];
	char DefChar = ' ';
	WideCharToMultiByte(CP_ACP, 0, buffer, -1, directory, 260, &DefChar, NULL);
	DirectoryManager dirReader;
	std::vector<std::string> vectorOfStrings;
	return dirReader.findAllFilesInDirectory(vectorOfStrings, directory);
}