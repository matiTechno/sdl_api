#version 330

layout (location = 0) in vec4 vertex;

out vec2 texCoords;

uniform mat4 model;
uniform mat4 projection;
uniform vec2 texSides;
uniform vec2 texShift;

void main()
{
	gl_Position = projection * model * vec4(vertex.xy, 0, 1);
	texCoords = vertex.zw * texSides + texShift;
}