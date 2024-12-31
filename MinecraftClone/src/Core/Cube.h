#pragma once

#include <vector>
#include <glm/glm.hpp>

struct Cube
{
public:
	glm::vec3 Position{ 0, 0, 0 };
	glm::vec3 Scale{ 1, 1, 1 };
	glm::vec3 Rotation{ 0, 0, 0 };
	std::vector<float> Vertices;
	std::vector<float> TextureCoords;
	int VertexCount = 0;

	Cube(bool front = true, bool back = true, bool top = true, bool bottom = true, bool left = true, bool right = true)
	{
		Generate(front, back, top, bottom, left, right);
	}

	void AddVertexPosition(float x, float y, float z)
	{
		Vertices.push_back(x);
		Vertices.push_back(y);
		Vertices.push_back(z);
		VertexCount++;
	}

	void AddTexCoord(float x, float y)
	{
		TextureCoords.push_back(x);
		TextureCoords.push_back(y);
	}

private:
	void Generate(bool front, bool back, bool top, bool bottom, bool left, bool right)
	{

		if (back)
		{
			AddVertexPosition(-0.5f, 0.5f, -0.5f);
			AddVertexPosition(-0.5f, -0.5f, -0.5f);
			AddVertexPosition(0.5f, 0.5f, -0.5f);
			AddVertexPosition(0.5f, 0.5f, -0.5f);
			AddVertexPosition(-0.5f, -0.5f, -0.5f);
			AddVertexPosition(0.5f, -0.5f, -0.5f);

			AddTexCoord(0, 0);
			AddTexCoord(0, 1);
			AddTexCoord(1, 0);
			AddTexCoord(1, 0);
			AddTexCoord(0, 1);
			AddTexCoord(1, 1);
		}

		if (front)
		{
			AddVertexPosition(-0.5f, 0.5f, 0.5f);
			AddVertexPosition(-0.5f, -0.5f, 0.5f);
			AddVertexPosition(0.5f, 0.5f, 0.5f);
			AddVertexPosition(0.5f, 0.5f, 0.5f);
			AddVertexPosition(-0.5f, -0.5f, 0.5f);
			AddVertexPosition(0.5f, -0.5f, 0.5f);

			AddTexCoord(0, 0);
			AddTexCoord(0, 1);
			AddTexCoord(1, 0);
			AddTexCoord(1, 0);
			AddTexCoord(0, 1);
			AddTexCoord(1, 1);
		}

		if (right)
		{
			AddVertexPosition(0.5f, 0.5f, -0.5f);
			AddVertexPosition(0.5f, -0.5f, -0.5f);
			AddVertexPosition(0.5f, 0.5f, 0.5f);
			AddVertexPosition(0.5f, 0.5f, 0.5f);
			AddVertexPosition(0.5f, -0.5f, -0.5f);
			AddVertexPosition(0.5f, -0.5f, 0.5f);

			AddTexCoord(0, 0);
			AddTexCoord(0, 1);
			AddTexCoord(1, 0);
			AddTexCoord(1, 0);
			AddTexCoord(0, 1);
			AddTexCoord(1, 1);
		}

		if (left)
		{
			AddVertexPosition(-0.5f, 0.5f, -0.5f);
			AddVertexPosition(-0.5f, -0.5f, -0.5f);
			AddVertexPosition(-0.5f, 0.5f, 0.5f);
			AddVertexPosition(-0.5f, 0.5f, 0.5f);
			AddVertexPosition(-0.5f, -0.5f, -0.5f);
			AddVertexPosition(-0.5f, -0.5f, 0.5f);

			AddTexCoord(0, 0);
			AddTexCoord(0, 1);
			AddTexCoord(1, 0);
			AddTexCoord(1, 0);
			AddTexCoord(0, 1);
			AddTexCoord(1, 1);
		}

		if (top)
		{
			AddVertexPosition(-0.5f, 0.5f, 0.5f);
			AddVertexPosition(-0.5f, 0.5f, -0.5f);
			AddVertexPosition(0.5f, 0.5f, 0.5f);
			AddVertexPosition(0.5f, 0.5f, 0.5f);
			AddVertexPosition(-0.5f, 0.5f, -0.5f);
			AddVertexPosition(0.5f, 0.5f, -0.5f);

			AddTexCoord(0, 0);
			AddTexCoord(0, 1);
			AddTexCoord(1, 0);
			AddTexCoord(1, 0);
			AddTexCoord(0, 1);
			AddTexCoord(1, 1);
		}

		if (bottom)
		{
			AddVertexPosition(-0.5f, -0.5f, 0.5f);
			AddVertexPosition(-0.5f, -0.5f, -0.5f);
			AddVertexPosition(0.5f, -0.5f, 0.5f);
			AddVertexPosition(0.5f, -0.5f, 0.5f);
			AddVertexPosition(-0.5f, -0.5f, -0.5f);
			AddVertexPosition(0.5f, -0.5f, -0.5f);

			AddTexCoord(0, 0);
			AddTexCoord(0, 1);
			AddTexCoord(1, 0);
			AddTexCoord(1, 0);
			AddTexCoord(0, 1);
			AddTexCoord(1, 1);
		}
	}
};