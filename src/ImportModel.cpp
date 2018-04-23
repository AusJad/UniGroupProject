#include "ImportModel.h"

ImportModel::ImportModel()
{
}

ImportModel::ImportModel(const ImportModel & tocpy)
{
	minx = tocpy.minx;
	maxx = tocpy.maxx;
	minz = tocpy.minz;
	maxz = tocpy.maxz;
	miny = tocpy.miny;
	maxy = tocpy.maxy;
	
	modelDetails = tocpy.modelDetails;
	model = tocpy.model;
	id = tocpy.id;
}
ImportModel::~ImportModel()
{
}

bool ImportModel::loadModel(std::string filename)
{
	Assimp::Importer importer;

	model = importer.ReadFile(filename, aiProcessPreset_TargetRealtime_MaxQuality); 

	if (!model)
	{
		return false;
	}

	aiString path;

	if (model->HasMaterials()) {

		for (unsigned i = 0; i < model->mNumMaterials; i++)
		{
			if (model->mMaterials[i]->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
				if (model->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
				{
					texture = RandomString(25);
					if (Singleton<TextureManager>::getInstance()->loadNewTexture(path.data, "TGA", texture, Singleton<RenderModuleStubb>::getInstance()) == false) {
						texture.clear();
					}
				}
			}
		}
	}

	Mesh tempMesh;
	for (unsigned i = 0; i < model->mNumMeshes; i++)
	{
		tempMesh.setVertices(model->mMeshes[i]);
		tempMesh.setTexCoords(model->mMeshes[i]);
		tempMesh.setNormals(model->mMeshes[i]);
		tempMesh.setIndexes(model->mMeshes[i]);

		modelDetails.push_back(tempMesh);

	}

	setMinsAndMaxs();

	return(true);
}

void ImportModel::setMinsAndMaxs()
{
	for (unsigned j = 0; j < modelDetails.size(); j++)
	{
		minx = modelDetails[j].Vertices.at(0).x();
		minz = modelDetails[j].Vertices.at(0).z();
		maxx = modelDetails[j].Vertices.at(0).x();
		maxz = modelDetails[j].Vertices.at(0).z();
		maxy = modelDetails[j].Vertices.at(0).y();
		miny = modelDetails[j].Vertices.at(0).y();

		for (unsigned i = 0; i < modelDetails[j].Vertices.size(); i++)
		{
			if (minx > modelDetails[j].Vertices.at(i).x())
			{
				minx = modelDetails[j].Vertices.at(i).x();
			}
			if (miny > modelDetails[j].Vertices.at(i).y())
			{
				miny = modelDetails[j].Vertices.at(i).y();
			}
			if (minz > modelDetails[j].Vertices.at(i).z())
			{
				minz = modelDetails[j].Vertices.at(i).z();
			}
			if (maxx < modelDetails[j].Vertices.at(i).x())
			{
				maxx = modelDetails[j].Vertices.at(i).x();
			}

			if (maxy < modelDetails[j].Vertices.at(i).y())
			{
				maxy = modelDetails[j].Vertices.at(i).y();
			}
			if (maxz < modelDetails[j].Vertices.at(i).z())
			{
				maxz = modelDetails[j].Vertices.at(i).z();
			}
		}


	}

}

ImportModel* ImportModel::create() const
{
	return new ImportModel(*this);
}

std::vector<vec3>& ImportModel::getVerticies() {
	return modelDetails[0].Vertices; //currently just returns the vertices of the first mesh, probably need to change this somehow.
}


void ImportModel::centerOnPoint(vec3 & point)
{
	for (unsigned j = 0; j < modelDetails.size(); j++)
	{
		setMinsAndMaxs();
		float centerx = (maxx + minx) / 2;
		float centerz = (maxz + minz) / 2;
		float centery = (maxy + miny) / 2;

		float difx = centerx - point.x();
		float difz = centerz - point.z();
		float dify = centery - point.y();

		for (unsigned i = 0; i < modelDetails[j].Vertices.size(); i++)
		{
			modelDetails[j].Vertices.at(i).sx(modelDetails[j].Vertices.at(i).x() - difx);
			modelDetails[j].Vertices.at(i).sy(modelDetails[j].Vertices.at(i).y() - dify);
			modelDetails[j].Vertices.at(i).sz(modelDetails[j].Vertices.at(i).z() - difz);
		}

		setMinsAndMaxs();
	}
}

void ImportModel::setScale(vec3 & toset) {
	for (unsigned j = 0; j < modelDetails.size(); j++)
	{
		for (unsigned i = 0; i <  modelDetails[j].Vertices.size(); i++)
		{
			modelDetails[j].Vertices.at(i).sx(modelDetails[j].Vertices.at(i).x() * toset.x());
			modelDetails[j].Vertices.at(i).sy(modelDetails[j].Vertices.at(i).y() * toset.y());
			modelDetails[j].Vertices.at(i).sz(modelDetails[j].Vertices.at(i).z() * toset.z());
		}
	}

	setMinsAndMaxs();
}

void ImportModel::update()
{
}

void ImportModel::render(const vec3 & transmat)
{
	vec3 trans(-1 * ((maxx + minx) / 2 - transmat.x()), -1 * ((maxy + miny) / 2 - transmat.y()), -1 * ((maxz + minz) / 2 - transmat.z()));
	
	for (unsigned i = 0; i < modelDetails.size(); i++)
	{
		if (!texture.empty())
			Singleton<TextureManager>::getInstance()->useTexture(texture, Singleton<RenderModuleStubb>::getInstance());
		if (modelDetails[i].Normals.empty())
			Singleton<RenderModuleStubb>::getInstance()->renderArrayTri(modelDetails[i].vertIndex, modelDetails[i].Vertices, modelDetails[i].texCoords, trans);
		else
			Singleton<RenderModuleStubb>::getInstance()->renderArrayTri(modelDetails[i].vertIndex, modelDetails[i].Vertices, modelDetails[i].Normals, modelDetails[i].texCoords, trans);
		Singleton<TextureManager>::getInstance()->disableTexture(Singleton<RenderModuleStubb>::getInstance());
	}
}

std::string ImportModel::RandomString(unsigned len) {
	std::string tmp;

	for (unsigned i = 0; i < len; ++i) {
		tmp.push_back((char)97 + (rand() % static_cast<int>(122 - 97 + 1)));
	}

	return tmp;
}