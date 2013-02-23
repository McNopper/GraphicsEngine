/*
 * FontFactory.cpp
 *
 *  Created on: 21.09.2012
 *      Author: nopper
 */

#include "Font.h"
#include "FontManager.h"

#include "FontFactory.h"

FontFactory::FontFactory()
{
}

FontFactory::~FontFactory()
{
}

void FontFactory::createDefaultFont() const
{
	FontSP font = FontSP(new Font("CourierNew.tga", 512.0f, 512.0f, 16, 16, 32.0f, 18.0f, 10.0f, 16.0f));
	FontManager::getInstance()->setFont("CourierNew", font);
}
