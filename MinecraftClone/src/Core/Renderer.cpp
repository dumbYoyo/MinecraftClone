#include "Renderer.h"

void Renderer::Init()
{
	m_shader.Init("res/vertex.glsl", "res/fragment.glsl");

	glm::mat4 proj = glm::perspective(70.f, 16.f / 9.f, 0.1f, 1000.f);
	m_shader.Bind();
	m_shader.LoadMat4f("proj", proj);
	m_shader.Unbind();

	CreateTexture(m_texId, "res/tex.png");
}

void Renderer::AddChunk(const Chunk& chunk)
{
	m_chunks.push_back(chunk);
}

void Renderer::Render(Camera& camera)
{
	m_shader.Bind();

	glm::mat4& view = camera.GetView();
	m_shader.LoadMat4f("view", view);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texId);
	m_shader.LoadInt("texSampler", 0);

	for (Chunk& chunk : m_chunks)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, chunk.Position);
		m_shader.LoadMat4f("model", model);

		/*
		for (int i = 0; i < mesh.Translations.size(); i++)
		{
			glm::mat4 perObjectModel = glm::mat4(1.0f);
			perObjectModel = glm::translate(perObjectModel, mesh.Translations[i]);
			m_shader.LoadMat4f(("modelMatrices[" + std::to_string(i) + "]").c_str(), perObjectModel);
		}
		*/

		glBindVertexArray(chunk.Vao);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glDrawArrays(GL_TRIANGLES, 0, chunk.VertexCount);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindVertexArray(0);
	}
	m_shader.Unbind();
}

void Renderer::CreateTexture(unsigned int& texId, std::string texPath)
{
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height, channels;
	unsigned char* data = stbi_load(texPath.c_str(), &width, &height, &channels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}
	else
	{
		std::cout << "ERROR::TEXTURE_LOADING::" << texPath << "\n";
	}
}
