#version 330 core

uniform sampler2D u_FrameColor;
uniform sampler2D u_FrameDepth;

in vec2 f_TexCoord;
out vec4 o_Color;
const vec3 FogColor = vec3(0.3, 0.45, 0.7);

void main()
{
	vec4 Color = texture(u_FrameColor, f_TexCoord);
	o_Color = Color;
}