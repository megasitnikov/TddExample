#pragma once
class Indexer
{
private:
	double* array;
	int Index_1, Index_2;
public:
	Indexer(double* arr, int arrLength, int FirstIndex, int length);
	int Length();
	double& operator[] (const int index);
};