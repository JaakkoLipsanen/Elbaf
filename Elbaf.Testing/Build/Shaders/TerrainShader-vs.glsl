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