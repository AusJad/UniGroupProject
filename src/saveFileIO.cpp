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

void save::saveGame(int sceneno)
{
	// Set scene number to string and store this is a varaible defined in save() because opening and closing the file constantly seems inefficient 
	// and the 2nd saveGame() function is normally called after and if it isnt then we dont want to save this data to file anyway.
	tmpsceneno = std::to_string(sceneno);
	tmpsceneno.append(";");
}

void save::saveGame(int state, vec3 pos, vec3 target, vec3 targetlook, Identifiers id)
{
	std::ofstream ofile;

	ofile.open(savePath, std::ofstream::app);

	ofile
		<< tmpsceneno
		<< state << ","
		<< pos[0] << "," << pos[1] << "," << pos[2] << ","
		<< target[0] << "," << target[1] << "," << target[2] << ","
		<< targetlook[0] << "," << targetlook[1] << "," << targetlook[2] << ","
		<< id.getId() << "," << id.getType() << "," << id.getName()
		<< std::endl;

	ofile.close();
	//std::cout << "SAVE - saveGame: Object saved to file." << std::endl;

}

bool save::loadFile()
{
	// Read in all files in directory.
	std::vector<std::string> allfiles = fileNameReader::getFileNames(directory, fileType);
	
	for (int i = 0; i < allfiles.size(); i++)
	{
		if (allfiles[i] == savePath) // If a file in the directory vector matches the name of the savePath
		{
			std::cout << "SAVE: Save found." << std::endl;
			openFile();
			return true;
		}
	}
	std::cout << "SAVE: Game failed to load." << std::endl;
	return false;
}

void save::openFile()
{
	std::ifstream rfile(savePath);
	std::string tmp;
	goData tempdata;

	if (!rfile)
	{
		std::cout << "SAVE: BAD READ FROM: " << savePath << std::endl;
	}
	else
	{
		//std::cout << "SAVE - openFile: Loading data." << std::endl;
		while (getline(rfile, tmp, ';'))
		{
			tempdata.sceneno = atoi(tmp.c_str());

			getline(rfile, tmp, ',');
			tempdata.state = atoi(tmp.c_str());

			getline(rfile, tmp, ',');
			tempdata.position[0] = atof(tmp.c_str());

			getline(rfile, tmp, ',');
			tempdata.position[1] = atof(tmp.c_str());

			getline(rfile, tmp, ',');
			tempdata.position[2] = atof(tmp.c_str());

			getline(rfile, tmp, ',');
			tempdata.targetPos[0] = atof(tmp.c_str());

			getline(rfile, tmp, ',');
			tempdata.targetPos[1] = atof(tmp.c_str());

			getline(rfile, tmp, ',');
			tempdata.targetPos[2] = atof(tmp.c_str());

			getline(rfile, tmp, ',');
			tempdata.targetLook[0] = atof(tmp.c_str());

			getline(rfile, tmp, ',');
			tempdata.targetLook[1] = atof(tmp.c_str());

			getline(rfile, tmp, ',');
			tempdata.targetLook[2] = atof(tmp.c_str());

			getline(rfile, tmp, ',');
			tempdata.id.setId(atoi(tmp.c_str()));

			getline(rfile, tmp, ',');
			tempdata.id.setType(tmp);

			getline(rfile, tmp);
			tempdata.id.setName(tmp);

			d.push_back(tempdata);
			//std::cout << "SAVE - openFile: Object found..." << std::endl;
		}
	}
}

std::vector<goData> save::getData() const
{
	return d;
}