#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include"VAO.h"
#include"Perlin.h"

struct ChunkGraphics
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
};

class Chunk
{
	public:
		static const unsigned char TEXTURE_ATLAS_WIDTH = 4;
		static const unsigned char CHUNK_WIDTH = 16;
		static const unsigned char CHUNK_HEIGHT = 16;
		static const bool DRAW_ALL_FACES = false;

		char blocks[CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT];
		Chunk();
		void GenerateBlocks(int chunkX, int chunkZ);
		ChunkGraphics GenerateVertices(int chunkX, int chunkZ);

		static const int COORD_INDEX(int localX, int localY, int localZ);
		bool isABlock(int x, int y, int z);

		Perlin perlin;
};

#endif