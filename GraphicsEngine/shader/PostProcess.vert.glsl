#version 420 core

uniform sampler2D u_screenTexture;
uniform sampler1D u_blurTexture;

uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_modelMatrix;

in vec4 a_vertex;
in vec2 a_texCoord;

out vec2 v_texCoord;
flat out vec2 v_texCoordStep;

flat out int v_texWidthBlur;
flat out float v_texWidthBlurStep;

void main(void)
{
	v_texCoord = a_texCoord;
	
	ivec2 texSize = textureSize(u_screenTexture, 0); 
	v_texCoordStep = vec2(1.0 / float(texSize.s + 1), 1.0 / float(texSize.t + 1));
	
	int texWidth = textureSize(u_blurTexture, 0);
	v_texWidthBlur = texWidth;
	v_texWidthBlurStep = 1.0 / float(texWidth + 1);

	gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * a_vertex;
}
