#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "MouseListener.h"
#include "KeyListener.h"

class Camera
{
public:
	glm::vec3 Position{ 0, 0, 0 };
	glm::vec3 Rotation{ 0, 0, 0 };

	void Movement(float dt, GLFWwindow* window);
	glm::mat4& GetView();
private:
	glm::mat4 m_view;
};
