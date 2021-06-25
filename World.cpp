#include"World.h"
#include<map>

World::World(Texture& texture) : texture(texture)
{
	World::texture = texture;
}

void World::AddChunk(int x, int z)
{
	//CubeMesh newChunk(texture, x, z);
	//achunks[x * 4 + z] = newChunk;
	achunks.push_back(CubeMesh(texture, x, z));
	/*
	if (chunks.count(x) > 0)
	{
		std::map<int, CubeMesh> row = chunks[x];

		if (row.count(z) > 0)
		{
			//All good
		}
		else
		{
			//Row exists, but individual chunk doesn't.
			std::cout << "added chunk " << z << " in " << x << std::endl;

			CubeMesh newChunk(texture, x, z);
			row.insert(std::make_pair(z, newChunk));
			//row[z] = newChunk;
		}
	}
	else
	{
		//Make a whole new row
		std::cout << "added row " << x << std::endl;
		std::map<int, CubeMesh> newRow;

		CubeMesh newChunk(texture, x, z);
		newRow.insert(std::make_pair(z, newChunk));

		chunks.insert(std::make_pair(x, newRow));
	}
	*/
}

void World::Draw(Shader& shader, Camera& camera)
{
	//for (const auto& [x, row] : chunks) {
	//	for (const auto& [z, chunk] : row) {
	//		//cout << "[" << key << "," << value << "]\n";
	//	}
	//}
	for (CubeMesh n : achunks)
	{
		n.Draw(shader, camera);
	}
	for (auto& x : chunks)
	{
		for (auto& z : x.second)
		{
			//z.second.Draw(shader, camera);
		}
	}
}