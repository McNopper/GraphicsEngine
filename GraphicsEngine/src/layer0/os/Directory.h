/*
 * Directory.h
 *
 *  Created on: 01.07.2014
 *      Author: nopper
 */

#ifndef DIRECTORY_H_
#define DIRECTORY_H_

#include "../../UsedLibs.h"

class Directory
{

public:

	Directory();
	~Directory();

	static bool create(const std::string& name);

};

#endif /* DIRECTORY_H_ */
