#ifndef CUBE_MESH_CLASS_H
#define CUBE_MESH_CLASS_H

#include<string>

#include"VAO.h"
#include"EBO.h"
#include"Camera.h"
#include"Texture.h"
#include"Chunk.h"

class CubeMesh
{
public:
	std::vector<VE> vertices;
	std::vector<GLuint> indices;
	Texture texture;

	VAO VAO;
	Chunk chunk;

	CubeMesh(Texture& texture, int x, int z);
	CubeMesh();
	void GenerateVertices();
	void Draw(Shader& shader, Camera& camera);
};

#endif