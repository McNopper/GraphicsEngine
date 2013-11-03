#version 410 core

uniform sampler2D u_fontTexture;
uniform vec4 u_fontColor;

in vec2 v_texCoord;

layout(location = 0, index = 0) out vec4 fragColor;

void main(void)
{
	fragColor = texture(u_fontTexture, v_texCoord) * u_fontColor;
}
