#version 410 core

layout(triangles, invocations = 6) in;

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

#define NUMBER_FACES 6

uniform mat4 u_cubeMapProjectionMatrix;
uniform mat4 u_cubeMapViewMatrix[NUMBER_FACES];

uniform	MaterialProperties u_material;

uniform	int u_numberLights;

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
    gl_Layer = gl_InvocationID;

	mat4 faceMatrix = u_cubeMapProjectionMatrix * u_cubeMapViewMatrix[gl_InvocationID];

	vec4 finalPosition[3];
	vec4 ndcPosition[3];

	// Calculate the NDC coordinates
	for(int i = 0; i < gl_in.length(); ++i)
	{
		finalPosition[i] = faceMatrix * u_modelMatrix * gl_in[i].gl_Position;
		
		ndcPosition[i] = finalPosition[i]; 
		
		if (ndcPosition[i].w != 0.0)
		{
			ndcPosition[i] /= ndcPosition[i].w; 
		}
	}

	int greaterX = 0;
	int lessX = 0;
	int greaterY = 0;
	int lessY = 0;
	int greaterZ = 0;
	int lessZ = 0;
	
	// Count, how often a coordinate is outside the view frustum 
	for (int i = 0; i < 3; i++)
	{
		if (ndcPosition[i].x < -1.0)
		{
			lessX++;
		}
		else if (ndcPosition[i].x > 1.0)
		{
			greaterX++;
		}

		if (ndcPosition[i].y < -1.0)
		{
			lessY++;
		}
		else if (ndcPosition[i].y > 1.0)
		{
			greaterY++;
		}

		if (ndcPosition[i].z < -1.0)
		{
			lessZ++;
		}
		else if (ndcPosition[i].z > 1.0)
		{
			greaterZ++;
		}
	}
	
	// If one of the counter is 3, the primitive is for sure not in the view frustum
	if (lessX == 3 || greaterX == 3 || lessY == 3 || greaterY == 3 || lessZ == 3 || greaterZ == 3)
	{
		return;
	}

	//

	for(int i = 0; i < gl_in.length(); ++i)
	{
		v_tangent = u_normalModelMatrix * v_g_tangent[i];
		v_bitangent = u_normalModelMatrix * v_g_bitangent[i];
		v_normal = u_normalModelMatrix * v_g_normal[i];
		v_texCoord = v_g_texCoord[i];
		
		float displacementOffset = texture(u_material.normalMapTexture, v_texCoord).a * u_displacementScale;
		vec4 displacement = vec4(normalize(v_g_normal[i]) * displacementOffset, 0.0);

		v_vertex = u_modelMatrix * (gl_in[i].gl_Position + displacement);

		gl_Position = faceMatrix * v_vertex;

		EmitVertex();
	}
	
	EndPrimitive();
}
