#(vertex-shader)
#(name "Default Shader VS")
#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec2 vertexUV;
layout(location = 3) in vec3 vertexNormal;

struct DirectionalLight
{
	vec3 Direction;
	float Power; // [0, 1]
};

const int MaxLights = 4;
uniform DirectionalLight Lights[MaxLights];
uniform int LightCount;

uniform float AmbientLightAmount = 0.3f;
uniform mat4 MVP;


out vec4 fragmentColor;
out vec2 fragmentUV;

void main(){

	gl_Position =  MVP * vec4(vertexPosition, 1);	
	
	fragmentColor = vertexColor;
	fragmentUV = vertexUV;
	if(LightCount == 0)
	{
		return;
	}

	float lightAmount = 0;
	for(int i = 0; i < LightCount; i++)
	{
		vec3 l = normalize(Lights[i].Direction);
		vec3 n = normalize(vertexNormal);

		float d = dot(n, l);
		d = sqrt(clamp(-d, 0, 1));

		lightAmount += d * Lights[i].Power;
	}

	lightAmount = min(lightAmount + AmbientLightAmount, 1);
	fragmentColor.rgb *= vec3(lightAmount, lightAmount, lightAmount);
}


#(fragment-shader)
#(name "Default Shader FS")
#version 330 core

in vec4 fragmentColor;
in vec2 fragmentUV;

// Ouput data
layout(location = 0) out vec4 color;

uniform sampler2D TextureSampler;
uniform vec3 Tint;

void main()
{
	// Output color = red 
	color = fragmentColor;
	color.rgba *= texture2D(TextureSampler, fragmentUV).rgba;

	color.rgb *= Tint;
}