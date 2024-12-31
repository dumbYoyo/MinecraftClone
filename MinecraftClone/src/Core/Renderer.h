#pragma once

#include <glad/glad.h>
#include <iostream>
#include <unordered_map>
#include <stb/stb_image.h>

#include "Shader.h"
#include "Camera.h"
#include "Chunk.h"

class Renderer
{
public:
	void Init();
	void AddChunk(const Chunk& chunk);
	void Render(Camera& camera);
private:
	void CreateTexture(unsigned int& texId, std::string texPath);

	std::vector<Chunk> m_chunks;
	Shader m_shader;
	unsigned int m_texId;
};
