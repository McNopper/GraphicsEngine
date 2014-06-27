/*
 * Interpolator.h
 *
 *  Created on: 31.08.2012
 *      Author: nopper
 */

#ifndef INTERPOLATOR_H_
#define INTERPOLATOR_H_

#include "../../UsedLibs.h"

class Interpolator
{

private:

	std::string name;

	std::int32_t id;

protected:

	Interpolator(const std::string& name, std::int32_t id) : name(name), id(id)
	{

	}

	virtual ~Interpolator()
	{

	}

public:

	virtual float interpolate(const std::map<float, float>& table, float time) const = 0;

	const std::string& getName() const
	{
		return name;
	}

	std::int32_t getId() const
	{
		return id;
	}

};

#endif /* INTERPOLATOR_H_ */
