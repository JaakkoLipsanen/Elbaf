
#version 330 core


// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec2 vertexUV;
layout(location = 3) in vec3 normal;

uniform mat4 MVP;

out vec4 fragmentColor;
out vec2 fragmentUV;

const vec3 LightDirection = vec3(0, -1, 0);
void main(){

	gl_Position =  MVP * vec4(vertexPosition_modelspace, 1);
	fragmentUV = vertexUV;

	vec3 l = normalize(LightDirection);
	vec3 n = normalize(normal);

	float d = dot(n, l);
	d = sqrt(clamp(-d, 0, 1));
	
	fragmentColor = vertexColor * vec4(d, d, d, 1);
}
