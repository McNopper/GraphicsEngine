#version 410 core

uniform samplerCube u_cubemap;

uniform	int u_writeBrightColor;
uniform	float u_brightColorLimit;

in vec3 v_ray;

layout(location = 0, index = 0) out vec4 fragColor;
layout(location = 1, index = 0) out vec4 brightColor;

void main(void)
{
	vec4 color = texture(u_cubemap, v_ray); 

	fragColor = color;

	if (u_writeBrightColor > 0)
	{
		vec3 tempBrightColor = max(color.rgb - vec3(u_brightColorLimit), vec3(0.0));
		
		float bright = dot(tempBrightColor, vec3(1.0));
		bright = smoothstep(0.0, 0.5, bright);
	
		brightColor.rgb = mix(vec3(0.0), color.rgb, bright).rgb; 
	
		brightColor.a = 1.0; 
	}
}
