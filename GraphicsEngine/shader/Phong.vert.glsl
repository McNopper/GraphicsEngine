#version 410 core

#define MAX_SKIN_INDICES 8
#define MAX_MATRICES 64

uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_modelMatrix;
uniform mat3 u_normalModelMatrix;

uniform mat4 u_bindMatrix[MAX_MATRICES];
uniform mat3 u_bindNormalMatrix[MAX_MATRICES];
uniform mat4 u_inverseBindMatrix[MAX_MATRICES];
uniform mat3 u_inverseBindNormalMatrix[MAX_MATRICES];

uniform int u_hasSkinning;
uniform	int u_hasDiffuseTexture;
uniform	int u_hasNormalMapTexture;

uniform	int u_numberLights;

in vec4 a_vertex;
in vec3 a_normal;
in vec3 a_bitangent;
in vec3 a_tangent;
in vec2 a_texCoord;

in vec4 a_boneIndex_0;
in vec4 a_boneIndex_1;
in vec4 a_boneWeight_0;
in vec4 a_boneWeight_1;
in float a_boneCounter;

out vec4 v_vertex;
out vec3 v_normal;
out vec3 v_bitangent;
out vec3 v_tangent;
out vec2 v_texCoord;

void main(void)
{
	vec4 vertex = vec4(0.0);
	vec3 normal = vec3(0.0);
	vec3 bitangent = vec3(0.0);
	vec3 tangent = vec3(0.0);

	int boneCounter;

	int currentBone;
	float currentWeight;

	if (u_hasSkinning == 0)
	{
		vertex = a_vertex;
		normal = a_normal;
		
		if (u_hasNormalMapTexture != 0)
		{
			bitangent = a_bitangent;
			tangent = a_tangent;
		}
	}
	else
	{
	 	boneCounter = int(a_boneCounter);
	
		if (boneCounter == 0)
		{
			vertex = a_vertex;
			normal = a_normal;
			
			if (u_hasNormalMapTexture != 0)
			{
				bitangent = a_bitangent;
				tangent = a_tangent;
			}
		}
		else
		{		
			for (int i = 0; i < boneCounter; i++)
			{
				if (i < 4)
				{
					currentBone = int(a_boneIndex_0[i]);
					currentWeight = a_boneWeight_0[i];
				}
				else
				{
					currentBone = int(a_boneIndex_1[i-4]);
					currentWeight = a_boneWeight_1[i-4];
				}
				
				vertex += (u_bindMatrix[currentBone] * u_inverseBindMatrix[currentBone] * a_vertex) * currentWeight;
				
				normal += (u_bindNormalMatrix[currentBone] * u_inverseBindNormalMatrix[currentBone] * a_normal) * currentWeight;

				if (u_hasNormalMapTexture != 0)
				{
					bitangent += (u_bindNormalMatrix[currentBone] * u_inverseBindNormalMatrix[currentBone] * a_bitangent) * currentWeight;
					tangent += (u_bindNormalMatrix[currentBone] * u_inverseBindNormalMatrix[currentBone] * a_tangent) * currentWeight;
				}
			}
		}
	}

	v_vertex = u_modelMatrix * vertex;

	v_normal = u_normalModelMatrix * normal;
	
	if (u_hasNormalMapTexture != 0)
	{
		v_bitangent = u_normalModelMatrix * bitangent;
		v_tangent = u_normalModelMatrix * tangent;
	}
	
	if (u_hasDiffuseTexture != 0 || u_hasNormalMapTexture != 0)
	{
		v_texCoord = a_texCoord;
	}
	
	gl_Position = u_projectionMatrix * u_viewMatrix * v_vertex;	
}
