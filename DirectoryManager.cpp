#include "stdafx.h"

std::vector<std::string> DirectoryManager::findAllFilesInDirectory(std::vector<std::string>& vectorOfStrings, std::string const& directory)
{
	std::experimental::filesystem::path directoryPath(directory);
	std::experimental::filesystem::recursive_directory_iterator start(directoryPath);
	std::experimental::filesystem::recursive_directory_iterator end;
	std::transform(start, end, std::back_inserter(vectorOfStrings), directory_entry_information());
	removeFilebyExtensionFromVector(vectorOfStrings, ".dir");
	return vectorOfStrings;
}

bool DirectoryManager::equalFileContent(const std::string& pathOfFileA, const std::string& pathOfFileB)
{
	std::ifstream alphaFile(pathOfFileA.c_str());
	std::ifstream betaFile(pathOfFileB.c_str());
	std::ifstream::pos_type sizeAlpha, sizeBeta;
	sizeAlpha = filesize(pathOfFileA);
	alphaFile.seekg(0, std::ifstream::beg);
	sizeBeta = filesize(pathOfFileB);
	betaFile.seekg(0, std::ifstream::beg);
	if (sizeAlpha != sizeBeta)
	{
		return false;
	}
	char* alphaBuffer = (char*)malloc(static_cast<int>(sizeAlpha));
	char* betaBuffer = (char*)malloc(static_cast<int>(sizeBeta));
	size_t remaining = static_cast<int>(sizeAlpha);
	while (remaining)
	{
		size_t size = std::min(static_cast<int>(sizeAlpha), static_cast<int>(remaining));
		alphaFile.read(alphaBuffer, size);
		betaFile.read(betaBuffer, size);
		if (0 != memcmp(alphaBuffer, betaBuffer, size))
		{
			return false;
		}
		remaining -= size;
	}
	free(alphaBuffer);
	free(betaBuffer);
	return true;
}

void DirectoryManager::removeUniqueFilesFromVector(std::vector<std::string>& vectorOfStrings)
{
	for (size_t x = 0; x < vectorOfStrings.size(); x++)
	{
		bool isUniqueFlag = false;
		std::vector<std::string> alphaVector = returnStringStreamVector(vectorOfStrings[x]);
		for (size_t y = 0; y < vectorOfStrings.size(); y++)
		{
			std::vector<std::string> betaVector = returnStringStreamVector(vectorOfStrings[y]);
			if (alphaVector[0] == betaVector[0] && alphaVector[1] == betaVector[1] && x != y)
			{
				if (equalFileContent(alphaVector[2] + "\\" + alphaVector[0], betaVector[2] + "\\" + betaVector[0]))
				{
					isUniqueFlag = false;
					break;
				}
				else
				{
					isUniqueFlag = true;
				}
			}
			else
			{
				isUniqueFlag = true;
			}
		}
		if (isUniqueFlag)
		{
			auto extensionBegin = vectorOfStrings[x].find(".");
			auto extensionEnd = vectorOfStrings[x].find(" ");
			auto extensionLength = extensionEnd - extensionBegin;
			vectorOfStrings[x].replace(extensionBegin, extensionLength, ".unq");
		}
	}
	removeFilebyExtensionFromVector(vectorOfStrings, ".unq");
}
void DirectoryManager::outputFilesAndDirectories(std::vector<std::string>& vectorOfStrings)
{
	bool printFileFlag = true;
	std::sort(vectorOfStrings.begin(), vectorOfStrings.end());
	std::ofstream outputFile("List of files.txt");
	if (outputFile)
	{
		std::vector<std::string> alphaVector = returnStringStreamVector(vectorOfStrings[0]);
		for(auto& x : vectorOfStrings)
		{
			std::vector<std::string> betaVector = returnStringStreamVector(x);
			if (betaVector[0] != alphaVector[0])
			{
				printFileFlag = true;
				alphaVector = betaVector;
			}
			if (printFileFlag)
			{
				printFileFlag = false;
				outputFile << betaVector[0] + "\n";
			}
			outputFile << "\t" + betaVector[2] + "\n";
		}
	}
}
std::ifstream::pos_type DirectoryManager::filesize(const std::string& filename)
{
	std::ifstream in;
	in.open(filename, std::ios::in | std::ios::binary);
	in.ignore(std::numeric_limits<std::streamsize>::max());
	std::streamsize length = in.gcount();
	in.clear();
	in.seekg(0, std::ios_base::beg);
	return length;
}
void DirectoryManager::removeFilebyExtensionFromVector(std::vector<std::string>& vectorOfStrings, const std::string& extension)
{
	vectorOfStrings.erase(std::remove_if(vectorOfStrings.begin(), vectorOfStrings.end(), [&extension](const std::string& file)
	{
		return file.find(extension) != std::string::npos;
	}), vectorOfStrings.end());
}
std::vector<std::string> DirectoryManager::returnStringStreamVector(std::string stringToVector)
{
	std::istringstream sStream(stringToVector);
	std::vector<std::string> stringVector((std::istream_iterator<std::string>(sStream)),
		std::istream_iterator<std::string>());
	return stringVector;
}