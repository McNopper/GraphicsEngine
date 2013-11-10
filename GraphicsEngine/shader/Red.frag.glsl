#version 410 core

#define MAX_LIGHT_SECTIONS 3
#define MAX_LIGHTS 4

#define ALPHA_FACTOR 2.0

struct LightProperties
{
	vec4 diffuseColor;
	vec4 specularColor;
		
	vec3 direction;

	vec4 position;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
	
	vec3 spotDirection;
	float spotCosCutOff;
	float spotCosCutOffOuter;
};

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

uniform	vec4 u_ambientLightColor;


uniform	LightProperties u_light[MAX_LIGHTS];

uniform	MaterialProperties u_material;

uniform	float u_eta;
uniform	float u_reflectanceNormalIncidence;

uniform	int u_numberLights;
uniform	int u_lightType[MAX_LIGHTS];
uniform	int u_hasDiffuseTexture;
uniform	int u_hasSpecularTexture;
uniform	int u_hasNormalMapTexture;
uniform	int u_hasCubeMapTexture;
uniform	int u_hasDynamicCubeMapTexture;

uniform int u_convertDirectX;

uniform	int u_writeBrightColor;
uniform	float u_brightColorLimit;

uniform vec4 u_eyePosition;

uniform samplerCube u_cubemap;

uniform	int u_shadowType[MAX_LIGHTS];
uniform mat4 u_shadowMatrix[MAX_LIGHTS * MAX_LIGHT_SECTIONS];
uniform sampler2DArrayShadow u_shadowTexture[MAX_LIGHTS];
uniform float u_shadowSections[MAX_LIGHTS];
uniform vec4 u_frustumZs;

in vec4 v_vertex;
in vec3 v_normal;
in vec3 v_bitangent;
in vec3 v_tangent;
in vec2 v_texCoord;

layout(location = 0, index = 0) out vec4 fragColor;
layout(location = 1, index = 0) out vec4 brightColor;

void main(void)
{
	fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
