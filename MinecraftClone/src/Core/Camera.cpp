#include "Camera.h"

void Camera::Movement(float dt, GLFWwindow* window)
{
	glm::vec3 forward = glm::normalize(glm::inverse(m_view)[2]);
	glm::vec3 right = glm::normalize(glm::inverse(m_view)[0]);
	glm::vec3 up = glm::normalize(glm::inverse(m_view)[1]);

	if (MouseListener::GetMouseButtonPressed(0))
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		Rotation.y -= MouseListener::GetDx() * .002f;
		Rotation.x -= MouseListener::GetDy() * .002f;

		if (KeyListener::GetKeyPressed(GLFW_KEY_W))
			Position += 4.f * dt * forward;
		if (KeyListener::GetKeyPressed(GLFW_KEY_S))
			Position -= 4.f * dt * forward;
		if (KeyListener::GetKeyPressed(GLFW_KEY_A))
			Position += 4.f * dt * right;
		if (KeyListener::GetKeyPressed(GLFW_KEY_D))
			Position -= 4.f * dt * right;
		if (KeyListener::GetKeyPressed(GLFW_KEY_Q))
			Position += 4.f * dt * up;
		if (KeyListener::GetKeyPressed(GLFW_KEY_E))
			Position -= 4.f * dt * up;
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

glm::mat4& Camera::GetView()
{
	m_view = glm::mat4(1.0f);
	m_view = glm::rotate(m_view, Rotation.x, glm::vec3(1, 0, 0));
	m_view = glm::rotate(m_view, Rotation.y, glm::vec3(0, 1, 0));
	m_view = glm::rotate(m_view, Rotation.z, glm::vec3(0, 0, 1));
	m_view = glm::translate(m_view, Position);
	return m_view;
}
