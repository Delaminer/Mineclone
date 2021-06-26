#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

#include<glad/glad.h>
#include <map>
#include <vector>
#include"Texture.h"
#include"CubeMesh.h"

class World
{
	public:
		const int RENDER_DISTANCE = 3;

		std::map<int, std::map<int, CubeMesh*>> chunks;
		World(Texture& texture);
		void AddChunk(int x, int z);
		void Draw(Shader& shader, Camera& camera);
		void CheckForChunks(glm::vec3 position);
		void SetPosition(glm::vec3 position);
		void Job();

		int GetHeight(int x, int z);
		int GetHeight(glm::vec3);

	private:

		Texture texture;
		int chunkX;
		int chunkZ;
		std::vector<CubeMesh*> toLoad;
};

#endif