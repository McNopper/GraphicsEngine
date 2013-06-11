#version 410 core

uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_modelMatrix;

uniform vec3 u_lineGeometryOffset0;
uniform vec3 u_lineGeometryOffset1;

in vec4 a_vertex;

void main(void)
{
	int index = gl_VertexID % 2;
	
	vec4 vertex = a_vertex; 
	
	if (index == 0)
	{
		vertex += vec4(u_lineGeometryOffset0, 0.0);
	}
	else
	{
		vertex += vec4(u_lineGeometryOffset1, 0.0);
	}

	gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * vertex;
}
