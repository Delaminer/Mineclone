#include"Rigidbody.h"

Rigidbody::Rigidbody(glm::vec3 pos)
{
	Rigidbody::Position = pos;
	Rigidbody::Velocity = glm::vec3(0.0f, 0.0f, 0.0f);

}
void Rigidbody::Process(float dt, float groundLevel)
{
	Velocity += GRAVITY * dt;
	Position += Velocity * dt;
	float offset = 2.0f;
	if (Position.y - offset < groundLevel)
	{
		Velocity.y = 0.0f;
		Position.y = groundLevel + offset;
		ground = true;
	}
}