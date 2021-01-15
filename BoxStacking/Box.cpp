#include "Box.h"

Box::Box(int width, int length, int height) : _width(width), _length(length), _height(height) { }

int Box::Width() { return _width; }

int Box::Length() { return _length; }

int Box::Height() { return _height; }

std::ostream& operator<<(std::ostream& out, const Box& b)
{
	out << "W: " << b._width << " X L: " << b._length << " X H: " << b._height;
	return out;
}

bool Box::WidthComparator::operator()(const Box& b1, const Box& b2)
{
	return b1._width <= b2._width;
}

void Box::MakeBoxes(int W[], int L[], int H[], int n, Box* boxes[])
{
	for (int i = 0; i < n; i++)
		boxes[i] = new Box(W[i], L[i], H[i]);
}