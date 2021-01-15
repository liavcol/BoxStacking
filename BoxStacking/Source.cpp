#include <iostream>
#include <ctime>
#include "Box.h"
#include "ArrayUtils.h"


int HighestBuilding(int W[], int L[], int H[], int n);

int main()
{
	srand(0);
	auto FillDifferentIntsOfRange = [](int arr[], int size, int limit)
	{
		bool* used = new bool[limit + 1]{ false };
		for (int i = 0; i < size; i++)
		{
			int r;
			do
				r = rand() % limit + 1;
			while (used[r]);
			arr[i] = r;
			used[r] = true;
		}
		delete[] used;
	};

	std::cout << "Running the algorithm for 20 boxes with different dimensions:" << std::endl;

	int W1[20];
	int L1[20];
	int H1[20];

	FillDifferentIntsOfRange(W1, 20, 200);
	FillDifferentIntsOfRange(L1, 20, 200);
	FillDifferentIntsOfRange(H1, 20, 200);

	int max = HighestBuilding(W1, L1, H1, 20);
	std::cout << "Highest building possible height: " << max << std::endl;

	std::cout <<std::endl << "Running the algorithm for 30 boxes with different dimensions:" << std::endl;

	int W2[30];
	int L2[30];
	int H2[30];
	
	FillDifferentIntsOfRange(W2, 30, 200);
	FillDifferentIntsOfRange(L2, 30, 200);
	FillDifferentIntsOfRange(H2, 30, 200);

	max = HighestBuilding(W2, L2, H2, 30);
	std::cout << "Highest building possible height: " << max << std::endl;

	std::cin.get();
}

//The function uses dynamic programming to solve the problem at O(n^2).
//For each Box, it will find it's highest possible building by trying to stack every box with width and length less than it and check which gives the highest building.
//Since checking the highest building of each box is a recursive problem in itself, we are storing what we already calculated so we can use this information in O(1).
//Lowering our overall time complexity from O(n^n) to O(n^2)
int HighestBuilding(int W[], int L[], int H[], int n)
{
	//Convert the dimensions arrays to an array of Box objects - O(n).
	Box** boxes = new Box*[n];
	Box::MakeBoxes(W, L, H, n, boxes);
	
	//Print the boxes recieved as input.
	ArrayUtils::PrintArray<Box>(std::cout, boxes, n);

	//Sort the boxes by width and then length to make sure that for each box, all the boxes that may be stacked on it are found to the
	//left of it in the array and therefore their highest building was already calculated and ready to be used.
	//Using Merge Sort - O(nlog(n)).
	ArrayUtils::MergeSort<Box, Box::WidthComparator>(boxes, 0, n - 1);

	int* maxBuildingWithBase = new int[n]; //An array for keeping all the highest buildings that i is their base.
	int* prevBoxi = new int[n]; //An array to keep track on what box is stacked on top of what box. (prevBoxi[i] = j <==> j is on top of i).
	int* numBoxesInBuildingOf = new int[n]; //An array to keep track on the number of boxes in each building (used later to print the building nicely ;) ).

	int max = 0;
	int maxBoxi = 0;
	for (int i = 0; i < n; i++)
	{
		maxBuildingWithBase[i] = boxes[i]->Height();
		prevBoxi[i] = -1;
		numBoxesInBuildingOf[i] = 1;

		//Because we sorted the array before we know that all possible stable boxes relative to i will be before it in the array.
		for (int j = 0; j < i; j++)
		{
			//We still need to make sure though that both the width and length of j are really less the i's. 
			if (boxes[j]->Width() < boxes[i]->Width() && boxes[j]->Length() < boxes[i]->Length())
			{
				//And if they are then check if by stacking the highest building that starts with j on top of i yields a higher building.
				if (maxBuildingWithBase[i] < boxes[i]->Height() + maxBuildingWithBase[j])
				{
					maxBuildingWithBase[i] = boxes[i]->Height() + maxBuildingWithBase[j];
					prevBoxi[i] = j;
					numBoxesInBuildingOf[i] = 1 + numBoxesInBuildingOf[j];
				}
			}
		}

		//By now we found the highest building we can build on i, so let's check if it's the highest building overall. 
		if (maxBuildingWithBase[i] > max)
		{
			max = maxBuildingWithBase[i];
			maxBoxi = i;
		}
	}


	//Bonus part: Build another array with all the boxes of the highest building.
	//We do this because our algorithm produce an array that keep track over who stacked on top of who from bottom to top,
	//but when printing the building we'll need to print from top to bottom so the top will be on top. (really not necessary).
	Box** highestBuiding = new Box*[numBoxesInBuildingOf[maxBoxi]];
	int b = maxBoxi;
	for (int i = 0; i < numBoxesInBuildingOf[maxBoxi]; i++)
	{
		highestBuiding[i] = boxes[b];
		b = prevBoxi[b];
	}
	std::cout <<std::endl << "This is the highest building: " << std::endl;
	ArrayUtils::PrintArray<Box>(std::cout, highestBuiding, numBoxesInBuildingOf[maxBoxi], true);

	//Free all allocated memory used for the algorithm.
	for (int i = 0; i < n; i++)
		delete boxes[i];
	delete[] boxes;
	delete[] maxBuildingWithBase;
	delete[] prevBoxi;
	delete[] numBoxesInBuildingOf;
	delete[] highestBuiding;

	//As requested, return the height of the highest possible building.
	return max;
}