#pragma once

#include <glad/glad.h>
#include <iostream>
#include <unordered_map>
#include <stb/stb_image.h>

#include "Shader.h"
#include "Camera.h"

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

struct Mesh
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

	Mesh() {  }
	Mesh(unsigned int initialVertexArraySize)
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

class Renderer
{
public:
	void Init();
	void CreateMesh(unsigned int& meshId, std::string commonTexture);
	void Render(Camera& camera);
	Mesh& GetMesh(unsigned int& meshId);
private:
	void CreateTexture(unsigned int& texId, std::string texPath);

	std::unordered_map<unsigned int, Mesh> m_meshes; // am I really needed?
	Shader m_shader;
	unsigned int m_texId;
};
