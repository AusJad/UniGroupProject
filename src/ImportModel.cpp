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

	Vertices = tocpy.Vertices;
	texCoords = tocpy.texCoords;
	Normals = tocpy.Normals;
	vertIndex = tocpy.vertIndex;
	texture = tocpy.texture;
	
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

	for (unsigned i = 0; i < model->mNumMeshes; i++)
	{
		setVertices(model->mMeshes[i]);
		setTexCoords(model->mMeshes[i]);
		setNormals(model->mMeshes[i]);
		setIndexes(model->mMeshes[i]);
	}

	setMinsAndMaxs();

	return(true);
}

void ImportModel::setMinsAndMaxs()
{
	minx = Vertices.at(0).x();
	minz = Vertices.at(0).z();
	maxx = Vertices.at(0).x();
	maxz = Vertices.at(0).z();
	maxy = Vertices.at(0).y();
	miny = Vertices.at(0).y();

	for (unsigned i = 0; i < Vertices.size(); i++)
	{
		if (minx > Vertices.at(i).x())
		{
			minx = Vertices.at(i).x();
		}
		if (miny > Vertices.at(i).y())
		{
			miny = Vertices.at(i).y();
		}
		if (minz > Vertices.at(i).z())
		{
			minz = Vertices.at(i).z();
		}
		if (maxx < Vertices.at(i).x())
		{
			maxx = Vertices.at(i).x();
		}

		if (maxy < Vertices.at(i).y())
		{
			maxy = Vertices.at(i).y();
		}
		if (maxz < Vertices.at(i).z())
		{
			maxz = Vertices.at(i).z();
		}


	}

}

ImportModel* ImportModel::create() const
{
	return new ImportModel(*this);
}

std::vector<vec3>& ImportModel::getVerticies() {
	return Vertices;
}

void ImportModel::setVertices(aiMesh *mesh)
{
	if (mesh->HasPositions())
	{
		for (unsigned i = 0; i < mesh->mNumVertices; i++)
		{
			Vertices.push_back(vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));
		}
	}
}

void ImportModel::setIndexes(aiMesh *mesh)
{
	int indexStart = 0;
	if (mesh->HasFaces())
	{
		for (unsigned i = 0; i < mesh->mNumFaces; i++)
		{

			vertIndex.push_back(mesh->mFaces[i].mIndices[0]);
			vertIndex.push_back(mesh->mFaces[i].mIndices[1]);
			vertIndex.push_back(mesh->mFaces[i].mIndices[2]);

		}
	}
}

void ImportModel::setNormals(aiMesh *mesh)
{
	if (mesh->HasNormals())
	{
		for (unsigned i = 0; i < mesh->mNumVertices; i++)
		{
			Normals.push_back(vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
		}
	}
}


void ImportModel::setTexCoords(aiMesh *mesh)
{
	if (mesh->HasTextureCoords(0))
	{
		for (unsigned i = 0; i < mesh->mNumVertices; i++)
		{
			texCoords.push_back(vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y));
		}
	}
}

void ImportModel::centerOnPoint(vec3 & point)
{
	setMinsAndMaxs();
	float centerx = (maxx + minx) / 2;
	float centerz = (maxz + minz) / 2;
	float centery = (maxy + miny) / 2;

	float difx = centerx - point.x();
	float difz = centerz - point.z();
	float dify = centery - point.y();

	for (unsigned i = 0; i < Vertices.size(); i++)
	{
		Vertices.at(i).sx(Vertices.at(i).x() - difx);
		Vertices.at(i).sy(Vertices.at(i).y() - dify);
		Vertices.at(i).sz(Vertices.at(i).z() - difz);
	}

	setMinsAndMaxs();
}

void ImportModel::setScale(vec3 & toset) {
	for (unsigned i = 0; i < Vertices.size(); i++)
	{
		Vertices.at(i).sx(Vertices.at(i).x() * toset.x());
		Vertices.at(i).sy(Vertices.at(i).y() * toset.y());
		Vertices.at(i).sz(Vertices.at(i).z() * toset.z());
	}

	setMinsAndMaxs();
}

void ImportModel::update(float time)
{
}

void ImportModel::render(const vec3 & transmat)
{
	lasttrans = vec3(-1 * ((maxx + minx) / 2 - transmat.x()), -1 * ((maxy + miny) / 2 - transmat.y()), -1 * ((maxz + minz) / 2 - transmat.z()));

	if (texture.empty() == false) Singleton<TextureManager>::getInstance()->useTexture(texture, Singleton<RenderModuleStubb>::getInstance());
	if(Normals.empty())Singleton<RenderModuleStubb>::getInstance()->renderArrayTri(vertIndex,Vertices, texCoords, lasttrans);
	else Singleton<RenderModuleStubb>::getInstance()->renderArrayTri(vertIndex, Vertices, Normals, texCoords, lasttrans);
	Singleton<TextureManager>::getInstance()->disableTexture(Singleton<RenderModuleStubb>::getInstance());
}

std::string ImportModel::RandomString(unsigned len) {
	std::string tmp;

	for (unsigned i = 0; i < len; ++i) {
		tmp.push_back((char)97 + (rand() % static_cast<int>(122 - 97 + 1)));
	}

	return tmp;
}