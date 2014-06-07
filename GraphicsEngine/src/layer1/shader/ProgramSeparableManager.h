/*
 * ProgramSeparableManager.h
 *
 *  Created on: 06.06.2014
 *      Author: nopper
 */

#ifndef PROGRAMSEPARABLEMANAGER_H_
#define PROGRAMSEPARABLEMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer0/stereotype/KeyValueMap.h"
#include "../../layer0/stereotype/Singleton.h"

#include "ProgramSeparable.h"

class ProgramSeparableManager : public Singleton<ProgramSeparableManager>
{

	friend class Singleton<ProgramSeparableManager>;

private:

	KeyValueMap<std::string, ProgramSeparableSP> allProgramSeparables;

private:

	ProgramSeparableManager();
	virtual ~ProgramSeparableManager();

public:

	void addProgramSeparable(const ProgramSeparableSP& programSeparable);

	void removeProgramSeparable(const ProgramSeparableSP& programSeparable);

	ProgramSeparableSP getProgramSeparableBy(const std::string& filename) const;

	const KeyValueMap<std::string, ProgramSeparableSP>& getAllProgramSeparables() const;

};

#endif /* PROGRAMSEPARABLEMANAGER_H_ */
