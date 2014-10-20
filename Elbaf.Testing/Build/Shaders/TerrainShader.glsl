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