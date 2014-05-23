/*
 * FontManager.cpp
 *
 *  Created on: 16.09.2012
 *      Author: nopper
 */

#include "FontManager.h"

using namespace std;

FontManager::FontManager() :
		Singleton<FontManager>()
{
}

FontManager::~FontManager()
{
	auto walker = allFonts.begin();
	while (walker != allFonts.end())
	{
		walker->second.reset();
		walker++;
	}
	allFonts.clear();
}

const FontSP& FontManager::getFont(const string& key)
{
	return allFonts[key];
}

void FontManager::setFont(const string& key, const FontSP& font)
{
	allFonts[key] = font;
}
