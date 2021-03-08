# Box Stacking Problem - Dynamic Programming Example
An example demonstaring the power of dynamic programming to significantly reduce a solution's time complexity (written in C++).
Also includes a demonstration of generics in C++.

## Introduction
Given as an assignment in a course in Computer Science BSc.
The problem: We have 3 arrays: lengths array, widths array and heights array - representing the dimensions for a list of boxes. A box, i, can only be stacked on another box, j, if the length of i is less than the length of j and the width of i is less than the width of j. We need to determine what is the highest building we can build by stacking boxes from our list on top of each other, the boxes cannot be rotated in any way.
Note that it is not as simple as it may sound, since we need to consider what boxes to use and what not, if we'll take for example a box that is tall but "narrow" we might not be
able to keep stacking on it and we might not get the overall highest building we can build.
Normally, trying to build all options for the highest bulding and compare them would result in an enormous O(n^n) algorithm. However, using dynamic programming the solution shows how to reduce the time complexity to a much more reasonable O(n^2) (and O(n) space complexity)!

