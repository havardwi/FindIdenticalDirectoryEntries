#pragma once

class DirectoryManager
{
private:
	struct directory_entry_information
	{
		std::string operator()(const std::experimental::filesystem::directory_entry& entry) const
		{
			if (std::experimental::filesystem::is_directory(entry))
			{
				return entry.path().filename().replace_extension(".dir").string();
			}
			else if (entry.path().filename().string().find(" ")|| entry.path().stem().string().find(".") || entry.path().parent_path().string().find(" "))
			{
				auto filePath = entry.path().parent_path().string();
				if (filePath == "")
				{
					filePath = "Root";
				}
				if (entry.path().parent_path().string().find(" "))
				{
					for (auto& i : filePath)
					{
						if (i == ' ')
						{
							i = '_';
						}
					}
				}
				auto nameOfFile = entry.path().stem().string();
				for (auto& i : nameOfFile)
				{
					if (i == ' ')
					{
						i = '_';
					}						
					if(i == '.')
					{
						i = '_';
					}
				}
				nameOfFile = nameOfFile + entry.path().extension().string();
				return nameOfFile + " " + std::to_string(std::experimental::filesystem::file_size(entry)) + "bytes" + " " + filePath;
			}
			else
			{
				return entry.path().filename().string() + " " + std::to_string(std::experimental::filesystem::file_size(entry)) + "bytes" + " " + entry.path().parent_path().string();
			}
		}
	};
	void removeFilebyExtensionFromVector(std::vector<std::string>& vectorOfStrings, const std::string &extension);
	std::vector<std::string> returnStringStreamVector(std::string stringToVector);
	bool equalFileContent(const std::string& pathOfFileA, const std::string& pathOfFileB);
	std::ifstream::pos_type filesize(const std::string& filename);

public:
	std::vector<std::string> findAllFilesInDirectory(std::vector<std::string>& vectorOfStrings, std::string const& directory);
	void removeUniqueFilesFromVector(std::vector<std::string>& vectorOfStrings);
	void outputFilesAndDirectories(std::vector<std::string>& vectorOfStrings);

};