#(include "Shaders/ShadowHelper.frag")

in vec4 FragmentShadowCoord;

vec4 ApplyShadow(vec4 color) 
{
	return ApplyShadow(color, ShadowMap, FragmentShadowCoord.xyz);
}