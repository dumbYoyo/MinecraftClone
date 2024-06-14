#include "Renderer.h"

void Renderer::Init()
{
	m_shader.Init("res/vertex.glsl", "res/fragment.glsl");

	glm::mat4 proj = glm::perspective(70.f, 16.f / 9.f, 0.1f, 1000.f);
	m_shader.Bind();
	m_shader.LoadMat4f("proj", proj);
	m_shader.Unbind();
}

/// <summary>
/// Meshes with same Id are not allowed
/// </summary>
void Renderer::CreateMesh(unsigned int& meshId, std::string commonTexture)
{
	Mesh mesh(120);
	m_meshes[meshId] = mesh;
	CreateTexture(m_texId, commonTexture);
}

void Renderer::Render(Camera& camera)
{
	m_shader.Bind();

	glm::mat4& view = camera.GetView();
	m_shader.LoadMat4f("view", view);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texId);
	m_shader.LoadInt("texSampler", 0);

	for (auto it = m_meshes.begin(); it != m_meshes.end(); it++)
	{
		Mesh& mesh = it->second;
		
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, mesh.Position);
		m_shader.LoadMat4f("model", model);

		for (int i = 0; i < mesh.Translations.size(); i++)
		{
			glm::mat4 perObjectModel = glm::mat4(1.0f);
			perObjectModel = glm::translate(perObjectModel, mesh.Translations[i]);
			m_shader.LoadMat4f(("modelMatrices[" + std::to_string(i) + "]").c_str(), perObjectModel);
		}

		for (int i = 0; i < mesh.Indices.size(); i++)
		{
			m_shader.LoadInt(("indices[" + std::to_string(i) + "]").c_str(), mesh.Indices[i]);
		}

		glBindVertexArray(mesh.Vao);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glDrawArrays(GL_TRIANGLES, 0, mesh.VertexCount);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glBindVertexArray(0);
	}
	m_shader.Unbind();
}

Mesh& Renderer::GetMesh(unsigned int& meshId)
{
	return m_meshes[meshId];
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
