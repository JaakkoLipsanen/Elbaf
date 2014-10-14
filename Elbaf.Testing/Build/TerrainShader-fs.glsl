#version 330 core

in vec4 fragmentColor;
layout(location = 0) out vec4 color;

uniform vec3 Tint;

void main()
{
	// Output color = red 
	color = fragmentColor;
	color.rgb *= Tint;
}