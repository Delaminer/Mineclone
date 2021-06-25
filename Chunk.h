#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include"VAO.h"
#include"Perlin.h"

struct Out
{
	std::vector<VE> vertices;
	std::vector<GLuint> indices;
};

class Chunk
{
	public:
		static const unsigned char TEXTURE_ATLAS_WIDTH = 2;
		static const unsigned char CHUNK_WIDTH = 16;
		static const unsigned char CHUNK_HEIGHT = 16;
		static const bool DRAW_ALL_FACES = false;

		int blocks[CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT];
		Chunk(int x, int y);
		Out GenerateVertices(int chunkX, int chunkZ);

		static const int COORD_INDEX(int localX, int localY, int localZ);
		bool isABlock(int x, int y, int z);

		Perlin perlin;
};

#endif