#include "LinearEquation.h"
#include <algorithm>
#include <vector>
#include <string>
#include <ctime>
#include <stdexcept>
#include <iostream>
using namespace std;

LinearEquation::LinearEquation()
{
    this->coefficients = { 0, 0 };
}

LinearEquation::LinearEquation(string str)
{
    vector<string> sVec;
    int pos = str.find(" ");
    while (pos != string::npos)
    {
        sVec.push_back(str.substr(0, pos));
        str.erase(0, pos + 1);
        pos = str.find(" ");
    }
    if (!str.empty()) sVec.push_back(str);
    if (sVec.size() == 0) this->coefficients = { 0, 0 };
    else if (sVec.size() == 1) this->coefficients = { stod(sVec[0]), 0 };
    else for (int i = 0; i < sVec.size(); i++)
    {
        this->coefficients.push_back(stod(sVec[i]));
    }
}

LinearEquation::LinearEquation(const vector<double>& vec)
{
    if (vec.size() == 0) this->coefficients = { 0, 0 };
    else if (vec.size() == 1) this->coefficients = { vec[0], 0 };
    else this->coefficients = vector<double>(vec);
}

LinearEquation::LinearEquation(const double* const arr, int size)
{
    if (size == 0) this->coefficients = { 0, 0 };
    else if (size == 1) this->coefficients = { arr[0], 0 };
    else this->coefficients = vector<double>(arr, arr + size);
}
LinearEquation::LinearEquation(const LinearEquation& le)
{
    this->coefficients = vector<double>(le.coefficients);
}

LinearEquation::LinearEquation(int count)
{
    if (count >= 2)
    {
        this->coefficients.resize(count);
        fill(this->coefficients.begin(), this->coefficients.end(), 0.);
    }
    else if (count >= 0) this->coefficients = { 0, 0 };
    else throw invalid_argument("Count must be greater than or equal to zero");
}

void LinearEquation::FillByDuplicates(double number)
{
    fill(this->coefficients.begin(), this->coefficients.end(), number);
}

void LinearEquation::FillByRandom(double minValue, double maxValue, int seed)
{
    if (maxValue < minValue) throw invalid_argument("Minimum is greater than maximum");
    srand(seed);
    for (int i = 0; i < this->coefficients.size(); i++)
    {
        this->coefficients[i] = (double)rand() / RAND_MAX * (maxValue - minValue) + minValue;
    }
}

void LinearEquation::FillByRandom(double minValue, double maxValue)
{
    if (maxValue < minValue) throw invalid_argument("Minimum is greater than maximum");
    srand(time(NULL));
    for (int i = 0; i < this->coefficients.size(); i++)
    {
        this->coefficients[i] = (double)rand() / RAND_MAX * (maxValue - minValue) + minValue;
    }
}

int LinearEquation::GetDegree() const
{
    int degree = 0;
    for (int i = 0; i < this->coefficients.size(); i++)
    {
        if (this->coefficients[i] != 0) degree = i;
    }
    return degree;
}

const LinearEquation operator+(const LinearEquation& le1, const LinearEquation& le2)
{
    int count = max(le1.coefficients.size(), le2.coefficients.size());
    LinearEquation result = LinearEquation(count);
    for (int i = 0; i < count; i++)
    {
        result.coefficients[i] = ((i < le1.coefficients.size()) ? le1.coefficients[i] : 0) + ((i < le2.coefficients.size()) ? le2.coefficients[i] : 0);
    }
    return result;
}

const LinearEquation operator-(const LinearEquation& le1, const LinearEquation& le2)
{
    int count = max(le1.coefficients.size(), le2.coefficients.size());
    LinearEquation result = LinearEquation(count);
    for (int i = 0; i < count; i++)
    {
        result.coefficients[i] = ((i < le1.coefficients.size()) ? le1.coefficients[i] : 0) - ((i < le2.coefficients.size()) ? le2.coefficients[i] : 0);
    }
    return result;
}

const LinearEquation operator*(const LinearEquation& le, const double k)
{
    LinearEquation result = LinearEquation(le);
    for (int i = 0; i < le.coefficients.size(); i++)
    {
        result.coefficients[i] *= k;
    }
    return result;
}

const LinearEquation operator*(const double k, const LinearEquation& le)
{
    return le * k;
}

const LinearEquation operator-(const LinearEquation& le)
{
    return le * -1.;
}

const bool operator==(const LinearEquation& le1, const LinearEquation& le2)
{
    int count = max(le1.coefficients.size(), le1.coefficients.size());
    LinearEquation result = LinearEquation(count);
    for (int i = 0; i < count; i++)
    {
        bool isInequal = (i < le1.coefficients.size() && i >= le2.coefficients.size() && le1.coefficients[i] != 0) ||
            (i >= le1.coefficients.size() && i < le2.coefficients.size() && le2.coefficients[i] != 0) ||
            (i < le1.coefficients.size() && i < le2.coefficients.size() && le1.coefficients[i] != le2.coefficients[i]);
        if (isInequal) return false;
    }
    return true;
}

const bool operator!=(const LinearEquation& le1, const LinearEquation& le2)
{
    return !(le1 == le2);
}

LinearEquation::operator bool() const
{
    if (this->coefficients[0] == 0) return true;
    for (int i = 1; i < this->coefficients.size(); i++)
    {
        if (this->coefficients[i] != 0) return true;
    }
    return false;
}

LinearEquation::operator vector<double>() const
{
    vector<double> result = vector<double>(this->coefficients);
    return result;
}

const double& LinearEquation::operator[] (const int index) const
{
    if (index < 0 || index > this->GetDegree()) throw out_of_range("Index less than 0 or greater than degree");
    return this->coefficients[index];
}

LinearEquation::operator string() const
{
    string result = "";
    for (int i = this->coefficients.size() - 1; i >= 0; i--)
    {
        if (this->coefficients[i] != 0)
        {
            if (result != "" && this->coefficients[i] > 0) result += "+";
            result += to_string(this->coefficients[i]);
            if (i != 0) result += "x" + to_string(i);
        }
    }
    if (result == "") result += "0";
    result += "=0";
    return result;
}