/*
 * NodeOwner.h
 *
 *  Created on: 12.09.2012
 *      Author: nopper
 */

#ifndef NODEOWNER_H_
#define NODEOWNER_H_

#include "../../UsedLibs.h"

#include "../../layer0/math/Matrix3x3.h"
#include "../../layer0/math/Matrix4x4.h"

class NodeOwner {
public:
	NodeOwner()
	{
	}

	virtual ~NodeOwner()
	{
	}

	virtual const std::string& getCurrentProgramType() const = 0;

	virtual boost::int32_t getNumberJoints() const = 0;

    virtual const Matrix4x4* getBindMatrices() const = 0;
    virtual const Matrix3x3* getBindNormalMatrices() const = 0;
    virtual const Matrix4x4* getJointMatrices() const = 0;
    virtual const Matrix3x3* getJointNormalMatrices() const = 0;

    virtual bool isWriteBrightColor() const = 0;
    virtual float getBrightColorLimit() const = 0;

    virtual float getRefractiveIndex() const = 0;

};

#endif /* NODEOWNER_H_ */
