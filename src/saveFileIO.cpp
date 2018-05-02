#include "saveFileIO.h"

save::save()
{

}

save::save(string fn)
{
	filename = fn;
	savePath = directory;
	savePath.append(filename);
	savePath.append(fileType);
}

save::~save()
{

}

void save::saveGame(int sceneno)
{
	// create file of filename
	// open file
	// deposit sceneno;
	// close file

	ofstream ofile;

	ofile.open(savePath);

	ofile << sceneno << ";";

	ofile.close();
}

void save::saveGame(int state, vec3 pos, vec3 target, vec3 targetlook, Identifiers id)
{
	// open file
	// deposit state,pos[0],pos[1],pos[2],.....,id.getId(), id.getName, id.getType(), id.getName(), id.getObjectName() endl

	ofstream ofile;

	ofile.open(savePath);

	ofile
		<< state << ","
		<< pos[0] << "," << pos[1] << "," << pos[2] << ","
		<< target[0] << "," << target[1] << "," << target[2] << ","
		<< targetlook[0] << "," << targetlook[1] << "," << targetlook[2] << ","
		<< id.getId() << "," << id.getType() << "," << id.getName() << "," << id.getObjectname()
		<< endl;

}

bool save::loadFile()
{
	vector<string> allfiles = fileNameReader::getFileNames(directory, fileType);
	
	for (int i = 0; i < allfiles.size(); i++)
	{
		if (allfiles[i] == savePath)
		{
			openFile(allfiles[i]);
			return true;
		}
	}
	return false;
}

void save::openFile(string fp)
{
	ifstream rfile(savePath);
	string tmp;
	goData tempdata;

	if (!rfile)
	{
		// bad read or no save data
	}
	else
	{
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

			getline(rfile, tmp, ',');
			tempdata.id.setName(tmp);

			getline(rfile, tmp);
			tempdata.id.setObjectname(tmp);

			d.push_back(tempdata);
		}
	}
}

vector<goData> save::getData() const
{
	return d;
}