#version 330 core
layout(location = 0) in vec3 a_Position;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_World;

void main()
{
	gl_Position = u_Projection * u_View * u_World * vec4(a_Position, 1.0);
}