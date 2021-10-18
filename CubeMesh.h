#ifndef CUBE_MESH_CLASS_H
#define CUBE_MESH_CLASS_H

#include"VAO.h"
#include"EBO.h"
#include"Camera.h"
#include"Texture.h"
#include"Chunk.h"

class CubeMesh
{
	public:
		VAO VAO;
		Chunk chunk;

		CubeMesh(Texture& texture, int chunkX, int chunkZ);

		void Load();

		void Draw(Shader& shader, Camera& camera);

		bool loaded = false;
		int chunkX;
		int chunkZ;
	private:
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		Texture texture;
};

#endif