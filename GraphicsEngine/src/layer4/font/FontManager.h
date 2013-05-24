/*
 * FontManager.h
 *
 *  Created on: 16.09.2012
 *      Author: nopper
 */

#ifndef FONTMANAGER_H_
#define FONTMANAGER_H_

#include "../../UsedLibs.h"

#include "Font.h"

class FontManager {
private:

	static FontManager* instance;

	std::map<std::string, FontSP> allFonts;

	FontManager();
	virtual ~FontManager();

public:

	static FontManager* getInstance();

	static void terminate();

	const FontSP& getFont(const std::string& key);

	void setFont(const std::string& key, const FontSP& font);

};

#endif /* FONTMANAGER_H_ */
