/*
 * KeyValueMap.h
 *
 *  Created on: 22.05.2013
 *      Author: nopper
 */

#ifndef KEYVALUEMAP_H_
#define KEYVALUEMAP_H_

#include "../../UsedLibs.h"

template<class K, class V>
class KeyValueMap
{

	protected:

		std::map<K, V> allKeyValues;

	public:

		KeyValueMap()
		{
		}

		virtual ~KeyValueMap()
		{
			clear();
		}

		virtual void clear()
		{
			allKeyValues.clear();
		}

		virtual typename std::map<K, V>::iterator begin()
		{
			return allKeyValues.begin();
		}

		virtual typename std::map<K, V>::const_iterator begin() const
		{
			return allKeyValues.begin();
		}

		virtual typename std::map<K, V>::iterator end()
		{
			return allKeyValues.end();
		}

		virtual typename std::map<K, V>::const_iterator end() const
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

		virtual bool remove(const K& key)
		{
			if (allKeyValues.find(key) == allKeyValues.end())
			{
				return false;
			}

			allKeyValues.erase(key);

			return true;
		}

		virtual V search(const K& key) const
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

		virtual V& at(const K& key)
		{
			return allKeyValues.at(key);
		}

		virtual const V& at(const K& key) const
		{
			return allKeyValues.at(key);
		}

		virtual V& operator[](const K& key)
		{
			return allKeyValues[key];
		}

		virtual const std::map<K, V>& getAllKeyValues() const
		{
			return allKeyValues;
		}

		virtual std::int32_t size() const
		{
			return allKeyValues.size();
		}

};

#endif /* KEYVALUEMAP_H_ */
