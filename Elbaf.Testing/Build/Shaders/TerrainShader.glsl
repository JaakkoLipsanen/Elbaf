#(vertex-shader)
#version 440

#(name "Terrain VS")
#(include "Shaders/ShadowHelper.vert")

struct DirectionalLight
{
	vec3 Direction;
	float Power; // [0, 1]
	vec3 Color;
};

uniform vec3 AmbientLight = vec3(0.3, 0.3, 0.3);
uniform DirectionalLight Light = { vec3(-0.2, -1., -0.5), 1, vec3(1, 1, 1) };





layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec4 VertexColor;
layout(location = 2) in vec2 VertexUV;
layout(location = 3) in vec3 VertexNormal;

uniform mat4 MVP;
uniform mat4 M;
uniform mat4 ShadowMVP;

out vec4 FragmentColor;
out vec2 FragmentUV;
out vec3 FragmentShadowCoord; // shadow/light coordinate
out vec3 FragmentLightColor;

void main(){

	gl_Position =  MVP * vec4(VertexPosition, 1);
	FragmentShadowCoord = CalculateShadowFragmentCoord(ShadowMVP, VertexPosition);

	FragmentUV = VertexUV;
	FragmentColor = VertexColor;


	mat4 inverseTransposeWorld = transpose(inverse(M));
	vec3 L = normalize(Light.Direction);
	vec3 N = normalize((inverseTransposeWorld * vec4(VertexNormal, 0)).xyz); /// !!!!!!!!!!!! WHEN TRANSFORMING NORMAL, THE "W" COMPONENT MUST BE 0... forgot that..
	float d = dot(N, L);
	d = clamp(-d, 0, 1);

	FragmentLightColor = min(vec3(1, 1, 1), AmbientLight + Light.Color * d * Light.Power); 

}

#(fragment-shader)
#version 440

#(name "Terrain FS")
#(include "Shaders/ShadowHelper.frag")

in vec4 FragmentColor;
in vec2 FragmentUV;
in vec3 FragmentShadowCoord;
in vec3 FragmentLightColor;

layout(location = 0) out vec4 color;

uniform sampler2D ShadowMap;
uniform sampler2D Texture;
uniform vec3 Tint;

void main()
{
	color = texture(Texture, FragmentUV) * FragmentColor;
	color.rgb *= Tint;
	color.rgb *= FragmentLightColor;

	color = ApplyShadow(color, ShadowMap, FragmentShadowCoord);
}