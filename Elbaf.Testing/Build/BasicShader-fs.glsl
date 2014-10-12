#version 330 core

in vec4 fragmentColor;
in vec2 uvFS;

// Ouput data
layout(location = 0) out vec4 color;


uniform sampler2D TextureSampler;
uniform vec3 Tint;

void main()
{

	// Output color = red 
	color = fragmentColor;
	color.rgb *= Tint;

	color.rgba *= texture2D(TextureSampler, uvFS).rgba;
}