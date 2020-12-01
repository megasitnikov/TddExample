#include "pch.h"
#include "CppUnitTest.h"
#include <stdexcept>
#include <string>
#include <vector>
#include "../task2/SystemOfLinearEquation.h"
#include "../task2/SystemOfLinearEquation.cpp"
#include "../task2/LinearEquation.h"
#include "../task2/LinearEquation.cpp"
#include <iostream>
using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SOLETest
{
	TEST_CLASS(SystemOfLinearEquationTest)
	{
	public:

		TEST_METHOD(Constructor)
		{
			int size = 2;
			SystemOfLinearEquation sole = SystemOfLinearEquation(size);
			string result = "0=0\n0=0\n";
			Assert::AreEqual(result, (string)sole);
		}
		TEST_METHOD(ConstructorWithNegativeArgument)
		{
			Assert::ExpectException<invalid_argument>([] { SystemOfLinearEquation(-2); });
		}
		TEST_METHOD(Get)
		{
			int size = 1;
			SystemOfLinearEquation sole = SystemOfLinearEquation(size);
			string result = "0=0";
			Assert::AreEqual(result, (string)sole[0]);
		}
		TEST_METHOD(GetWithIncorrectArgument)
		{
			int size = 1;
			SystemOfLinearEquation sole = SystemOfLinearEquation(size);
			Assert::ExpectException<invalid_argument>([&] { sole[-4]; });
		}
		TEST_METHOD(SetAndGet)
		{
			int size = 2;
			SystemOfLinearEquation sole = SystemOfLinearEquation(size);
			sole[0] = LinearEquation("1 2 3");
			string result = "3.000000x2+2.000000x1+1.000000=0";
			Assert::AreEqual(result, (string)sole[0]);
		}
		TEST_METHOD(SetWithIncorrectArgument)
		{
			int size = 1;
			SystemOfLinearEquation sole = SystemOfLinearEquation(size);
			Assert::ExpectException<invalid_argument>([&] { sole[3] = LinearEquation("1 2 3"); });
		}
		TEST_METHOD(Triangular)
		{
			int size = 3;
			SystemOfLinearEquation sole = SystemOfLinearEquation(size);
			sole[0] = LinearEquation("-8 -1 1 2");
			sole[1] = LinearEquation("11 2 -1 -3");
			sole[2] = LinearEquation("3 2 1 -2");
			sole.ToTriangular();
			string result = "2.000000x3+1.000000x2-1.000000x1-8.000000=0\n0.500000x2+0.500000x1-1.000000=0\n-1.000000x1-1.000000=0\n";
			Assert::AreEqual(result, (string)sole);
		}
		TEST_METHOD(Solve)
		{
			int size = 3;
			SystemOfLinearEquation sole = SystemOfLinearEquation(size);
			sole[0] = LinearEquation("-8 -1 1 2");
			sole[1] = LinearEquation("11 2 -1 -3");
			sole[2] = LinearEquation("3 2 1 -2");
			vector<double> result = { -1, 3, 2 };
			Assert::IsTrue(result == sole.Solve());
		}
		TEST_METHOD(SolveWithSameEquations)
		{
			int size = 4;
			SystemOfLinearEquation sole = SystemOfLinearEquation(size);
			sole[0] = LinearEquation("-8 -1 1 2");
			sole[1] = LinearEquation("11 2 -1 -3");
			sole[2] = LinearEquation("11 2 -1 -3");
			sole[3] = LinearEquation("3 2 1 -2");
			vector<double> result = { -1, 3, 2 };
			Assert::IsTrue(result == sole.Solve());
		}
		TEST_METHOD(SolveWithContradictoryEquations)
		{
			int size = 4;
			SystemOfLinearEquation sole = SystemOfLinearEquation(size);
			sole[0] = LinearEquation("-8 -1 1 2");
			sole[1] = LinearEquation("11 2 -1 -3");
			sole[2] = LinearEquation("3 2 1 -2");
			sole[3] = LinearEquation("4 2 2 -2");
			Assert::ExpectException<logic_error>([&] { sole.Solve(); });
		}
	};
}