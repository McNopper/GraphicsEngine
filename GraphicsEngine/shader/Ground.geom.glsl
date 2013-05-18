#version 420 core

layout(triangle_strip, max_vertices = 3) out;

struct MaterialProperties
{
	vec4 emissiveColor;
	vec4 ambientColor;
	vec4 diffuseColor;
	sampler2D diffuseTexture; 
	vec4 specularColor;
	sampler2D specularTexture; 
	float shininess;
	
	sampler2D normalMapTexture;
	
	vec4 reflectionColor;
	vec4 refractionColor;
	
	float transparency;
	
	samplerCube dynamicCubeMapTexture;
};

uniform	MaterialProperties u_material;

uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_modelMatrix;

uniform mat3 u_normalModelMatrix;

uniform float u_displacementScale;

in vec4 v_g_vertex[];
in vec3 v_g_tangent[];
in vec3 v_g_bitangent[];
in vec3 v_g_normal[];
in vec2 v_g_texCoord[];

out vec4 v_vertex;
out vec3 v_tangent;
out vec3 v_bitangent;
out vec3 v_normal;
out vec2 v_texCoord;

void main(void)
{
	for(int i = 0; i < gl_in.length(); ++i)
	{
		v_tangent = u_normalModelMatrix * v_g_tangent[i];
		v_bitangent = u_normalModelMatrix * v_g_bitangent[i];
		v_normal = u_normalModelMatrix * v_g_normal[i];
		v_texCoord = v_g_texCoord[i];
		
		float displacementOffset = texture(u_material.normalMapTexture, v_texCoord).a * u_displacementScale;
		vec4 displacement = vec4(normalize(v_g_normal[i]) * displacementOffset, 0.0);

		v_vertex = u_modelMatrix * (gl_in[i].gl_Position + displacement);

		gl_Position = u_projectionMatrix * u_viewMatrix * v_vertex;

		EmitVertex();
	}
	
	EndPrimitive();
}
