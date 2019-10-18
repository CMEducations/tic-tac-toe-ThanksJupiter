#version 330 core

uniform samplerCube u_Sampler;

in vec3 f_CubeDirection;
out vec4 o_Color;

void main()
{
	o_Color = texture(u_Sampler, f_CubeDirection);
}