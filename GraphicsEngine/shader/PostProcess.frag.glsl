#version 420 core

uniform sampler2D u_screenTexture;
uniform sampler2D u_bloomTexture;
uniform sampler1D u_blurTexture;

uniform int u_useBlur;
uniform int u_blurHorizontal;
uniform int u_blurVertical;

uniform int u_useBloom;
uniform float u_bloomLevel;

uniform int u_useExposure;
uniform float u_exposure;

uniform int u_useGamma;
uniform float u_gamma;

in vec2 v_texCoord;
flat in vec2 v_texCoordStep;

flat in int v_texWidthBlur;
flat in float v_texWidthBlurStep;

layout(location = 0, index = 0) out vec4 fragColor;

vec4 blur()
{
	vec4 blurred = vec4(0.0);
	
	int spixel = 0;
	int tpixel = 0;
	
	float convolution;
	
	if (u_blurHorizontal != 0)
	{
		spixel = v_texWidthBlur/2;
	}
	if (u_blurVertical != 0)
	{
		tpixel = v_texWidthBlur/2;
	}
	
	for (int s = -spixel; s <= spixel; s++)
	{
		for (int t = -tpixel; t <= tpixel; t++)
		{
			convolution = 1.0;
			
			if (u_blurHorizontal != 0)
			{
				convolution *= texture(u_blurTexture, v_texWidthBlurStep*float(s+spixel+1)).r;
			}
			if (u_blurVertical != 0)
			{
				convolution *= texture(u_blurTexture, v_texWidthBlurStep*float(t+tpixel+1)).r;
			}

			blurred += texture(u_screenTexture, vec2(v_texCoord.s + v_texCoordStep.s*float(s), v_texCoord.t + v_texCoordStep.t*float(t))) * convolution;
		}
	}

    return blurred;
}

void main(void)
{
	vec4 color;

	if (u_useBlur != 0)
	{
		color = blur();
	}
	else
	{
		color = texture(u_screenTexture, v_texCoord);
	}

	if (u_useBloom != 0)
	{
		color += texture(u_bloomTexture, v_texCoord) * u_bloomLevel;
	}		
	
	if (u_useExposure != 0)
	{
		color = 1.0 - exp2(-color * u_exposure);
		color.a = 1.0; 
	}

	if (u_useGamma != 0)
	{
		color = pow(color, vec4(1.0 / u_gamma));
		color.a = 1.0; 
	}
	
	fragColor = color;
}
