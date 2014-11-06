#(vertex-shader)
#(name "Terrain VS")
#version 440

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec4 vertexColor;
layout(location = 3) in vec3 vertexNormal;

uniform mat4 MVP;
uniform mat4 ShadowMVP;

out vec4 fragmentColor;
out vec4 fragShadowCoord; // shadow/light coordinate

const vec3 LightDirection = vec3(0, -1, 0);
void main(){

	gl_Position =  MVP * vec4(vertexPosition, 1);
	fragShadowCoord = ShadowMVP * vec4(vertexPosition, 1);

	/* vertex shading */
	vec3 l = normalize(LightDirection);
	vec3 n = normalize(vertexNormal);

	float d = dot(n, l);
	d = sqrt(clamp(-d, 0, 1));
	
	fragmentColor = vertexColor * vec4(d, d, d, 1);
}

#(fragment-shader)
#(name "Terrain FS")
#version 440

in vec4 fragmentColor;
in vec4 fragShadowCoord;

layout(location = 0) out vec4 color;

uniform vec3 Tint;
uniform sampler2D ShadowMap;

float GetShadowAmount(vec3 shadowCoord)
{
	// omni-directional. 4-direction could be okay too
	const vec2 Offsets[] = { vec2(-1, 0), vec2(1, 0), vec2(0, -1), vec2(0, 1), vec2(-1, -1), vec2(-1, 1), vec2(1, -1), vec2(1, 1) };
	const float ShadowDarkness = 0.5; // multiplier of color when the fragment is in shadow

	vec2 uv = shadowCoord.xy; // "uv" == shadow map uv
	if(uv.x <= 0 || uv.x >= 1 || uv.y <= 0 || uv.y >= 1)
	{
		// if the uv is out of bounds (outside [0, 1]), then the area is LIGHTED
		return 1;
	}

	const float Bias = 0.005;
	float fragmentZ = shadowCoord.z - Bias; // current fragment depth in SHADOW/LIGHT COORDINATES aka distance from shadowmap source

	float totalLight = 0f;
	for(int i = 0; i <  Offsets.length(); i++)
	{
		const float OffsetAmount = 0.001;
		float shadowMapZ = texture(ShadowMap, shadowCoord.xy + Offsets[i] * OffsetAmount).r; // shadow map's z-value
		totalLight += (shadowMapZ < fragmentZ) ? ShadowDarkness : 1;
	}

	return totalLight / Offsets.length();
}

void main()
{
	// Output color = red 
	color = fragmentColor;
	color.rgb *= Tint;

	color.rgb *= GetShadowAmount(fragShadowCoord.xyz);
}