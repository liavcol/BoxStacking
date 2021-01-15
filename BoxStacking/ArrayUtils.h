#pragma once
#include <iostream>

//A class for generic helper functions for arrays.
class ArrayUtils
{
public:
	template <typename T, typename COMPARATOR>
	static void MergeSort(T* arr[], int li, int ri)
	{
		if (li >= ri)
			return;
		int mi = (li + ri) / 2;
		ArrayUtils::MergeSort<T,COMPARATOR>(arr, li, mi);
		ArrayUtils::MergeSort<T,COMPARATOR>(arr, mi + 1, ri);
		ArrayUtils::Merge<T,COMPARATOR>(arr, li, mi, ri);
	}

	template <typename T>
	static std::ostream& PrintArray(std::ostream& out, T* arr[], int size, bool reverse = false)
	{
		if (reverse)
			for (int i = size - 1; i >= 0; i--)
				out << *arr[i] << std::endl;
		else
			for (int i = 0; i < size; i++)
			out << *arr[i] << std::endl;
		
		return out;
	}

private:
	template <typename T, typename COMPARATOR>
	static void Merge(T* arr[], int li, int mi, int ri)
	{
		int nl = mi - li + 1;
		int nr = ri - mi;

		T** lArr = new T*[nl];
		T** rArr = new T*[nr];

		for (int i = 0; i < nl; i++)
			lArr[i] = arr[li + i];
		for (int j = 0; j < nr; j++)
			rArr[j] = arr[mi + 1 + j];

		int i = 0;
		int j = 0;
		int k = li;

		COMPARATOR cmp;
		while (i < nl && j < nr)
		{
			if(cmp(*lArr[i], *rArr[j]))
			{
				arr[k] = lArr[i];
				i++;
			}
			else
			{
				arr[k] = rArr[j];
				j++;
			}
			k++;
		}

		while (i < nl)
		{
			arr[k] = lArr[i];
			i++;
			k++;
		}

		while (j < nr)
		{
			arr[k] = rArr[j];
			j++;
			k++;
		}

		delete[] lArr;
		delete[] rArr;
	}
};

