/*
 * ValueVector.h
 *
 *  Created on: 22.05.2013
 *      Author: nopper
 */

#ifndef VALUEVECTOR_H_
#define VALUEVECTOR_H_

#include "../../UsedLibs.h"

template<class V>
class ValueVector
{

	protected:

		std::vector<V> allValues;

	public:

		ValueVector() :
				allValues()
		{
		}

		virtual ~ValueVector()
		{
			clear();
		}

		virtual void clear()
		{
			allValues.clear();
		}

		virtual typename std::vector<V>::iterator begin()
		{
			return allValues.begin();
		}

		virtual typename std::vector<V>::const_iterator begin() const
		{
			return allValues.begin();
		}

		virtual typename std::vector<V>::iterator end()
		{
			return allValues.end();
		}

		virtual typename std::vector<V>::const_iterator end() const
		{
			return allValues.end();
		}

		virtual bool add(const V& value)
		{
			auto walker = std::find(allValues.begin(), allValues.end(), value);

			if (walker != allValues.end())
			{
				return false;
			}

			allValues.push_back(value);

			return true;
		}

		virtual bool remove(const V& value)
		{
			auto walker = std::find(allValues.begin(), allValues.end(), value);

			if (walker != allValues.end())
			{
				allValues.erase(walker);

				return true;
			}

			return false;
		}

		virtual bool contains(const V& value) const
		{
			return std::find(allValues.begin(), allValues.end(), value) != allValues.end();
		}

		virtual V& at(boost::int32_t i)
		{
			return allValues.at(i);
		}

		virtual const V& at(boost::int32_t i) const
		{
			return allValues.at(i);
		}

		virtual const std::vector<V>& getAllValues() const
		{
			return allValues;
		}

		virtual boost::int32_t size() const
		{
			return allValues.size();
		}

};

#endif /* VALUEVECTOR_H_ */
