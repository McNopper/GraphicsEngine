#version 410 core

#define MAX_LIGHTS 8

layout(triangles, equal_spacing, ccw) in;

uniform	int u_numberLights;

in vec4 v_e_vertex[];
in vec3 v_e_tangent[];
in vec3 v_e_bitangent[];
in vec3 v_e_normal[];
in vec2 v_e_texCoord[];

in ArrayData
{
	vec4 projCoord[MAX_LIGHTS];
} v_inData[];

out vec4 v_g_vertex;
out vec3 v_g_tangent;
out vec3 v_g_bitangent;
out vec3 v_g_normal;
out vec2 v_g_texCoord;

out ArrayData
{
	vec4 projCoord[MAX_LIGHTS];
} v_outData;

vec2 interpolateVec2(in vec2 v0, in vec2 v1, in vec2 v2)
{
	return v0 * gl_TessCoord.x + v1 * gl_TessCoord.y + v2 * gl_TessCoord.z;
}

vec3 interpolateVec3(in vec3 v0, in vec3 v1, in vec3 v2)
{
	return v0 * gl_TessCoord.x + v1 * gl_TessCoord.y + v2 * gl_TessCoord.z;
}

vec4 interpolateVec4(in vec4 v0, in vec4 v1, in vec4 v2)
{
	return v0 * gl_TessCoord.x + v1 * gl_TessCoord.y + v2 * gl_TessCoord.z;
}

void main(void)
{
	v_g_vertex = interpolateVec4(v_e_vertex[0], v_e_vertex[1], v_e_vertex[2]);
	v_g_tangent = interpolateVec3(v_e_tangent[0], v_e_tangent[1], v_e_tangent[2]);
	v_g_bitangent = interpolateVec3(v_e_bitangent[0], v_e_bitangent[1], v_e_bitangent[2]);
	v_g_normal = interpolateVec3(v_e_normal[0], v_e_normal[1], v_e_normal[2]);
	v_g_texCoord = interpolateVec2(v_e_texCoord[0], v_e_texCoord[1], v_e_texCoord[2]);

	#pragma optionNV(unroll all)
	for (int i = 0; i < MAX_LIGHTS; i++)
	{
		if (i >= u_numberLights)
		{
			break;
		}

		v_outData.projCoord[i] = interpolateVec4(v_inData[0].projCoord[i], v_inData[1].projCoord[i], v_inData[2].projCoord[i]);
	}

	gl_Position = interpolateVec4(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_in[2].gl_Position);
}
