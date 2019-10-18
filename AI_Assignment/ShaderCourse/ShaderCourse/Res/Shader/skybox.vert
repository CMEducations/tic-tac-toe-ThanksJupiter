#version 330 core
in vec3 a_Position;

uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 f_CubeDirection;

void main()
{
	mat4 ViewNoTranslate = u_View;
	ViewNoTranslate[3] = vec4(0.0, 0.0, 0.0, 1.0);

	gl_Position = u_Projection * ViewNoTranslate * vec4(a_Position, 1.0);
	gl_Position.z = gl_Position.w - 0.001;

	f_CubeDirection = a_Position;
}
