#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Core/Shader.h"
#include "Core/Renderer.h"
#include <FastNoise/FastNoiseLite.h>

void GenerateChunk(const FastNoiseLite& noise, Renderer& renderer, float x, float y, float z)
{
	Chunk chunk(120);
	chunk.Position = glm::vec3(x, y, z);

	std::vector<glm::vec3> positions;

	int CHUNK_SIZE = 9*5;
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			for (int k = 0; k < CHUNK_SIZE; k++)
			{
				positions.push_back(glm::vec3(i, (int)((noise.GetNoise((float)i, (float)k)) * 20), k));
			}
		}
	}

	std::vector<glm::mat4> models;

	std::vector<glm::vec3> oldPositions;
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			for (int k = 0; k < CHUNK_SIZE; k++)
			{
				glm::vec3 position = glm::vec3(i, (int)((noise.GetNoise((float)i, (float)k)) * 20), k);

				bool right = (std::find(positions.begin(), positions.end(), glm::vec3(position.x + 1, position.y, position.z)) != positions.end()) ? false : true;
				bool left = (std::find(positions.begin(), positions.end(), glm::vec3(position.x - 1, position.y, position.z)) != positions.end()) ? false : true;
				bool top = (std::find(positions.begin(), positions.end(), glm::vec3(position.x, position.y + 1, position.z)) != positions.end()) ? false : true;
				bool bottom = (std::find(positions.begin(), positions.end(), glm::vec3(position.x, position.y - 1, position.z)) != positions.end()) ? false : true;
				bool back = (std::find(positions.begin(), positions.end(), glm::vec3(position.x, position.y, position.z - 1)) != positions.end()) ? false : true;
				bool front = (std::find(positions.begin(), positions.end(), glm::vec3(position.x, position.y, position.z + 1)) != positions.end()) ? false : true;

				if (std::find(oldPositions.begin(), oldPositions.end(), position) == oldPositions.end())
				{
					Cube cube(front, back, top, bottom, left, right);
					cube.Position = position;
					oldPositions.push_back(position);
					chunk.AddCube(cube);
					glm::mat4 perObjectModel = glm::mat4(1.0f);
					perObjectModel = glm::translate(perObjectModel, cube.Position);
					models.push_back(perObjectModel);
				}
			}
		}
	}

	renderer.AddChunk(chunk);
	
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, chunk.Ssbo_Models);
	glBufferData(GL_SHADER_STORAGE_BUFFER, models.size() * sizeof(glm::mat4), models.data(), GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, chunk.Ssbo_Models);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

int main()
{
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Minecraft", 0, 0);
	glfwMakeContextCurrent(window);
	gladLoadGL();

	glfwSetKeyCallback(window, KeyListener::KeyCallback);
	glfwSetMouseButtonCallback(window, MouseListener::MouseButtonCallback);
	glfwSetCursorPosCallback(window, MouseListener::MousePosCallback);
	glfwSetScrollCallback(window, MouseListener::MouseScrollCallback);

	Renderer renderer;
	renderer.Init();

	Camera camera;

	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

	GenerateChunk(noise, renderer, 9, 0, 0);

	float previous = (float)glfwGetTime();

	while (!glfwWindowShouldClose(window))
	{
		float now = (float)glfwGetTime();
		float dt = now - previous;
		previous = now;

		glEnable(GL_DEPTH_TEST);
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer.Render(camera);
		camera.Movement(dt, window);

		KeyListener::EndFrame();
		MouseListener::EndFrame();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	return 0;
}