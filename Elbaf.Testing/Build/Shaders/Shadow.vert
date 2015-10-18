#(include "Shaders/ShadowHelper.vert")

uniform mat4 ShadowMVP;
out vec4 FragmentShadowCoord; // shadow/light coordinate

void CalculateShadows(vec3 vertexPosition)
{
	FragmentShadowCoord = CalculateShadows(ShadowMVP, VertexPosition);
}