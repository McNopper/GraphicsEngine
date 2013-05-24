/*
 * FontManager.cpp
 *
 *  Created on: 16.09.2012
 *      Author: nopper
 */

#include "FontManager.h"

using namespace std;

FontManager* FontManager::instance;

FontManager::FontManager() {
}

FontManager::~FontManager() {
	auto walker = allFonts.begin();
	while (walker != allFonts.end())
	{
		walker->second.reset();
		walker++;
	}
	allFonts.clear();
}

FontManager* FontManager::getInstance()
{
	if (!instance)
	{
		instance = new FontManager();
	}

	return instance;}

void FontManager::terminate()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}

const FontSP& FontManager::getFont(const string& key)
{
	return allFonts[key];
}

void FontManager::setFont(const string& key, const FontSP& font)
{
	allFonts[key] = font;
}
