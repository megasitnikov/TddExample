#include "pch.h"
#include "CppUnitTest.h"
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include "../task2/LinearEquation.h"
#include "../task2/LinearEquation.cpp"
#include <iostream>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LETest
{
	TEST_CLASS(LinearEquationTest)
	{
	public:
		TEST_METHOD(StringConstructor)
		{
			string s = "1 1.5 2.6 -4 89 13.4";
			vector<double> res = { 1, 1.5, 2.6, -4, 89, 13.4 };
			LinearEquation le = LinearEquation(s);
			Assert::IsTrue(res == (vector<double>)le);
		}
		TEST_METHOD(StringConstructorWithEmptyString)
		{
			string s = "";
			vector<double> res = { 0, 0 };
			LinearEquation le = LinearEquation(s);
			Assert::IsTrue(res == (vector<double>)le);
		}
		TEST_METHOD(StringConstructorWithOneElement)
		{
			string s = "2";
			vector<double> res = { 2, 0 };
			LinearEquation le = LinearEquation(s);
			Assert::IsTrue(res == (vector<double>)le);
		}
		TEST_METHOD(StringConstructorWithWrongArgument)
		{
			Assert::ExpectException<invalid_argument>([] { LinearEquation("1 g 2.25 -5.7 helloworld 3 k"); });
		}
		TEST_METHOD(VectorConstructor)
		{
			vector<double> input = { 0, -5.6, 4, 7 };
			vector<double> res = { 0, -5.6, 4, 7 };
			LinearEquation le = LinearEquation(input);
			Assert::IsTrue(res == (vector<double>)le);
		}
		TEST_METHOD(ArrayConstructor)
		{
			double* input = new double[4]{ 0, -5.6, 4, 7 };
			vector<double> res = { 0, -5.6, 4, 7 };
			LinearEquation le = LinearEquation(input, 4);
			Assert::IsTrue(res == (vector<double>)le);
		}
		TEST_METHOD(VectorConstructorWithEmptyVector)
		{
			vector<double> input = { };
			vector<double> res = { 0, 0 };
			LinearEquation le = LinearEquation(input);
			Assert::IsTrue(res == (vector<double>)le);
		}
		TEST_METHOD(VectorConstructorWithOneElement)
		{
			vector<double> input = { 1 };
			vector<double> res = { 1, 0 };
			LinearEquation le = LinearEquation(input);
			Assert::IsTrue(res == (vector<double>)le);
		}
		TEST_METHOD(ArrayConstructorWithOneElement)
		{
			double* input = new double[1]{ 2 };
			vector<double> res = { 2, 0 };
			LinearEquation le = LinearEquation(input, 1);
			Assert::IsTrue(res == (vector<double>)le);
		}
		TEST_METHOD(LinearEquationConstructor)
		{
			vector<double> input = { 5, 7, 2.4, -78, 3 };
			vector<double> res = { 5, 7, 2.4, -78, 3 };
			LinearEquation le1 = LinearEquation(input);
			LinearEquation le2 = LinearEquation(le1);
			Assert::IsTrue(res == (vector<double>)le2);
		}
		TEST_METHOD(IntConstructor)
		{
			int count = 3;
			vector<double> res = { 0, 0, 0 };
			LinearEquation le = LinearEquation(count);
			Assert::IsTrue(res == (vector<double>)le);
		}
		TEST_METHOD(IntConstructorWithZero)
		{
			int count = 0;
			vector<double> res = { 0, 0 };
			LinearEquation le = LinearEquation(count);
			Assert::IsTrue(res == (vector<double>)le);
		}
		TEST_METHOD(IntConstructorWithOne)
		{
			int count = 1;
			vector<double> res = { 0, 0 };
			LinearEquation le = LinearEquation(count);
			Assert::IsTrue(res == (vector<double>)le);
		}
		TEST_METHOD(IntConstructorWithNegativeArgument)
		{
			int count = -1;
			Assert::ExpectException<invalid_argument>([] { LinearEquation(-1); });
		}
		TEST_METHOD(FillByDuplicates)
		{
			int count = 4;
			vector<double> res = { 7.3, 7.3, 7.3, 7.3 };
			LinearEquation le = LinearEquation(count);
			le.FillByDuplicates(7.3);
			Assert::IsTrue(res == (vector<double>)le);
		}
		TEST_METHOD(FillByRandomWithMinMoreThanMaxArguments)
		{
			int count = 4;
			LinearEquation le = LinearEquation(count);
			Assert::ExpectException<invalid_argument>([&] { le.FillByRandom(100, 10); });
		}
		TEST_METHOD(FillByRandomWithEqualSeeds)
		{
			int count = 3;
			LinearEquation le1 = LinearEquation(count);
			LinearEquation le2 = LinearEquation(count);
			le1.FillByRandom(-5, 10, 100);
			le2.FillByRandom(-5, 10, 100);
			Assert::IsTrue((vector<double>)le1 == (vector<double>)le2);
		}
		TEST_METHOD(GetDegree)
		{
			vector<double> input = { 1, 2, 3 };
			LinearEquation le = LinearEquation(input);
			Assert::AreEqual(2, le.GetDegree());
		}
		TEST_METHOD(GetDegreeWithZeros)
		{
			vector<double> input = { 1, 2, 3, 0, 0 };
			LinearEquation le = LinearEquation(input);
			Assert::AreEqual(2, le.GetDegree());
		}
		TEST_METHOD(AdditionWithSameCountOfCoefficients)
		{
			vector<double> input1 = { 1, 2, 3 };
			vector<double> input2 = { 4, 5, 6 };
			vector<double> result = { 5, 7, 9 };
			LinearEquation le1 = LinearEquation(input1);
			LinearEquation le2 = LinearEquation(input2);
			Assert::IsTrue(result == (vector<double>)(le1 + le2));
		}
		TEST_METHOD(AdditionWithDifferentCountOfCoefficients)
		{
			vector<double> input1 = { 1, -5, 3, 7 };
			vector<double> input2 = { 4, 5, 6 };
			vector<double> result = { 5, 0, 9, 7 };
			LinearEquation le1 = LinearEquation(input1);
			LinearEquation le2 = LinearEquation(input2);
			Assert::IsTrue(result == (vector<double>)(le1 + le2));
		}
		TEST_METHOD(SubstractionWithSameCountOfCoefficients)
		{
			vector<double> input1 = { 5, 2, 0 };
			vector<double> input2 = { 1, 5, 1 };
			vector<double> result = { 4, -3, -1 };
			LinearEquation le1 = LinearEquation(input1);
			LinearEquation le2 = LinearEquation(input2);
			Assert::IsTrue(result == (vector<double>)(le1 - le2));
		}
		TEST_METHOD(SubstractionWithDifferentCountOfCoefficients)
		{
			vector<double> input1 = { 4, 5, 3 };
			vector<double> input2 = { 1, 5, 6, 8 };
			vector<double> result = { 3, 0, -3, -8 };
			LinearEquation le1 = LinearEquation(input1);
			LinearEquation le2 = LinearEquation(input2);
			Assert::IsTrue(result == (vector<double>)(le1 - le2));
		}
		TEST_METHOD(LeftMultiplication)
		{
			vector<double> input = { 4, -5, 3 };
			vector<double> result = { 8, -10, 6 };
			LinearEquation le = LinearEquation(input);
			double k = 2;
			Assert::IsTrue(result == (vector<double>)(k * le));
		}
		TEST_METHOD(RightMultiplication)
		{
			vector<double> input = { 4, -5, 3 };
			vector<double> result = { 8, -10, 6 };
			LinearEquation le = LinearEquation(input);
			double k = 2;
			Assert::IsTrue(result == (vector<double>)(le * k));
		}
		TEST_METHOD(Inverse)
		{
			vector<double> input = { 2, 0, -4 };
			vector<double> result = { -2, 0, 4 };
			LinearEquation le = LinearEquation(input);
			Assert::IsTrue(result == (vector<double>)(-le));
		}
		TEST_METHOD(EqualityWithSameCountOfCoefficients)
		{
			vector<double> input1 = { 1, 2, 3 };
			vector<double> input2 = { 1, 2, 3 };
			LinearEquation le1 = LinearEquation(input1);
			LinearEquation le2 = LinearEquation(input2);
			Assert::IsTrue(le1 == le2);
		}
		TEST_METHOD(EqualityWithDifferentCountOfCoefficients)
		{
			vector<double> input1 = { 1, 2, 3 };
			vector<double> input2 = { 1, 2, 3, 0, 0 };
			LinearEquation le1 = LinearEquation(input1);
			LinearEquation le2 = LinearEquation(input2);
			Assert::IsTrue(le1 == le2);
		}
		TEST_METHOD(Inequality)
		{
			vector<double> input1 = { 1, 2, 3 };
			vector<double> input2 = { 1, 6, 3 };
			LinearEquation le1 = LinearEquation(input1);
			LinearEquation le2 = LinearEquation(input2);
			Assert::IsTrue(le1 != le2);
		}
		TEST_METHOD(TrueLinearEquation)
		{
			vector<double> input = { 1, 2, 1 };
			LinearEquation le = LinearEquation(input);
			Assert::IsTrue((bool)le);
		}
		TEST_METHOD(FalseLinearEquation)
		{
			vector<double> input = { 2, 0, 0 };
			LinearEquation le = LinearEquation(input);
			Assert::IsFalse((bool)le);
		}
		TEST_METHOD(Coefficient)
		{
			vector<double> input = { 2, 3, 1 };
			LinearEquation le = LinearEquation(input);
			Assert::AreEqual((double)3, le[1]);
		}
		TEST_METHOD(CoefficientOutOfRange)
		{
			vector<double> input = { 2, 3, 1, 0, 0, 0 };
			LinearEquation le = LinearEquation(input);
			Assert::ExpectException<out_of_range>([&] {le[4]; });
		}
		TEST_METHOD(ToString)
		{
			vector<double> input = { 2, 1, 4 };
			string result = "4.000000x2+1.000000x1+2.000000=0";
			LinearEquation le = LinearEquation(input);
			Assert::AreEqual(result, (string)le);
		}
		TEST_METHOD(ToStringWithMinus)
		{
			vector<double> input = { 2, -1, 4 };
			string result = "4.000000x2-1.000000x1+2.000000=0";
			LinearEquation le = LinearEquation(input);
			Assert::AreEqual(result, (string)le);
		}
		TEST_METHOD(ToStringWithZeroArgument)
		{
			vector<double> input = { 2, 1, 0, 4 };
			string result = "4.000000x3+1.000000x1+2.000000=0";
			LinearEquation le = LinearEquation(input);
			Assert::AreEqual(result, (string)le);
		}
	};
}