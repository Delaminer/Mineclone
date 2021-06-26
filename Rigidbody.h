#ifndef RIGIDBODY_CLASS_H
#define RIGIDBODY_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>


class Rigidbody
{
	public:
		glm::vec3 Position;
		glm::vec3 Velocity;
		bool ground = true;

		Rigidbody(glm::vec3 pos);
		void Process(float dt, float groundLevel);

		const glm::vec3 GRAVITY = glm::vec3(0.0f, -9.8f, 0.0f);
};

#endif