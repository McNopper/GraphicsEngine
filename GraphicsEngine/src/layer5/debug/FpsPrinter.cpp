/*
 * FpsPrinter.cpp
 *
 *  Created on: 28.09.2012
 *      Author: nopper
 */

#include "../../layer4/font/Font.h"
#include "../../layer4/font/FontManager.h"

#include "FpsPrinter.h"

FpsPrinter FpsPrinter::printer = FpsPrinter();

FpsPrinter::FpsPrinter() :
		fontColor(Color(1.0f, 0.0f, 0.0f, 1.0f))
{
}

FpsPrinter::~FpsPrinter()
{
}

void FpsPrinter::print(float deltaTime)
{
	frameCounter.increaseElapsedTime(deltaTime);
	FontSP currentFont = FontManager::getInstance()->getFont("CourierNew");
	currentFont->print(10.0f, 10.0f, fontColor,
			frameCounter.calculateFramesPerSecondAsString());
	frameCounter.increaseNumberFrames();
}

const Color& FpsPrinter::getFontColor() const
{
	return fontColor;
}

void FpsPrinter::setFontColor(const Color& fontColor)
{
	this->fontColor = fontColor;
}
