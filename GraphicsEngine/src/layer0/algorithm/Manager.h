/*
 * Manager.h
 *
 *  Created on: 21.04.2013
 *      Author: nopper
 */

#ifndef MANAGER_H_
#define MANAGER_H_

#include "../../UsedLibs.h"

template<class KEY, class ELEMENT>
class Manager
{

protected:

	static Manager<KEY, ELEMENT>* instance;

	std::map<KEY, ELEMENT> allElements;

	Manager() :
			allElements()
	{

	}

	virtual ~Manager()
	{
		allElements.clear();
	}

public:

	static Manager<KEY, ELEMENT>* getInstance()
	{
		if (!instance)
		{
			instance = new Manager<KEY, ELEMENT>();
		}

		return instance;
	}

	static void terminate()
	{
		if (instance)
		{
			delete instance;

			instance = nullptr;
		}
	}

	void addElement(KEY key, ELEMENT element)
	{
		allElements[key] = element;
	}

	ELEMENT findElement(KEY key)
	{
		ELEMENT result;

		auto walker = allElements.find(key);
		if (walker != allElements.end())
		{
			return allElements[key];
		}

		return result;
	}

	bool removeElement(KEY key)
	{
		auto walker = allElements.find(key);
		if (walker != allElements.end())
		{
			allElements.erase(walker);
		}

		return false;
	}

	bool containsElement(KEY key) const
	{
		return allElements.find(key) != allElements.end();
	}

	const std::map<KEY, ELEMENT>& getAllElements() const
	{
		return allElements;
	}

};

template<class KEY, class ELEMENT>
Manager<KEY, ELEMENT>* Manager<KEY, ELEMENT>::instance = nullptr;

#endif /* MANAGER_H_ */
