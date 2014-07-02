/*
 * GlTfBin.h
 *
 *  Created on: 21.06.2014
 *      Author: nopper
 */

#ifndef GLTFBIN_H_
#define GLTFBIN_H_

#include "../../UsedLibs.h"

class GlTfBin
{

private:

	std::vector<std::uint8_t> data;

	size_t counter;

public:

	GlTfBin();
	virtual ~GlTfBin();

	void addData(const std::uint8_t* data, const size_t length);

	size_t getLength() const;

	size_t getCounter() const;

	const std::uint8_t* getData() const;

	void reset();

};

#endif /* GLTFBIN_H_ */
