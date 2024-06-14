#include "MouseListener.h"

MouseListener* MouseListener::m_instance = nullptr;

MouseListener::MouseListener()
{
	m_scrollX = 0.0f;
	m_scrollY = 0.0f;
	m_posX = 0.0f;
	m_posY = 0.0f;
	m_lastX = 0.0f;
	m_lastY = 0.0f;
}

MouseListener* MouseListener::Get()
{
	if (m_instance == nullptr)
		m_instance = new MouseListener();
	return m_instance;
}

void MouseListener::MousePosCallback(GLFWwindow* window, double posX, double posY)
{
	Get()->m_lastX = Get()->m_posX;
	Get()->m_lastY = Get()->m_posY;
	Get()->m_posX = (float)posX;
	Get()->m_posY = (float)posY;
}

void MouseListener::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		Get()->m_mouseButtonPressed[button] = true;
		Get()->m_mouseButtonClicked[button] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		Get()->m_mouseButtonPressed[button] = false;
		Get()->m_mouseButtonClicked[button] = false;
	}
}

void MouseListener::MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	Get()->m_scrollX = (float)xOffset;
	Get()->m_scrollY = (float)yOffset;
}

void MouseListener::EndFrame()
{
	Get()->m_scrollX = 0;
	Get()->m_scrollY = 0;
	Get()->m_lastX = Get()->m_posX;
	Get()->m_lastY = Get()->m_posY;

	for (int i = 0; i < sizeof(Get()->m_mouseButtonClicked) / sizeof(bool); i++)
	{
		Get()->m_mouseButtonClicked[i] = false;
	}
}

float MouseListener::GetX()
{
	return Get()->m_posX;
}

float MouseListener::GetY()
{
	return Get()->m_posY;
}

float MouseListener::GetDx()
{
	return (Get()->m_lastX - Get()->m_posX);
}

float MouseListener::GetDy()
{
	return (Get()->m_lastY - Get()->m_posY);
}

float MouseListener::GetScrollX()
{
	return Get()->m_scrollX;
}

float MouseListener::GetScrollY()
{
	return Get()->m_scrollY;
}

bool MouseListener::GetMouseButtonPressed(int button)
{
	return Get()->m_mouseButtonPressed[button];
}

bool MouseListener::GetMouseButtonClicked(int button)
{
	return Get()->m_mouseButtonClicked[button];
}
