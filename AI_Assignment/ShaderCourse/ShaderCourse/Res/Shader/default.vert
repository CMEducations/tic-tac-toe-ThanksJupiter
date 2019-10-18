#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;

uniform float u_Time;
uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_World;

out vec3 f_World;
out vec3 f_Normal;
out vec2 f_TexCoord;
out float f_CameraDepth;

void main()
{
	gl_Position = u_Projection * u_View * u_World * vec4(a_Position, 1.0);

	vec4 CameraSpacePosition = u_View * u_World * vec4(a_Position, 1.0);
	f_CameraDepth = -CameraSpacePosition.z;

	f_World = (u_World * vec4(a_Position, 1.0)).xyz;
	f_Normal = normalize((u_World * vec4(a_Normal, 0.0)).xyz);
	f_TexCoord = a_TexCoord;
}