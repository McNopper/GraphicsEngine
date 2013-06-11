#version 410 core

uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_modelMatrix;

in vec4 a_vertex;

out vec3 v_ray;

void main(void)
{
	v_ray = normalize(a_vertex.xyz);
	
	gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * a_vertex;
}
