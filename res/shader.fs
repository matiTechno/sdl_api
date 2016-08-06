#version 330

in vec2 texCoords;

out vec4 color;

uniform vec4 sprite_color;

uniform sampler2D sampl;

void main()
{
	color = texture(sampl, texCoords) * sprite_color;
}