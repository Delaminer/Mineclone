#include"Mesh.h"
#include"CubeMesh.h"
#include"World.h"

const unsigned int width = 800;
const unsigned int height = 800;

Vertex plane_vertices[] =
{
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

GLuint plane_indices[] =
{
	0, 1, 2,
	0, 2, 3,
};

Vertex lightVertices[] =
{
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7,
};

int main()
{
	//Initialize GLFW
	glfwInit();

	//Set OpenGL version and compatability mode
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	//Create a window
	GLFWwindow* window = glfwCreateWindow(width, height, "Sample Game", NULL, NULL);
	//If the window was unable to be created, return an error
	if (window == NULL)
	{
		std::cout << "Failed to create window." << std::endl;
		glfwTerminate();
		return -1;
	}
	//Set the context to the current window
	glfwMakeContextCurrent(window);

	//Load OpenGL
	gladLoadGL();

	//Set the viewport dimensions
	glViewport(0, 0, width, height);

	Texture textures[]
	{
		Texture("Assets/sample1.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("Assets/planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE),
	};

	Shader shaderProgram("defaultSimple.vert", "defaultSimple.frag");

	std::vector<Vertex> verts(plane_vertices, plane_vertices + sizeof(plane_vertices) / sizeof(Vertex));
	std::vector<GLuint> ind(plane_indices, plane_indices + sizeof(plane_indices) / sizeof(GLuint));
	std::vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	//Mesh floor(verts, ind, tex);

	Shader lightShader("light.vert", "light.frag");
	std::vector<Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector<GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	//Mesh light(lightVerts, lightInd, tex);

	Shader blockShader("block.vert", "block.frag");

	Texture s("Assets/blocks.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE);
	World world(s);
	//world.AddChunk(0, 0);
	for (int x = 0; x < 10; x++)
	{
		for (int z = 0; z < 10; z++)
		{
			world.AddChunk(x, z);
		}
	}

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	
	glEnable(GL_DEPTH_TEST);

	//Cull back faces for performance improvements (because you never see the back anyway :P)
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

	Camera camera(width, height, glm::vec3(Chunk::CHUNK_WIDTH / 2, Chunk::CHUNK_HEIGHT, Chunk::CHUNK_WIDTH / 2));

	//Timing stuff to display FPS
	double prevTime = 0.0;
	double crntTime = 0.0;
	double timeDiff;
	unsigned int counter = 0;

	//Disable VSync (not necessary)
	//glfwSwapInterval(0);

	//While the window is meant to be open, loop through this
	while (!glfwWindowShouldClose(window))
	{
		crntTime = glfwGetTime();
		timeDiff = crntTime - prevTime;
		counter++;
		if (timeDiff >= 1.0 / 30.0)
		{
			std::string FPS = std::to_string((1.0 / timeDiff) * counter);
			std::string ms = std::to_string((timeDiff / counter) * 1000);
			std::string title = "Mineclone TheGame - " + FPS + "FPS / " + ms + "ms";
			glfwSetWindowTitle(window, title.c_str());
			prevTime = crntTime;
			counter = 0;
		}

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		//floor.Draw(shaderProgram, camera);
		//light.Draw(lightShader, camera);
		world.Draw(blockShader, camera);

		glfwSwapBuffers(window);


		//Check if an event occurred (like the close button is clicked)
		glfwPollEvents();
	}

	shaderProgram.Delete();
	lightShader.Delete();

	//Destroy the window and stop OpenGL/GLFW
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}