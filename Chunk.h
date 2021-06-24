#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include"VAO.h"

struct Out
{
	std::vector<VE> vertices;
	std::vector<GLuint> indices;
};

class Chunk
{
	public:
		static const unsigned char CHUNK_WIDTH = 32;
		static const unsigned char CHUNK_HEIGHT = 16;

		int blocks[CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT];
		Chunk(int x, int y);
		Out GenerateVertices();

		static const int COORD_INDEX(int localX, int localY, int localZ);
};

#endif