#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

#include <map>
#include <vector>
#include"Texture.h"
#include"CubeMesh.h"

class World
{
	public:

		Texture texture;

		std::map<int, std::map<int, CubeMesh>> chunks;
		std::vector<CubeMesh> achunks;
		//std::map<int, CubeMesh> chunks;
		World(Texture& texture);
		void AddChunk(int x, int z);
		void Draw(Shader& shader, Camera& camera);
};

#endif