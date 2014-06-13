/*
 * PostProcessorVAO.h
 *
 *  Created on: 29.11.2012
 *      Author: nopper
 */

#ifndef POSTPROCESSORVAO_H_
#define POSTPROCESSORVAO_H_

#include "../../layer1/shader/Program.h"
#include "../../layer1/shader/VAO.h"

class PostProcessor;

class PostProcessorVAO : public VAO
{
public:
	PostProcessorVAO(const ProgramSP& program, const PostProcessor& postProcessor);
	virtual ~PostProcessorVAO();
};

typedef std::shared_ptr<PostProcessorVAO> PostProcessorVAOSP;

#endif /* POSTPROCESSORVAO_H_ */
