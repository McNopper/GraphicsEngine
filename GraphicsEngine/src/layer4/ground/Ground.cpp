/*
 * Ground.cpp
 *
 *  Created on: 16.05.2013
 *      Author: nopper
 */

#include "Ground.h"

Ground::Ground(const BoundingSphere& boundingSphere) :
		boundingSphere(boundingSphere)
{
}

Ground::~Ground()
{
}

const BoundingSphere& Ground::getBoundingSphere() const
{
	return boundingSphere;
}

