
#(vertex-shader)
#(name "Depth Pass VS")
#version 330 core

layout(location = 0) in vec3 vertexPosition;
uniform mat4 MVP;

void main()
{
	gl_Position =  MVP * vec4(vertexPosition, 1);
}



#(fragment-shader)
#(name "Depth Pass FS")
#version 330 core

layout(location = 0) out float depth;
void main()
{
	depth = gl_FragCoord.z;
}