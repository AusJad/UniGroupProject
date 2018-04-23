#include "Mesh.h"



Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}



void Mesh::setVertices(aiMesh *mesh)
{
	if (mesh->HasPositions())
	{
		for (unsigned i = 0; i < mesh->mNumVertices; i++)
		{
			Vertices.push_back(vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));
		}
	}
}

void Mesh::setIndexes(aiMesh *mesh)
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

void Mesh::setNormals(aiMesh *mesh)
{
	if (mesh->HasNormals())
	{
		for (unsigned i = 0; i < mesh->mNumVertices; i++)
		{
			Normals.push_back(vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
		}
	}
}


void Mesh::setTexCoords(aiMesh *mesh)
{
	if (mesh->HasTextureCoords(0))
	{
		for (unsigned i = 0; i < mesh->mNumVertices; i++)
		{
			texCoords.push_back(vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y));
		}
	}
}