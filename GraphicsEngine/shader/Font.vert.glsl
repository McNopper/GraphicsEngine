#version 410 core

uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_modelMatrix;

uniform float u_fontLeft;
uniform float u_fontTop;
uniform float u_fontWidth;
uniform float u_fontHeight;

in vec4 a_vertex;
in vec2 a_texCoord;

out vec2 v_texCoord;

void main(void)
{
	v_texCoord = vec2(u_fontLeft + u_fontWidth * a_texCoord.s, u_fontTop + u_fontHeight * a_texCoord.t);

	gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * a_vertex;
}
