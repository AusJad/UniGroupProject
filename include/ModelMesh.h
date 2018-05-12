#pragma once
#include <Assimp/mesh.h>
#include <vector>
#include "Maths.h"


class ModelMesh
{
public:
	ModelMesh();
	~ModelMesh();

	/**
	* @brief Set the vertices.
	*
	* @param mesh - The Mesh.
	*/
	void setVerticies(aiMesh *mesh);

	/**
	* @brief Set the texture coords.
	*
	* @param mesh - The Mesh.
	*/
	void setTexCoords(aiMesh *mesh);

	/**
	* @brief Set the normals.
	*
	* @param mesh - The Mesh.
	*/
	void setNormals(aiMesh *mesh);

	/**
	* @brief Set the indexies.
	*
	* @param mesh - The Mesh.
	*/
	void setIndexes(aiMesh *mesh);

	/// Vector for the verticies.
	std::vector<vec3> Verticies;
	/// Vector for the texture coords.
	std::vector<vec2> texCoords;
	/// Vector for the normals.
	std::vector<vec3> Normals;
	/// Vector for the indexies
	std::vector<unsigned> vertIndex;

	std::string texture;
};

