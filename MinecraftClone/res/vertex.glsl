#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
//layout (location = 2) in vec3 aOffset;

out vec2 texCoords;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

uniform mat4 modelMatrices[125];
uniform int indices[1000];

void main()
{
	texCoords = aTexCoords;

	gl_Position = proj * view * modelMatrices[indices[gl_VertexID]] * vec4(aPos, 1.0);
}