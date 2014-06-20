#version 330 core

in vec4 fragmentColor;
in vec2 uvFS;

// Ouput data
out vec4 color;


uniform sampler2D TextureSampler;

void main()
{

	// Output color = red 
	color = texture2D(TextureSampler, uvFS).rgba + fragmentColor; // vec3(1,0,0);

}