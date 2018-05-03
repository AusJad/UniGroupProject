#include "saveFileIO.h"

save::save()
{

}

save::save(std::string fn)
{
	// Set file name.
	filename = fn;

	// Set file path with file type for opening the file.
	savePath = directory;
	savePath.append(filename);
	savePath.append(fileType);

	// Create/wipe save file here as saveGame() appends to file and if we re-use existing name we have problems.
	/*
	std::ofstream ofile;
	ofile.open(savePath);
	ofile.close();
	*/
}

save::~save()
{

}

void save::saveGame(std::vector<std::string> data)
{
	std::ofstream ofile;
	ofile.open(savePath);
	for (int i = 0; i < data.size(); i++)
	{
		ofile << data[i] << std::endl;
	}
	ofile.close();
}

bool save::loadFile()
{
	std::ifstream rfile(savePath);
	std::string tmp;

	if (!rfile)
	{
		std::cout << "SAVE: BAD READ FROM: " << savePath << std::endl;
		return false;
	}
	else
	{
		while (getline(rfile, tmp))
		{
			d.push_back(tmp);
		}
	}

	return true;
}

std::vector<std::string> save::getData() const
{
	return d;
}