#version 330

layout(location = 0) vec3 vertexPosition;

out vec3 fragmentPosition;
uniform mat4 MVP;

void main()
{
	gl_Position =  MVP * vec4(vertexPosition, 1);
}