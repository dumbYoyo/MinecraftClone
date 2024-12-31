#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <glad/glad.h>
#include "Cube.h"

struct Chunk
{
public:
	unsigned int Vao{ 0 };
	unsigned int Vbo{ 0 };
	unsigned int Tbo{ 0 };
	unsigned int Ssbo_Indices{ 0 };
	unsigned int Ssbo_Models{ 0 };
	int VertexCount{ 0 };
	int InstanceCount{ 0 };
	glm::vec3 Position{ 0, 0, 0 };
	std::vector<glm::vec3> Translations{};
	std::vector<int> Indices{};

	Chunk() { }
	Chunk(unsigned int initialVertexArraySize)
		: m_initialVertexArraySize(initialVertexArraySize)
	{
		glGenVertexArrays(1, &Vao);
		glBindVertexArray(Vao);

		glGenBuffers(1, &Vbo);
		glBindBuffer(GL_ARRAY_BUFFER, Vbo);
		glBufferData(GL_ARRAY_BUFFER, initialVertexArraySize * sizeof(float), m_vertices.data(), GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &Tbo);
		glBindBuffer(GL_ARRAY_BUFFER, Tbo);
		glBufferData(GL_ARRAY_BUFFER, 2 * (initialVertexArraySize / 3) * sizeof(float), m_texCoords.data(), GL_DYNAMIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &Ssbo_Indices);
		glGenBuffers(1, &Ssbo_Models);
	}


	void AddCube(Cube& cube)
	{
		AppendVertices(cube.Vertices);
		AppendTexCoords(cube.TextureCoords);

		Translations.push_back(cube.Position);
		for (int i = 0; i < cube.VertexCount; i++)
			Indices.push_back(InstanceCount);
		VertexCount += cube.VertexCount;
		UpdateSsbo_Indices();

		InstanceCount++;
	}

	void AppendVertices(const std::vector<float>& verticesToAppend)
	{
		m_vertices.insert(m_vertices.end(), verticesToAppend.begin(), verticesToAppend.end());
		UpdateVbo();
	}

	void AppendTexCoords(const std::vector<float>& texCoordsToAppend)
	{
		m_texCoords.insert(m_texCoords.end(), texCoordsToAppend.begin(), texCoordsToAppend.end());
		UpdateTbo();
	}

	void AddVertex(float x, float y, float z)
	{
		m_vertices.push_back(x);
		m_vertices.push_back(y);
		m_vertices.push_back(z);
		UpdateVbo();
	}

	void AddTexCoord(float x, float y)
	{
		m_texCoords.push_back(x);
		m_texCoords.push_back(y);
		UpdateTbo();
	}

	void UpdateSsbo_Indices()
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, Ssbo_Indices);
		glBufferData(GL_SHADER_STORAGE_BUFFER, Indices.size() * sizeof(int), Indices.data(), GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, Ssbo_Indices);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}

	void UpdateVbo()
	{
		glBindBuffer(GL_ARRAY_BUFFER, Vbo);
		if (m_vertices.size() * sizeof(float) > m_initialVertexArraySize * sizeof(float))
			glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_DYNAMIC_DRAW);
		else
			glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(float), m_vertices.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void UpdateTbo()
	{
		glBindBuffer(GL_ARRAY_BUFFER, Tbo);
		if (m_texCoords.size() * sizeof(float) > (2 / 3) * m_initialVertexArraySize * sizeof(float))
		{
			glBufferData(GL_ARRAY_BUFFER, m_texCoords.size() * sizeof(float), m_texCoords.data(), GL_DYNAMIC_DRAW);
		}
		else
			glBufferSubData(GL_ARRAY_BUFFER, 0, m_texCoords.size() * sizeof(float), m_texCoords.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
private:
	std::vector<float> m_vertices{};
	std::vector<float> m_texCoords{};
	unsigned int m_initialVertexArraySize{ 0 };
};