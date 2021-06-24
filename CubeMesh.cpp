#include"CubeMesh.h"
#include<iostream>
CubeMesh::CubeMesh(Texture& texture) : chunk(0, 0), texture(texture)
{
	CubeMesh::texture = texture;
	//chunk = Chunk(0, 3);
	//Chunk chunk(0, 0);

	CubeMesh::indices = {
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


		//Left
		/*
		0, 1, 5,
		0, 5, 4,

		//Right
		3, 2, 6,
		3, 6, 7,

		//Front -z
		1, 2, 6,
		1, 6, 5,

		//Back
		0, 3, 7,
		0, 7, 4,

		//Bottom
		4, 5, 6,
		4, 6, 7,
		*/
		
	};
	CubeMesh::vertices = {
		/*
		VE{glm::vec3(-1.0f, 1.0f,  1.0f), glm::vec2(0.0f, 0.0f)},
		VE{glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 1.0f)},
		VE{glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f)},
		VE{glm::vec3(1.0f, 1.0f,  1.0f), glm::vec2(1.0f, 0.0f)},

		VE{glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec2(0.0f, 0.0f)},
		VE{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 1.0f)},
		VE{glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 1.0f)},
		VE{glm::vec3(1.0f, -1.0f,  1.0f), glm::vec2(1.0f, 0.0f)},
		*/

		//New

		//Top
		VE{glm::vec3(-1.0f, 1.0f,  1.0f), glm::vec2(0.0f, 0.0f)},
		VE{glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 1.0f)},
		VE{glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f)},
		VE{glm::vec3(1.0f, 1.0f,  1.0f), glm::vec2(1.0f, 0.0f)},
		//Front
		VE{glm::vec3(1.0f, -1.0f,  -1.0f), glm::vec2(0.0f, 0.0f)},
		VE{glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 1.0f)},
		VE{glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f)},
		VE{glm::vec3(-1.0f, -1.0f,  -1.0f), glm::vec2(1.0f, 0.0f)},
		//Back
		VE{glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec2(0.0f, 0.0f)},
		VE{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
		VE{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
		VE{glm::vec3(1.0f, -1.0f,  1.0f), glm::vec2(1.0f, 0.0f)},
		//Left
		VE{glm::vec3(-1.0f, -1.0f,  -1.0f), glm::vec2(0.0f, 0.0f)},
		VE{glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 1.0f)},
		VE{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
		VE{glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec2(1.0f, 0.0f)},
		//Right
		VE{glm::vec3(1.0f, -1.0f,  1.0f), glm::vec2(0.0f, 0.0f)},
		VE{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
		VE{glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f)},
		VE{glm::vec3(1.0f, -1.0f,  -1.0f), glm::vec2(1.0f, 0.0f)},

		//Bottom
		VE{glm::vec3(1.0f, -1.0f,  1.0f), glm::vec2(0.0f, 0.0f)},
		VE{glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 1.0f)},
		VE{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 1.0f)},
		VE{glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec2(1.0f, 0.0f)},
	};

	Out o = chunk.GenerateVertices();
	CubeMesh::vertices = o.vertices;
	CubeMesh::indices = o.indices;
	
	VAO.Bind();

	VBO VBO(vertices);

	EBO EBO(indices);
	
	


	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(VE), (void*)0);
	VAO.LinkAttrib(VBO, 1, 2, GL_FLOAT, sizeof(VE), (void*)(3 * sizeof(float)));

	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();

}

void CubeMesh::GenerateVertices()
{

}

void CubeMesh::Draw(Shader& shader, Camera& camera)
{
	/*
	shader.Activate();
	VAO.Bind();

	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		std::string num;
		std::string type = textures[i].type;
		if (type == "diffuse")
		{
			num = std::to_string(numDiffuse++);
		}
		else if (type == "specular")
		{
			num = std::to_string(numSpecular++);
		}
		textures[i].texUnit(shader, (type + num).c_str(), i);
		textures[i].Bind();
	}

	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	*/

	shader.Activate();
	VAO.Bind();

	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	std::string num;
	std::string type = texture.type;
	if (type == "diffuse")
	{
		num = std::to_string(numDiffuse++);
	}
	else if (type == "specular")
	{
		num = std::to_string(numSpecular++);
	}
	texture.texUnit(shader, (type + num).c_str(), 0);
	texture.Bind();

	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}