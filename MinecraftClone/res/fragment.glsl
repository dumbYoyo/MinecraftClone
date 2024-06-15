#version 430 core

out vec4 pColor;

in vec2 texCoords;

uniform sampler2D texSampler;

void main()
{
	pColor = texture(texSampler, texCoords);
}