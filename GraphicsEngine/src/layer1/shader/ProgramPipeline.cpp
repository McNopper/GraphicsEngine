/*
 * ProgramPipeline.cpp
 *
 *  Created on: 27.05.2014
 *      Author: nopper
 */

#include "ProgramPipeline.h"

using namespace std;

ProgramPipeline *ProgramPipeline::lastUsedProgramPipeline = 0;

void ProgramPipeline::off()
{
	glBindProgramPipeline(0);

	lastUsedProgramPipeline = 0;
}

ProgramPipeline::ProgramPipeline(const string& name, const string& type, const ProgramSeparableSP& computeProgramSeparable) :
		name(name), type(type), computeProgramSeparable(computeProgramSeparable), vertexProgramSeparable(), controlProgramSeparable(), evaluationProgramSeparable(), geometryProgramSeparable(), fragmentProgramSeparable()
{
	glusProgramPipelineBuildCompute(&programpipeline, computeProgramSeparable->getProgram());
}

ProgramPipeline::ProgramPipeline(const string& name, const string& type, const ProgramSeparableSP& vertexProgramSeparable, const ProgramSeparableSP& fragmentProgramSeparable) :
		name(name), type(type), computeProgramSeparable(), vertexProgramSeparable(vertexProgramSeparable), controlProgramSeparable(), evaluationProgramSeparable(), geometryProgramSeparable(), fragmentProgramSeparable(fragmentProgramSeparable)
{
	glusProgramPipelineBuild(&programpipeline, vertexProgramSeparable->getProgram(), 0, 0, 0, vertexProgramSeparable->getProgram());
}

ProgramPipeline::ProgramPipeline(const string& name, const string& type, const ProgramSeparableSP& vertexProgramSeparable, ProgramSeparableSP& geometryProgramSeparable, ProgramSeparableSP& fragmentProgramSeparable) :
		name(name), type(type), computeProgramSeparable(), vertexProgramSeparable(vertexProgramSeparable), controlProgramSeparable(), evaluationProgramSeparable(), geometryProgramSeparable(geometryProgramSeparable), fragmentProgramSeparable(fragmentProgramSeparable)
{
	glusProgramPipelineBuild(&programpipeline, vertexProgramSeparable->getProgram(), 0, 0, geometryProgramSeparable->getProgram(), vertexProgramSeparable->getProgram());
}

ProgramPipeline::ProgramPipeline(const string& name, const string& type, const ProgramSeparableSP& vertexProgramSeparable, const ProgramSeparableSP& controlProgramSeparable, const ProgramSeparableSP& evaluationProgramSeparable, const ProgramSeparableSP& geometryProgramSeparable, const ProgramSeparableSP& fragmentProgramSeparable) :
		name(name), type(type), computeProgramSeparable(), vertexProgramSeparable(vertexProgramSeparable), controlProgramSeparable(controlProgramSeparable), evaluationProgramSeparable(evaluationProgramSeparable), geometryProgramSeparable(geometryProgramSeparable), fragmentProgramSeparable(fragmentProgramSeparable)
{
	glusProgramPipelineBuild(&programpipeline, vertexProgramSeparable->getProgram(), controlProgramSeparable->getProgram(), evaluationProgramSeparable->getProgram(), geometryProgramSeparable->getProgram(), vertexProgramSeparable->getProgram());
}

ProgramPipeline::~ProgramPipeline()
{
	if (programpipeline.pipeline)
	{
		if (lastUsedProgramPipeline == this)
		{
			off();
		}

		glusProgramPipelineDestroy(&programpipeline);
	}
}

void ProgramPipeline::use()
{
	if (lastUsedProgramPipeline != this)
	{
		glBindProgramPipeline(programpipeline.pipeline);

		lastUsedProgramPipeline = this;
	}
}

const string& ProgramPipeline::getName() const
{
	return name;
}

const string& ProgramPipeline::getType() const
{
	return type;
}

bool ProgramPipeline::hasComputeProgramSeparable() const
{
	return computeProgramSeparable.get() != nullptr;
}

const ProgramSeparableSP& ProgramPipeline::getComputeProgramSeparable() const
{
	return computeProgramSeparable;
}

bool ProgramPipeline::hasVertexProgramSeparable() const
{
	return vertexProgramSeparable.get() != nullptr;
}

const ProgramSeparableSP& ProgramPipeline::getVertexProgramSeparable() const
{
	return vertexProgramSeparable;
}

bool ProgramPipeline::hasControlProgramSeparable() const
{
	return controlProgramSeparable.get() != nullptr;
}

const ProgramSeparableSP& ProgramPipeline::getControlProgramSeparable() const
{
	return controlProgramSeparable;
}

bool ProgramPipeline::hasEvaluationProgramSeparable() const
{
	return evaluationProgramSeparable.get() != nullptr;
}

const ProgramSeparableSP& ProgramPipeline::getEvaluationProgramSeparable() const
{
	return evaluationProgramSeparable;
}

bool ProgramPipeline::hasGeometryProgramSeparable() const
{
	return geometryProgramSeparable.get() != nullptr;
}

const ProgramSeparableSP& ProgramPipeline::getGeometryProgramSeparable() const
{
	return geometryProgramSeparable;
}

bool ProgramPipeline::hasFragmentProgramSeparable() const
{
	return fragmentProgramSeparable.get() != nullptr;
}

const ProgramSeparableSP& ProgramPipeline::getFragmentProgramSeparable() const
{
	return fragmentProgramSeparable;
}
