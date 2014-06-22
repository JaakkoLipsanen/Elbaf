#version 330 core

in vec4 fragmentColor;
in vec2 uvFS;

// Ouput data
out vec4 color;


uniform sampler2D TextureSampler;
uniform bool TextureEnabled;

void main()
{

	// Output color = red 
	color = fragmentColor;
	 color.rgb *= texture2D(TextureSampler, uvFS).rgb;

}