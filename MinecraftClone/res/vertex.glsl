#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 texCoords;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

//uniform mat4 modelMatrices[512];
//uniform int indices[1000];

layout(std430, binding = 3) buffer dataIndices
{
	int Indices[10000];
};

layout(std430, binding = 4) buffer dataModels
{
	mat4 ModelMatrices[8*8*8];
};

void main()
{
	texCoords = aTexCoords;

	gl_Position = (proj * view * (ModelMatrices[Indices[gl_VertexID]] * model) * vec4(aPos, 1.0));
}