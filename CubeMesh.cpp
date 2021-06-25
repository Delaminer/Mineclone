#include"CubeMesh.h"
#include<iostream>
CubeMesh::CubeMesh(Texture& texture, int x, int z) : chunk(x, z), texture(texture)
{
	CubeMesh::texture = texture;

	Out o = chunk.GenerateVertices(x, z);
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

void CubeMesh::Draw(Shader& shader, Camera& camera)
{

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