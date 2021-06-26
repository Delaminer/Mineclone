#include"World.h"
#include<map>

World::World(Texture& texture) : texture(texture)
{
	World::texture = texture;
}

void World::AddChunk(int x, int z)
{

	if (chunks.count(x) > 0)
	{
		if (chunks[x].count(z) == 0)
		{
			//Add to existing row
			CubeMesh* newChunk = new CubeMesh(texture, x, z);
			chunks[x].insert(std::make_pair(z, newChunk));
			//Add to the list of jobs
			toLoad.push_back(newChunk);
		}
	}
	else
	{
		//Make a whole new row
		std::map<int, CubeMesh*> newRow;
		CubeMesh* newChunk = new CubeMesh(texture, x, z);
		newRow.insert(std::make_pair(z, newChunk));
		chunks.insert(std::make_pair(x, newRow));
		//Add to the list of jobs
		toLoad.push_back(newChunk);
	}
	
}

std::map<int, std::map<int, CubeMesh*> >::iterator itr;
std::map<int, CubeMesh*>::iterator ptr;
void World::Draw(Shader& shader, Camera& camera)
{
	for (auto& x : chunks)
	{
		if (x.first <= chunkX + RENDER_DISTANCE && x.first >= chunkX - RENDER_DISTANCE)
		for (auto& z : x.second)
		{
			if (z.first <= chunkZ + RENDER_DISTANCE && z.first >= chunkZ - RENDER_DISTANCE)
			z.second->Draw(shader, camera);
		}
	}
}

void World::CheckForChunks(glm::vec3 position)
{
	//The player moved, so let's see if we have to add more chunks
	int newChunkX = (int)(position.x / Chunk::CHUNK_WIDTH);
	if (position.x < 0) newChunkX--;
	int newChunkZ = (int)(position.z / Chunk::CHUNK_WIDTH);
	if (position.z < 0) newChunkZ--;
	if (newChunkX != chunkX)
	{
		int edgeX = newChunkX + ((newChunkX > chunkX) ? RENDER_DISTANCE : -RENDER_DISTANCE);
		//Dang.
		for (int dz = -RENDER_DISTANCE; dz <= RENDER_DISTANCE; dz++)
		{
			//Add chunks!
			AddChunk(edgeX, chunkZ + dz);
		}
		chunkX = newChunkX;
	}
	if (newChunkZ != chunkZ)
	{
		int edgeZ = newChunkZ + ((newChunkZ > chunkZ) ? RENDER_DISTANCE : -RENDER_DISTANCE);
		//Dang.
		for (int dx = -RENDER_DISTANCE; dx <= RENDER_DISTANCE; dx++)
		{
			//Add chunks!
			AddChunk(chunkX + dx, edgeZ);
		}
		chunkZ = newChunkZ;
	}
}


//Converts 0,1,2,3,4,5 to 0,1,-1,2,-2,3,-3
int spread(int x)
{
	return (x + 1) / -2 * std::pow(-1, x);
}

void World::SetPosition(glm::vec3 position)
{
	//Assume this is the first action, so generate all surrounding chunks
	chunkX = (int)(position.x / Chunk::CHUNK_WIDTH);
	chunkZ = (int)(position.z / Chunk::CHUNK_WIDTH);

	//for (int dx = -RENDER_DISTANCE; dx <= RENDER_DISTANCE; dx++)
	for (int dx = 0; dx <= 2 * RENDER_DISTANCE; dx++)
	{
		//for (int dz = -RENDER_DISTANCE; dz <= RENDER_DISTANCE; dz++)
		for (int dz = 0; dz <= 2 * RENDER_DISTANCE; dz++)
		{
			AddChunk(chunkX + spread(2 * RENDER_DISTANCE - dx), chunkZ + spread(2 * RENDER_DISTANCE - dz));
		}
	}
}

void World::Job()
{
	if (toLoad.size() > 0)
	{
		CubeMesh* chunkToLoad = toLoad[toLoad.size() - 1];
		chunkToLoad->Load();
		toLoad.pop_back();
	}
}

int World::GetHeight(int x, int z)
{
	if (chunks.count(x/Chunk::CHUNK_WIDTH) > 0 && chunks[x/ Chunk::CHUNK_WIDTH].count(z / Chunk::CHUNK_WIDTH) > 0)
		return chunks[x / Chunk::CHUNK_WIDTH][z / Chunk::CHUNK_WIDTH]->chunk.GetHeight(x % Chunk::CHUNK_WIDTH, z % Chunk::CHUNK_HEIGHT);
	return -1;
}
int World::GetHeight(glm::vec3 position)
{
	return GetHeight(position.x, position.z);
}