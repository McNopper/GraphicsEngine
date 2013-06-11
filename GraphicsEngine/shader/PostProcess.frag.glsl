#version 410 core

// Depth of Field
// http://en.wikipedia.org/wiki/Circle_of_confusion#Determining_a_circle_of_confusion_diameter_from_the_object_field
// http://en.wikipedia.org/wiki/Thin_lens

uniform int u_numberSamples;

uniform sampler2D u_screenTexture;
uniform sampler2DMS u_screenTextureMS;
uniform sampler2D u_depthTexture;
uniform sampler2DMS u_depthTextureMS;
uniform sampler2D u_bloomTexture;
uniform sampler2DMS u_bloomTextureMS;
uniform sampler1DArray u_blurTexture;

uniform int u_useDoF;
uniform float u_aperture;
uniform float u_focal;
uniform float u_focusedObject;

uniform int u_useMS;

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

vec4 textureMultisample(sampler2DMS sampler, ivec2 ipos)
{
	vec4 color = vec4(0.0);
	
	for (int i = 0; i < u_numberSamples; i++)
	{
		color += texelFetch(sampler, ipos, i);
	}
	
	color /= float(u_numberSamples);
	
	return color;
}

vec4 blur(int texWidthBlur, float blurTextureIndex)
{
	vec4 blurred = vec4(0.0);
	
	int spixel = 0;
	int tpixel = 0;
	
	float convolution;

	vec2 texCoord;
	ivec2 maxDimension;	
	
	if (u_useMS > 0)
	{
		vec2 textureDimension = textureSize(u_screenTextureMS);
	
		texCoord = floor(textureDimension * v_texCoord);
		
		maxDimension.s = int(textureDimension.s);	
		maxDimension.t = int(textureDimension.t);
	}
	
	if (u_blurHorizontal != 0)
	{
		spixel = texWidthBlur;
	}
	if (u_blurVertical != 0)
	{
		tpixel = texWidthBlur;
	}
	
	for (int s = -spixel; s <= spixel; s++)
	{
		for (int t = -tpixel; t <= tpixel; t++)
		{
			convolution = 1.0;
			
			if (u_blurHorizontal != 0)
			{
				convolution *= texture(u_blurTexture, vec2(v_texWidthBlurStep*float(s+spixel+1), blurTextureIndex)).r;
			}
			if (u_blurVertical != 0)
			{
				convolution *= texture(u_blurTexture, vec2(v_texWidthBlurStep*float(t+tpixel+1), blurTextureIndex)).r;
			}
			
			if (u_useMS > 0)
			{
				ivec2 ipos = ivec2(int(texCoord.s + float(s)), int(texCoord.t + float(t)));
				
				if (ipos.s < 0)
				{
					ipos.s = 0;
				}
				else if (ipos.s >= maxDimension.s)
				{
					ipos.s = maxDimension.s - 1;
				}
				if (ipos.t < 0)
				{
					ipos.t = 0;
				}
				else if (ipos.t >= maxDimension.t)
				{
					ipos.t = maxDimension.t - 1;
				}
			
				blurred += textureMultisample(u_screenTextureMS, ipos) * convolution;
			}
			else
			{
				blurred += texture(u_screenTexture, vec2(v_texCoord.s + v_texCoordStep.s*float(s), v_texCoord.t + v_texCoordStep.t*float(t))) * convolution;
			}
		}		
	}

    return blurred;
}

void main(void)
{
	bool doDefault = true;

	vec4 color;

	float focusDifference = u_focusedObject - u_focal;
	if (u_useDoF != 0 && focusDifference > 0.0)
	{
		// Depth of Field
		
		// Get from depth texture
		float unfocusedObject = 0.0;
		
		if (u_useMS > 0)
		{
			ivec2 texCoord = ivec2(floor(textureSize(u_depthTextureMS) * v_texCoord));
			
			unfocusedObject = texelFetch(u_depthTextureMS, texCoord, 0).x;
		}
		else
		{
			unfocusedObject = texture(u_depthTexture, v_texCoord).x;
		}
		
		if (unfocusedObject > 0.0)
		{		
			int CoCRadius = int((u_aperture * abs(unfocusedObject - u_focusedObject)/unfocusedObject * u_focal/focusDifference) / 2.0);
		
			int maxCoCRadius = v_texWidthBlur / 2;
		
			int cocRadiusReduction = clamp(maxCoCRadius - CoCRadius, 0, maxCoCRadius);
		
			if (cocRadiusReduction < maxCoCRadius)
			{
				// Blur depending on DOF
				color = blur(maxCoCRadius - cocRadiusReduction, float(cocRadiusReduction));
				
				doDefault = false;
			}
		}
	}
	else if (u_useBlur != 0)
	{
		doDefault = false;
	
		// Blurring
		color = blur(v_texWidthBlur/2, 0.0);
	}
	
	if (doDefault)
	{
		// Default
		if (u_useMS > 0)
		{
			ivec2 texCoord = ivec2(floor(textureSize(u_screenTextureMS) * v_texCoord));

			color = textureMultisample(u_screenTextureMS, texCoord);
		}
		else
		{
			color = texture(u_screenTexture, v_texCoord);
		}
	}

	if (u_useBloom != 0)
	{
		if (u_useMS > 0)
		{
			ivec2 texCoord = ivec2(floor(textureSize(u_bloomTextureMS) * v_texCoord));
	
			color += textureMultisample(u_bloomTextureMS, texCoord) * u_bloomLevel;
		}
		else
		{
			color += texture(u_bloomTexture, v_texCoord) * u_bloomLevel;
		}
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
