#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glm/glm.hpp>
#include<glad/glad.h>
#include<vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

struct VE
{
	glm::vec3 position;
	glm::vec2 texUV;
};

class VBO
{
	public:
		GLuint ID;
		//VBO(std::vector<Vertex>& vertices);
		VBO(std::vector<VE>& vertices);

		void Bind();
		void Unbind();
		void Delete();
};

#endif