#pragma once
#include <vector>
#include "LinearEquation.h"
#include <iostream>
using namespace std;

class SystemOfLinearEquation
{
private:
	vector<LinearEquation> equations;
public:
	SystemOfLinearEquation(int size);
	LinearEquation& operator[] (const int index);
	void ToTriangular();
	const vector<double> Solve();
	operator string() const;
};

