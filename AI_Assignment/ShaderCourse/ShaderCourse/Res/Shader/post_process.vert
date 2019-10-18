#version 330 core
const vec2 QuadVerts[] = vec2[](
	vec2(-1.0, -1.0),
	vec2(1.0, -1.0),
	vec2(1.0, 1.0),
	vec2(-1.0, 1.0)
);

const vec2 QuadTexCoords[] = vec2[](
	vec2(0.0, 0.0),
	vec2(1.0, 0.0),
	vec2(1.0, 1.0),
	vec2(0.0, 1.0)
);

out vec2 f_TexCoord;

void main()
{
	gl_Position = vec4(QuadVerts[gl_VertexID], 0.0, 1.0);
	f_TexCoord = QuadTexCoords[gl_VertexID];
}