/*
 * FontManager.h
 *
 *  Created on: 16.09.2012
 *      Author: nopper
 */

#ifndef FONTMANAGER_H_
#define FONTMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer0/stereotype/Singleton.h"

#include "Font.h"

class FontManager : public Singleton<FontManager>
{

	friend class Singleton<FontManager>;

private:

	std::map<std::string, FontSP> allFonts;

	FontManager();
	virtual ~FontManager();

public:

	const FontSP& getFont(const std::string& key);

	void setFont(const std::string& key, const FontSP& font);

};

#endif /* FONTMANAGER_H_ */
