/*
 * KeyValueManager.h
 *
 *  Created on: 22.05.2013
 *      Author: nopper
 */

#ifndef KEYVALUEMANAGER_H_
#define KEYVALUEMANAGER_H_

#include "../../UsedLibs.h"

template<class K, class V>
class KeyValueManager
{

	protected:

		std::map<K, V> allKeyValues;

		KeyValueManager()
		{
		}

		virtual ~KeyValueManager()
		{
			allKeyValues.clear();
		}

	public:

		virtual typename std::map<K, V>::iterator begin()
		{
			return allKeyValues.begin();
		}

		virtual typename std::map<K, V>::iterator end()
		{
			return allKeyValues.end();
		}

		virtual bool add(const K& key, const V& value)
		{
			if (allKeyValues.find(key) != allKeyValues.end())
			{
				return false;
			}

			allKeyValues[key] = value;

			return true;
		}

		virtual void replace(const K& key, const V& value)
		{
			allKeyValues[key] = value;
		}

		virtual bool erase(const K& key)
		{
			if (allKeyValues.find(key) == allKeyValues.end())
			{
				return false;
			}

			allKeyValues.erase(key);

			return true;
		}

		virtual V find(const K& key) const
		{
			auto result = allKeyValues.find(key);

			if (result != allKeyValues.end())
			{
				return result->second;
			}

			return V();
		}

		virtual bool contains(const K& key) const
		{
			return allKeyValues.find(key) != allKeyValues.end();
		}

		virtual V at(const K& key) const
		{
			return allKeyValues.at(key);
		}

		virtual const std::map<K, V>& getAllKeyValues() const
		{
			return allKeyValues;
		}

		virtual boost::int32_t size() const
		{
			return allKeyValues.size();
		}

};

#endif /* KEYVALUEMANAGER_H_ */
