#include<iostream>
#include"Chunk.h"
#include <stdlib.h>
#include <time.h>
#include"Perlin.h"




Chunk::Chunk()
{

}

void Chunk::GenerateBlocks(int chunkX, int chunkZ)
{
	//Generate blocks
	for (int x = 0; x < CHUNK_WIDTH; x++)
	{
		for (int z = 0; z < CHUNK_WIDTH; z++)
		{
			//int height = (int)(CHUNK_HEIGHT * perlinNoise[x * CHUNK_WIDTH + z]);
			int scale = 10;
			int height = 4 + (int)(CHUNK_HEIGHT * perlin.ValueNoise_2D((chunkX * CHUNK_WIDTH + x) * scale, (chunkZ * CHUNK_WIDTH + z) * scale));
			for (int y = 0; y < CHUNK_HEIGHT; y++)
			{
				if (y == 0)
				{
					Chunk::blocks[COORD_INDEX(x, y, z)] = 4; //stone
				}
				else if (y == height)
				{
					Chunk::blocks[COORD_INDEX(x, y, z)] = 2; //grass
				}
				else if (y < height)
				{
					Chunk::blocks[COORD_INDEX(x, y, z)] = 1; //dirt
				}
				else
				{
					Chunk::blocks[COORD_INDEX(x, y, z)] = 0;
				}
			}
		}
	}
}

float map(float x, float in_min, float in_max, float out_min, float out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

glm::vec2 uv(glm::vec2 inUV, int x, int y)
{
	y = Chunk::TEXTURE_ATLAS_WIDTH - y - 1;

	float ux = (x + inUV.x) / Chunk::TEXTURE_ATLAS_WIDTH;
	float uy = (y + inUV.y) / Chunk::TEXTURE_ATLAS_WIDTH;

	return glm::vec2(ux, uy);
}

//Convert basic UVs to a texture atlas. ID is used to specify location right now, x,y coords are found in this function. (should use overloading)
glm::vec2 uv(glm::vec2 inUV, int id)
{
	//How many textures there are 
	int x, y;
	switch (id)
	{
	case 1:
		x = 0;
		y = 0;
		break;
	case 2:
		x = 1;
		y = 0;
		break;
	case 3:
		x = 1;
		y = 1;
		break;
	case 4:
		x = 0;
		y = 1;
		break;
	default:
		x = 0;
		y = 1;
	}
	return uv(inUV, x, y);
}

void getTextureCoords(int id, int* coords)
{
	switch (id)
	{
	case 1: //dirt
		for (int i = 0; i < 12; i++) coords[i] = 0;
		break;
	case 2: //grass
		//Sides
		for (int i = 2; i < 10; i++) coords[i] = 1;
		//Top
		coords[0] = 1;
		coords[1] = 0;
		//Bottom
		coords[10] = 0;
		coords[11] = 0;
		break;
	case 4: //stone
		for (int i = 0; i < 12; i += 2)
		{
			coords[i] = 0;
			coords[i + 1] = 1;
		}
		break;
	default: //stone
		for (int i = 0; i < 12; i += 2)
		{
			coords[i] = 0;
			coords[i + 1] = 1;
		}
	}
}

void generateUvSet(int id, glm::vec2* uvSet, glm::vec2* reference)
{
	//Make 24 UV coordinates
	int coordinates[12];
	getTextureCoords(id, coordinates); //Use ID to get coordinates of each block face in texture atlas

	//Use texture coordinates to form texture UVs
	for (int i = 0; i < 12; i += 2)
	{
		int x = coordinates[i];
		int y = coordinates[i + 1];
		uvSet[i * 2] = uv(reference[0], x, y);
		uvSet[i * 2 + 1] = uv(reference[1], x, y);
		uvSet[i * 2 + 2] = uv(reference[2], x, y);
		uvSet[i * 2 + 3] = uv(reference[3], x, y);
	}
}

ChunkGraphics Chunk::GenerateVertices(int chunkX, int chunkZ)
{
	Vertex referenceVertex[24] = {

		//Top
		Vertex{glm::vec3(0.0f, 1.0f,  1.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(1.0f, 1.0f,  1.0f), glm::vec2(1.0f, 0.0f)},
		//Front
		Vertex{glm::vec3(1.0f, 0.0f,  0.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(0.0f, 0.0f,  0.0f), glm::vec2(1.0f, 0.0f)},
		//Back
		Vertex{glm::vec3(0.0f, 0.0f,  1.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(1.0f, 0.0f,  1.0f), glm::vec2(1.0f, 0.0f)},
		//Left
		Vertex{glm::vec3(0.0f, 0.0f,  0.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(0.0f, 0.0f,  1.0f), glm::vec2(1.0f, 0.0f)},
		//Right
		Vertex{glm::vec3(1.0f, 0.0f,  1.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(1.0f, 0.0f,  0.0f), glm::vec2(1.0f, 0.0f)},
		//Bottom
		Vertex{glm::vec3(1.0f, 0.0f,  1.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(0.0f, 0.0f,  1.0f), glm::vec2(1.0f, 0.0f)},
	};

	GLuint referenceIndex[36] = {
		//Top
		0, 1, 2,
		0, 2, 3,

		//Front
		4, 5, 6,
		4, 6, 7,

		//Back
		8, 9, 10,
		8, 10, 11,

		//Left
		12, 13, 14,
		12, 14, 15,

		//Right
		16, 17, 18,
		16, 18, 19,

		//Bottom
		20, 21, 22,
		20, 22, 23,
	};

	glm::vec3 chunkOffset = glm::vec3(chunkX * CHUNK_WIDTH, 0, chunkZ * CHUNK_WIDTH);
	for (int i = 0; i < 24; i++)
	{
		referenceVertex[i].position = referenceVertex[i].position + chunkOffset;
	}

	glm::vec2 simpleUV[4] =
	{
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
	};

	std::vector<Vertex> tempV;
	std::vector<GLuint> tempI;
	for (int x = 0; x < CHUNK_WIDTH; x++)
	{
		for (int y = 0; y < CHUNK_HEIGHT; y++)
		{
			for (int z = 0; z < CHUNK_WIDTH; z++)
			{
				char block = Chunk::blocks[COORD_INDEX(x, y, z)];
				if (block != 0)
				{
					//Add vertex
					glm::vec3 position = glm::vec3(x * 1.0f, y * 1.0f, z * 1.0f);
					glm::vec2 uvSet[24];
					generateUvSet(block, uvSet, simpleUV);
					for (int i = 0; i < 24; i++)
					{
						//tempV.push_back(VE{ position + referenceVertex[i].position, uv(referenceVertex[i].texUV, block) });
						tempV.push_back(Vertex{ position + referenceVertex[i].position, uvSet[i] });
						
					}
					int offset = tempV.size() - 24;
					if (DRAW_ALL_FACES)
					{
						//Draw all faces
						for (int i = 0; i < 36; i++)
						{
							tempI.push_back(referenceIndex[i] + offset);
						}
					}
					else
					{
						//Only draw faces that are visible
						if (y == CHUNK_HEIGHT - 1 || !isABlock(x, y + 1, z))
						{
							//Draw top
							for (int i = 0; i < 6; i++)
							{
								tempI.push_back(referenceIndex[i] + offset);
							}
						}
						if (z == 0 || !isABlock(x, y, z - 1))
						{
							//Draw front
							for (int i = 6; i < 12; i++)
							{
								tempI.push_back(referenceIndex[i] + offset);
							}
						}
						if (z == CHUNK_WIDTH - 1 || !isABlock(x, y, z + 1))
						{
							//Draw back
							for (int i = 12; i < 18; i++)
							{
								tempI.push_back(referenceIndex[i] + offset);
							}
						}
						if (x == 0 || !isABlock(x - 1, y, z))
						{
							//Draw left
							for (int i = 18; i < 24; i++)
							{
								tempI.push_back(referenceIndex[i] + offset);
							}
						}
						if (x == CHUNK_WIDTH - 1 || !isABlock(x + 1, y, z))
						{
							//Draw right
							for (int i = 24; i < 30; i++)
							{
								tempI.push_back(referenceIndex[i] + offset);
							}
						}
						if (y == 0 || !isABlock(x, y - 1, z))
						{
							//Draw bottom
							for (int i = 30; i < 36; i++)
							{
								tempI.push_back(referenceIndex[i] + offset);
							}
						}
					}
				}
			}
		}
	}

	return ChunkGraphics{ tempV, tempI };
}
const int Chunk::COORD_INDEX(int localX, int localY, int localZ)
{
	return ((localY * CHUNK_WIDTH) + localZ) * CHUNK_WIDTH + localX;
}
bool Chunk::isABlock(int x, int y, int z)
{
	return blocks[COORD_INDEX(x, y, z)] != 0;
}