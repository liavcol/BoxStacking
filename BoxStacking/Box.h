#pragma once

#include <iostream>

//Simple class for a box.
class Box
{
private:
	int _width;
	int _length;
	int _height;

public:
	Box(int width, int length, int height);
	
	int Width();
	int Length();
	int Height();
	
	struct WidthComparator
	{
		bool operator()(const Box& b1, const Box& b2);
	};

	friend std::ostream& operator<<(std::ostream& out, const Box& b);

	//Caution using this static method as it allocates memory in the array that must be deleted later if used!
	static void MakeBoxes(int W[], int L[], int H[], int n, Box* boxes[]);
};

