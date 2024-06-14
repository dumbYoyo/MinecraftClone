#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Core/Shader.h"
#include "Core/Renderer.h"

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

	unsigned int mesh = 1;
	renderer.CreateMesh(mesh, "res/tex.png");

	std::vector<glm::vec3> positions;

	int CHUNK_SIZE = 5;
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			for (int k = 0; k < CHUNK_SIZE; k++)
			{
				positions.push_back(glm::vec3(i, j, k));
			}
		}
	}

	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			for (int k = 0; k < CHUNK_SIZE; k++)
			{
				bool right = (std::find(positions.begin(), positions.end(), glm::vec3(i + 1, j, k)) != positions.end()) ? false : true;
				bool left = (std::find(positions.begin(), positions.end(), glm::vec3(i - 1, j, k)) != positions.end()) ? false : true;
				bool top = (std::find(positions.begin(), positions.end(), glm::vec3(i, j + 1, k)) != positions.end()) ? false : true;
				bool bottom = (std::find(positions.begin(), positions.end(), glm::vec3(i, j - 1, k)) != positions.end()) ? false : true;
				bool back = (std::find(positions.begin(), positions.end(), glm::vec3(i, j, k - 1)) != positions.end()) ? false : true;
				bool front = (std::find(positions.begin(), positions.end(), glm::vec3(i, j, k + 1)) != positions.end()) ? false : true;
				
				Cube cube(front, back, top, bottom, left, right);
				cube.Position = glm::vec3(i, j, k);
				renderer.GetMesh(mesh).AddCube(cube);
			}
		}
	}

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