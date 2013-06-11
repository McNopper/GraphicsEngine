#version 410 core

uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_modelMatrix;
uniform mat3 u_normalModelMatrix;

in vec4 a_vertex;
in vec3 a_normal;
in vec3 a_bitangent;
in vec3 a_tangent;
in vec2 a_texCoord;

out vec4 v_vertex;
out vec3 v_normal;
out vec3 v_bitangent;
out vec3 v_tangent;
out vec2 v_texCoord;

void main(void)
{
	v_vertex = u_modelMatrix * a_vertex;

	v_normal = u_normalModelMatrix * a_normal;
	v_bitangent = u_normalModelMatrix * a_bitangent;
	v_tangent = u_normalModelMatrix * a_tangent;

	v_texCoord = a_texCoord;

	gl_Position = u_projectionMatrix * u_viewMatrix * v_vertex;
}
