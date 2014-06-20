#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec2 uvVS;

uniform mat4 MVP;
out vec4 fragmentColor;
out vec2 uvFS;
void main(){

	gl_Position =  MVP * vec4(vertexPosition_modelspace, 1);
	fragmentColor = vertexColor;
	uvFS = uvVS;
}

