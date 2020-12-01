#include <stdexcept>
#include <iostream>
#include "Indexer.h"
using namespace std;
Indexer::Indexer(double* arr, int arrLength, int FirstIndex, int length)
{
	if (arrLength <= FirstIndex + length || FirstIndex < 0 || length < 0) throw invalid_argument("Incorrect first index or length");
	this->array = arr;
	this->Index_1 = FirstIndex;
	this->Index_2 = FirstIndex + length - 1;
}
int Indexer::Length()
{
	return this->Index_2 - this->Index_1 + 1;
}
double& Indexer::operator[] (const int index)
{
	if (index < 0 || index >= Length()) throw out_of_range("Index out of range");
	return this->array[index + Index_1];
}