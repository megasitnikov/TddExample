#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class LinearEquation
{
private:
	vector<double> coefficients;
public:
	LinearEquation();
	LinearEquation(string str);
	LinearEquation(const vector<double>& vec);
	LinearEquation(const double* const arr, int size);
	LinearEquation(const LinearEquation& le);
	LinearEquation(int count);
	~LinearEquation() {};
	void FillByDuplicates(double number);
	void FillByRandom(double minValue, double maxValue, int seed);
	void FillByRandom(double minValue, double maxValue);
	int GetDegree() const;
	friend const LinearEquation operator+(const LinearEquation& le1, const LinearEquation& le2);
	friend const LinearEquation operator-(const LinearEquation& le1, const LinearEquation& le2);
	friend const LinearEquation operator*(const LinearEquation& le, const double k);
	friend const LinearEquation operator*(const double k, const LinearEquation& le);
	friend const LinearEquation operator-(const LinearEquation& le);
	friend const bool operator==(const LinearEquation& le1, const LinearEquation& le2);
	friend const bool operator!=(const LinearEquation& le1, const LinearEquation& le2);
	operator bool() const;
	operator vector<double>() const;
	const double& operator[] (const int index) const;
	operator string() const;
};
