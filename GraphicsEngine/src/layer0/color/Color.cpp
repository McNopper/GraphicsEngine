/*
 * Color.cpp
 *
 *  Created on: 27.04.2011
 *      Author: Norbert Nopper
 */

#include "Color.h"

const Color Color::WHITE = Color(1.0f, 1.0f, 1.0f, 1.0f);
const Color Color::WHITE_TRANSPARENT = Color(1.0f, 1.0f, 1.0f, 0.0f);
const Color Color::BLACK = Color(0.0f, 0.0f, 0.0f, 1.0f);
const Color Color::BLACK_TRANSPARENT = Color(0.0f, 0.0f, 0.0f, 0.0f);
const Color Color::RED = Color(1.0f, 0.0f, 0.0f, 1.0f);
const Color Color::RED_TRANSPARENT = Color(1.0f, 0.0f, 0.0f, 0.0f);
const Color Color::GREEN = Color(0.0f, 1.0f, 0.0f, 1.0f);
const Color Color::GREEN_TRANSPARENT = Color(0.0f, 1.0f, 0.0f, 0.0f);
const Color Color::BLUE = Color(0.0f, 0.0f, 1.0f, 1.0f);
const Color Color::BLUE_TRANSPARENT = Color(0.0f, 0.0f, 1.0f, 0.0f);
const Color Color::YELLOW = Color(1.0f, 1.0f, 0.0f, 1.0f);
const Color Color::YELLOW_TRANSPARENT = Color(1.0f, 1.0f, 0.0f, 0.0f);
const Color Color::MAGENTA = Color(1.0f, 0.0f, 1.0f, 1.0f);
const Color Color::MAGENTA_TRANSPARENT = Color(1.0f, 0.0f, 1.0f, 0.0f);
const Color Color::CYAN = Color(0.0f, 1.0f, 1.0f, 1.0f);
const Color Color::CYAN_TRANSPARENT = Color(0.0f, 1.0f, 1.0f, 0.0f);
const Color Color::BRIGHT_GREY = Color(0.75f, 0.75f, 0.75f, 1.0f);
const Color Color::BRIGHT_GREY_TRANSPARENT = Color(0.75f, 0.75f, 0.75f, 0.0f);
const Color Color::GREY = Color(0.5f, 0.5f, 0.5f, 1.0f);
const Color Color::GREY_TRANSPARENT = Color(0.5f, 0.5f, 0.5f, 0.0f);
const Color Color::DARK_GREY = Color(0.25f, 0.25f, 0.25f, 1.0f);
const Color Color::DARK_GREY_TRANSPARENT = Color(0.25f, 0.25f, 0.25f, 0.0f);

const Color Color::DEFAULT_EMISSIVE = Color(0.0f, 0.0f, 0.0f, 1.0f);
const Color Color::DEFAULT_AMBIENT = Color(0.2f, 0.2f, 0.2f, 1.0f);
const Color Color::DEFAULT_DIFFUSE = Color(0.8f, 0.8f, 0.8f, 1.0f);
const Color Color::DEFAULT_SPECULAR = Color(0.0f, 0.0f, 0.0f, 1.0f);
const Color Color::DEFAULT_REFLECTION = Color(0.0f, 0.0f, 0.0f, 1.0f);
const Color Color::DEFAULT_REFRACTION = Color(0.0f, 0.0f, 0.0f, 1.0f);

Color::Color()
{
	this->rgba[0] = 0.0f;
	this->rgba[1] = 0.0f;
	this->rgba[2] = 0.0f;
	this->rgba[3] = 1.0f;
}

Color::Color(float luminance)
{
	this->rgba[0] = luminance;
	this->rgba[1] = luminance;
	this->rgba[2] = luminance;
	this->rgba[3] = 1.0f;
}

Color::Color(uint8_t luminance)
{
	float luminancef = (float)luminance / 255.0f;

	this->rgba[0] = luminancef;
	this->rgba[1] = luminancef;
	this->rgba[2] = luminancef;
	this->rgba[3] = 1.0f;
}

Color::Color(float r, float g, float b)
{
	this->rgba[0] = r;
	this->rgba[1] = g;
	this->rgba[2] = b;
	this->rgba[3] = 1.0f;
}

Color::Color(uint8_t r, uint8_t g, uint8_t b)
{
	this->rgba[0] = (float)r / 255.0f;
	this->rgba[1] = (float)g / 255.0f;
	this->rgba[2] = (float)b / 255.0f;
	this->rgba[3] = 1.0f;
}

Color::Color(float r, float g, float b, float a)
{
	this->rgba[0] = r;
	this->rgba[1] = g;
	this->rgba[2] = b;
	this->rgba[3] = a;
}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	this->rgba[0] = (float)r / 255.0f;
	this->rgba[1] = (float)g / 255.0f;
	this->rgba[2] = (float)b / 255.0f;
	this->rgba[3] = (float)a / 255.0f;
}

Color::Color(const float rgba[4])
{
	this->rgba[0] = rgba[0];
	this->rgba[1] = rgba[1];
	this->rgba[2] = rgba[2];
	this->rgba[3] = rgba[3];
}

Color::Color(const uint8_t rgba[4])
{
	this->rgba[0] = (float)rgba[0] / 255.0f;
	this->rgba[1] = (float)rgba[1] / 255.0f;
	this->rgba[2] = (float)rgba[2] / 255.0f;
	this->rgba[3] = (float)rgba[3] / 255.0f;
}

Color::Color(const Color& other)
{
	this->rgba[0] = other.rgba[0];
	this->rgba[1] = other.rgba[1];
	this->rgba[2] = other.rgba[2];
	this->rgba[3] = other.rgba[3];
}

Color::~Color()
{
}

void Color::setR(float r)
{
	rgba[0] = r;
}

float Color::getR() const
{
	return rgba[0];
}

void Color::setG(float g)
{
	rgba[1] = g;
}

float Color::getG() const
{
	return rgba[1];
}

void Color::setB(float b)
{
	rgba[2] = b;
}

float Color::getB() const
{
	return rgba[2];
}

void Color::setA(float a)
{
	rgba[3] = a;
}

float Color::getA() const
{
	return rgba[3];
}

void Color::setRGBA(float value, int32_t index)
{
	rgba[index] = value;
}

float Color::getRGBA(int32_t index) const
{
	return rgba[index];
}

const float* Color::getRGBA() const
{
	return rgba;
}

void Color::setLuminance(float luminance)
{
	rgba[0] = luminance;
	rgba[1] = luminance;
	rgba[2] = luminance;
	rgba[3] = 1.0f;
}

void Color::setLuminance(uint8_t luminance)
{
	float luminancef = (float)luminance / 255.0f;

	this->rgba[0] = luminancef;
	this->rgba[1] = luminancef;
	this->rgba[2] = luminancef;
	this->rgba[3] = 1.0f;
}

void Color::setRGBA(float r, float g, float b, float a)
{
	rgba[0] = r;
	rgba[1] = g;
	rgba[2] = b;
	rgba[3] = a;
}

void Color::setRGBA(const float rgba[4])
{
	this->rgba[0] = rgba[0];
	this->rgba[1] = rgba[1];
	this->rgba[2] = rgba[2];
	this->rgba[3] = rgba[3];
}

void Color::setRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	this->rgba[0] = (float)r / 255.0f;
	this->rgba[1] = (float)g / 255.0f;
	this->rgba[2] = (float)b / 255.0f;
	this->rgba[3] = (float)a / 255.0f;
}

void Color::setRGBA(const uint8_t rgba[4])
{
	this->rgba[0] = (float)rgba[0] / 255.0f;
	this->rgba[1] = (float)rgba[1] / 255.0f;
	this->rgba[2] = (float)rgba[2] / 255.0f;
	this->rgba[3] = (float)rgba[3] / 255.0f;
}
