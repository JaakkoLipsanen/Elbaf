#version 330 core

in vec4 fragmentColor;
in vec4 fragShadowCoord;

layout(location = 0) out vec4 color;

uniform vec3 Tint;
uniform sampler2D ShadowMap;

const float ShadowDarkness = 0.5; // multiplier of color when the fragment is in shadow
void main()
{
	// Output color = red 
	color = fragmentColor;
	color.rgb *= Tint;
		
	vec2 uv = fragShadowCoord.xy; // "uv" == shadow map uv
	if(uv.x <= 0 || uv.x >= 1 || uv.y <= 0 || uv.y >= 1)
	{
		// if the uv is out of bounds (outside [0, 1]), then the area is LIGHTED
		return;
	}

	float shadowMapZ = texture(ShadowMap, fragShadowCoord.xy).r; // shadow map's z-value
	float fragmentZ = fragShadowCoord.z; // current fragment depth in SHADOW/LIGHT COORDINATES aka distance from shadowmap source

	const float Bias = 0.005;
	if(shadowMapZ < fragmentZ - Bias)
	{
		color.rgb *= ShadowDarkness; 
	}
}