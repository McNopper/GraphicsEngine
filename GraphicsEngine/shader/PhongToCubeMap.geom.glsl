#version 420 core

layout(triangles) in;

layout(triangle_strip, max_vertices = 3) out;

uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;

in vec4 v_g_vertex[];
in vec3 v_g_normal[];
in vec3 v_g_bitangent[];
in vec3 v_g_tangent[];
in vec2 v_g_texCoord[];

out vec4 v_vertex;
out vec3 v_normal;
out vec3 v_bitangent;
out vec3 v_tangent;
out vec2 v_texCoord;

void main(void)
{
	for(int i = 0; i < gl_in.length(); ++i)
	{
		v_vertex = v_g_vertex[i];
		v_normal = v_g_normal[i];
		v_bitangent = v_g_bitangent[i];
		v_tangent = v_g_tangent[i];
		v_texCoord = v_g_texCoord[i];

		gl_Position = u_projectionMatrix * u_viewMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
	
	EndPrimitive();
}
