/*
 * QuicksortPointer.h
 *
 *  Created on: 04.05.2011
 *      Author: Norbert Nopper
 */
#ifndef QUICKSORTPOINTER_H_
#define QUICKSORTPOINTER_H_

#include "../../UsedLibs.h"

template<class SORT>
class QuicksortPointer
{

private:

	void quicksort(std::int32_t left, std::int32_t right, std::vector<SORT>& allElements) const
	{
		if (left < right)
		{
			std::int32_t divider = divide(left, right, allElements);
			quicksort(left, divider - 1, allElements);
			quicksort(divider + 1, right, allElements);
		}
	}

	std::int32_t divide(std::int32_t left, std::int32_t right, std::vector<SORT>& allElements) const
	{
		std::int32_t leftWalker = left;

		std::int32_t rightWalker = right - 1;

		SORT pivot = allElements[right];

		do
		{
			while (*allElements[leftWalker] <= *pivot && leftWalker < right)
			{
				leftWalker++;
			}

			while (*allElements[rightWalker] >= *pivot && rightWalker > left)
			{
				rightWalker--;
			}

			if (leftWalker < rightWalker)
			{
				SORT temp = allElements[leftWalker];
				allElements[leftWalker] = allElements[rightWalker];
				allElements[rightWalker] = temp;
			}

		} while (leftWalker < rightWalker);

		SORT temp = allElements[leftWalker];
		allElements[leftWalker] = allElements[right];
		allElements[right] = temp;

		return leftWalker;
	}

public:

	QuicksortPointer()
	{
	}

	~QuicksortPointer()
	{
	}

	void sort(std::vector<SORT>& allElements) const
	{
		quicksort(0, allElements.size() - 1, allElements);
	}

};

#endif /* QUICKSORTPOINTER_H_ */
