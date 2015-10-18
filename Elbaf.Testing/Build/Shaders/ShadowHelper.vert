vec3 CalculateShadowFragmentCoord(mat4x4 shadowMVP, vec3 vertexPosition)
{
	return (shadowMVP * vec4(vertexPosition, 1)).xyz;
}