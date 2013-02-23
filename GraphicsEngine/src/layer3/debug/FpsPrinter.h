/*
 * FpsPrinter.h
 *
 *  Created on: 28.09.2012
 *      Author: nopper
 */

#ifndef FPSPRINTER_H_
#define FPSPRINTER_H_

#include "../../layer0/color/Color.h"
#include "../../layer0/statistic/FrameCounter.h"

class FpsPrinter
{

private:

	FrameCounter frameCounter;

	Color fontColor;

	FpsPrinter();
	virtual ~FpsPrinter();

public:

	static FpsPrinter printer;

	void print(float deltaTime);

	const Color& getFontColor() const;
	void setFontColor(const Color& fontColor);

};

#endif /* FPSPRINTER_H_ */
