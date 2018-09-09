#include "ImportModel.h"

ImportModel::ImportModel() : scale(1,1,1){
	model = NULL;
}

ImportModel::ImportModel(const ImportModel & tocpy)
{
	minx = tocpy.minx;
	maxx = tocpy.maxx;
	minz = tocpy.minz;
	maxz = tocpy.maxz;
	miny = tocpy.miny;
	maxy = tocpy.maxy;

	scale = tocpy.scale;

	modelDetails = tocpy.modelDetails;
	allVerticies = tocpy.allVerticies;

	model = tocpy.model;
	id = tocpy.id;

	displayListIDs = tocpy.displayListIDs;
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
	int totalTextures = 0;
	if (model->HasMaterials()) {
		for (unsigned i = 0; i < model->mNumMaterials; i++)
		{
			if (model->mMaterials[i]->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
				if (model->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
				{
					texture.push_back(RandomString(25));
					totalTextures++;
					if (Singleton<TextureManager>::getInstance()->loadNewTexture(path.data, "TGA", texture[i], Singleton<RenderModuleStubb>::getInstance()) == false) {
						texture[i].clear();
						totalTextures--;
					}
				}
			}

		}
	}

	ModelMesh tempMesh;
	for (unsigned i = 0; i < model->mNumMeshes; i++)
	{
		tempMesh.setVerticies(model->mMeshes[i]);
		tempMesh.setTexCoords(model->mMeshes[i]);
		tempMesh.setNormals(model->mMeshes[i]);
		tempMesh.setIndexes(model->mMeshes[i]);
		if ((unsigned) totalTextures > i)
			tempMesh.texture = texture[i];
		else
			tempMesh.texture.clear();

		modelDetails.push_back(tempMesh);
		tempMesh.vertIndex.clear();
		tempMesh.Verticies.clear();
		tempMesh.texCoords.clear();
		tempMesh.Normals.clear();

	}

	//using this for the getverticies function. can probably move this to the above for loop using tempMesh.Verticies after they're set.
	for (unsigned i = 0; i < modelDetails.size(); i++)
	{
		for (unsigned j = 0; j < modelDetails[i].Verticies.size(); j++)
		{
			allVerticies.push_back(modelDetails[i].Verticies[j]);
		}
	}

	setMinsAndMaxs();

	importer.FreeScene();
	
	for(unsigned i = 0; i < modelDetails.size(); i++) displayListIDs.push_back(RandomString(50));

	return(true);
}

void ImportModel::setMinsAndMaxs()
{

	for (unsigned j = 0; j < modelDetails.size(); j++)
	{
		minx = modelDetails[j].Verticies.at(0).x();
		minz = modelDetails[j].Verticies.at(0).z();
		maxx = modelDetails[j].Verticies.at(0).x();
		maxz = modelDetails[j].Verticies.at(0).z();
		maxy = modelDetails[j].Verticies.at(0).y();
		miny = modelDetails[j].Verticies.at(0).y();

		for (unsigned i = 0; i < modelDetails[j].Verticies.size(); i++)
		{
			if (minx > modelDetails[j].Verticies.at(i).x())
			{
				minx = modelDetails[j].Verticies.at(i).x();
			}
			if (miny > modelDetails[j].Verticies.at(i).y())
			{
				miny = modelDetails[j].Verticies.at(i).y();
			}
			if (minz > modelDetails[j].Verticies.at(i).z())
			{
				minz = modelDetails[j].Verticies.at(i).z();
			}
			if (maxx < modelDetails[j].Verticies.at(i).x())
			{
				maxx = modelDetails[j].Verticies.at(i).x();
			}

			if (maxy < modelDetails[j].Verticies.at(i).y())
			{
				maxy = modelDetails[j].Verticies.at(i).y();
			}
			if (maxz < modelDetails[j].Verticies.at(i).z())
			{
				maxz = modelDetails[j].Verticies.at(i).z();
			}
		}

	}

	minx *= scale.x();
	minz *= scale.z();
	maxx *= scale.x();
	maxz *= scale.z();
	maxy *= scale.y();
	miny *= scale.y();

}

std::vector<vec3> ImportModel::computeMMax() {
	std::vector<vec3> ret;

	float mminx, mminy, mminz, mmaxx, mmaxy, mmaxz;

	mminx = modelDetails[0].Verticies.at(0).x();
	mminz = modelDetails[0].Verticies.at(0).z();
	mmaxx = modelDetails[0].Verticies.at(0).x();
	mmaxz = modelDetails[0].Verticies.at(0).z();
	mmaxy = modelDetails[0].Verticies.at(0).y();
	mminy = modelDetails[0].Verticies.at(0).y();

	for (unsigned j = 0; j < modelDetails.size(); j++)
	{

		for (unsigned i = 0; i < modelDetails[j].Verticies.size(); i++)
		{
			if (mminx > modelDetails[j].Verticies.at(i).x())
			{
				mminx = modelDetails[j].Verticies.at(i).x();
			}
			if (mminy > modelDetails[j].Verticies.at(i).y())
			{
				mminy = modelDetails[j].Verticies.at(i).y();
			}
			if (mminz > modelDetails[j].Verticies.at(i).z())
			{
				mminz = modelDetails[j].Verticies.at(i).z();
			}
			if (mmaxx < modelDetails[j].Verticies.at(i).x())
			{
				mmaxx = modelDetails[j].Verticies.at(i).x();
			}

			if (mmaxy < modelDetails[j].Verticies.at(i).y())
			{
				mmaxy = modelDetails[j].Verticies.at(i).y();
			}
			if (mmaxz < modelDetails[j].Verticies.at(i).z())
			{
				mmaxz = modelDetails[j].Verticies.at(i).z();
			}
		}

	}

	mminx *= scale.x();
	mminz *= scale.z();
	mmaxx *= scale.x();
	mmaxz *= scale.z();
	mmaxy *= scale.y();
	mminy *= scale.y();

	ret.push_back(vec3(mminx, mminy, mminz));
	ret.push_back(vec3(mmaxx, mmaxy, mmaxz));

	return ret;
}

ImportModel* ImportModel::create() const
{
	return new ImportModel(*this);
}

std::vector<vec3>& ImportModel::getVerticies() {
	return allVerticies; //currently just returns the Verticies of all the meshes
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

		for (unsigned i = 0; i < modelDetails[j].Verticies.size(); i++)
		{
			modelDetails[j].Verticies.at(i).sx(modelDetails[j].Verticies.at(i).x() - difx);
			modelDetails[j].Verticies.at(i).sy(modelDetails[j].Verticies.at(i).y() - dify);
			modelDetails[j].Verticies.at(i).sz(modelDetails[j].Verticies.at(i).z() - difz);
		}

		setMinsAndMaxs();
	}
}

void ImportModel::setScale(vec3 & toset) {
	scale = toset;

	setMinsAndMaxs();
}

void ImportModel::update(float time)
{
}

void ImportModel::render(const vec3 & transmat)
{
	lasttrans = vec3(-1 * ((maxx + minx) / 2 - transmat.x()), -1 * ((maxy + miny) / 2 - transmat.y()), -1 * ((maxz + minz) / 2 - transmat.z()));

	for (unsigned i = 0; i < modelDetails.size(); i++)
	{
		if (!RNDR->hasList(displayListIDs.at(i))) {
			RNDR->beginCreateDisplayList(displayListIDs.at(i));
				if (modelDetails[i].Normals.empty())
					Singleton<RenderModuleStubb>::getInstance()->renderArrayTri(modelDetails[i].vertIndex, modelDetails[i].Verticies, modelDetails[i].texCoords, vec3(0, 0, 0));
				else
					Singleton<RenderModuleStubb>::getInstance()->renderArrayTri(modelDetails[i].vertIndex, modelDetails[i].Verticies, modelDetails[i].Normals, modelDetails[i].texCoords, vec3(0, 0, 0));
			RNDR->endCreateDisplayList();
		}

		if (modelDetails[i].texture.empty() == false)
				Singleton<TextureManager>::getInstance()->useTexture(modelDetails[i].texture, Singleton<RenderModuleStubb>::getInstance());
		RNDR->callList(displayListIDs.at(i));
		Singleton<TextureManager>::getInstance()->disableTexture(Singleton<RenderModuleStubb>::getInstance());
	}

	Singleton<TextureManager>::getInstance()->disableTexture(Singleton<RenderModuleStubb>::getInstance());
}

std::string ImportModel::RandomString(unsigned len) {
	std::string tmp;

	for (unsigned i = 0; i < len; ++i) {
		tmp.push_back((char)97 + (rand() % static_cast<int>(122 - 97 + 1)));
	}

	return tmp;
}