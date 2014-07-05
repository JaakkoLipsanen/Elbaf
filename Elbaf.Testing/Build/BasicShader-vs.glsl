#version 330 core


// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec2 uvVS;
layout(location = 3) in vec3 normal;

uniform bool UseLighting;
uniform mat4 MVP;
uniform vec3 lightDir = vec3(0, -1, 0);

out vec4 fragmentColor;
out vec2 uvFS;

void main(){

	gl_Position =  MVP * vec4(vertexPosition_modelspace, 1);
	uvFS = uvVS;
	fragmentColor = vertexColor;

	if(UseLighting)
	{
		vec3 l = normalize(lightDir);
		vec3 n = normalize(normal);

		float d = dot(n, l);
		d = clamp(-d, 0, 1);
	
		d = sqrt(d);
		fragmentColor = vertexColor * vec4(d, d, d, 1);
	}
}

