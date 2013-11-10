#version 410 core

layout(triangles, invocations = 6) in;

layout(triangle_strip, max_vertices = 3) out;

#define NUMBER_FACES 6

uniform mat4 u_cubeMapProjectionMatrix;
uniform mat4 u_cubeMapViewMatrix[NUMBER_FACES];

uniform	int u_numberLights;

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
    gl_Layer = gl_InvocationID;

	mat4 faceMatrix = u_cubeMapProjectionMatrix * u_cubeMapViewMatrix[gl_InvocationID];

	vec4 finalPosition[3];
	vec4 ndcPosition[3];

	// Calculate the NDC coordinates
	for(int i = 0; i < gl_in.length(); ++i)
	{
		finalPosition[i] = faceMatrix * gl_in[i].gl_Position;
		
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
	
	// If we get so far, emit the the vertices and the primitive
	
	for(int i = 0; i < gl_in.length(); ++i)
	{
		v_vertex = v_g_vertex[i];
		v_normal = v_g_normal[i];
		v_bitangent = v_g_bitangent[i];
		v_tangent = v_g_tangent[i];
		v_texCoord = v_g_texCoord[i];
		
		gl_Position = finalPosition[i]; 
		EmitVertex();
	}
	
	EndPrimitive();
}
