#version 410 core

uniform	float u_repeat;

in vec4 a_vertex;
in vec3 a_tangent;
in vec3 a_bitangent;
in vec3 a_normal;
in vec2 a_texCoord;

out vec4 v_c_vertex;
out vec3 v_c_tangent;
out vec3 v_c_bitangent;
out vec3 v_c_normal;
out vec2 v_c_texCoord;

void main(void)
{
	v_c_vertex = a_vertex;
	v_c_tangent = a_tangent;
	v_c_bitangent = a_bitangent;
	v_c_normal = a_normal;
	v_c_texCoord = a_texCoord * u_repeat; 

	gl_Position = a_vertex;
}
