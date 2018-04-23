#pragma once
#include <Assimp/mesh.h>
#include <vector>
#include "Maths.h"


class Mesh
{
public:
	Mesh();
	~Mesh();

	/**
	* @brief Set the vertices.
	*
	* @param mesh - The Mesh.
	*/
	void setVertices(aiMesh *mesh);

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
	std::vector<vec3> Vertices;
	/// Vector for the texture coords.
	std::vector<vec2> texCoords;
	/// Vector for the normals.
	std::vector<vec3> Normals;
	/// Vector for the indexies
	std::vector<unsigned> vertIndex;
};

