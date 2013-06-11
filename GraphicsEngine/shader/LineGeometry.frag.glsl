#version 410 core

uniform vec4 u_lineGeometryColor;

layout(location = 0, index = 0) out vec4 fragColor;

void main(void)
{
	fragColor = u_lineGeometryColor;
}
