/*
 * StlHelper.h
 *
 *  Created on: 17.09.2012
 *      Author: nopper
 */

#ifndef STLHELPER_H_
#define STLHELPER_H_

#include "../../UsedLibs.h"

template <typename KeyType, typename ValueType>
typename std::map<KeyType, ValueType>::const_iterator less_equal_bound(const std::map<KeyType, ValueType>& searchMap, const KeyType& searchKey)
{
	if (searchMap.size() == 0)
	{
		return searchMap.end();
	}

    auto walker = searchMap.upper_bound(searchKey);

    if (walker != searchMap.begin())
    {
        return --walker;
    }

    return searchMap.end();
}

#endif /* STLHELPER_H_ */
