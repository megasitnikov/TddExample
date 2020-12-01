#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include <stdexcept>
#include "../task1/Indexer.cpp"
#include "../task1/Indexer.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IndexerTest
{
	TEST_CLASS(IndexerTest)
	{
	private:
		double* arr = new double[4]{ 1, 2, 3, 4 };
	public:

		TEST_METHOD(HaveCorrectLength)
		{
			auto indexer = Indexer(arr, 4, 1, 2);
			Assert::AreEqual(2, indexer.Length());
		}
		TEST_METHOD(GetCorrectly)
		{
			auto indexer = Indexer(arr, 4, 1, 2);
			Assert::AreEqual((double)2, indexer[0]);
			Assert::AreEqual((double)3, indexer[1]);
		}
		TEST_METHOD(SetCorrectly)
		{
			auto indexer = Indexer(arr, 4, 1, 2);
			indexer[0] = 10;
			Assert::AreEqual((double)10, arr[1]);
		}
		TEST_METHOD(IndexerDoesNotCopyArray)
		{
			auto indexer1 = Indexer(arr, 4, 1, 2);
			auto indexer2 = Indexer(arr, 4, 0, 2);
			indexer1[0] = 100500;
			Assert::AreEqual((double)100500, indexer2[1]);
		}
		TEST_METHOD(FailWithWrongArguments1)
		{
			Assert::ExpectException<invalid_argument>([&] { Indexer(arr, 4, -1, 3); });

		}
		TEST_METHOD(FailWithWrongArguments2)
		{
			Assert::ExpectException<invalid_argument>([&] { Indexer(arr, 4, 1, -1); });

		}
		TEST_METHOD(FailWithWrongArguments3)
		{
			Assert::ExpectException<invalid_argument>([&] { Indexer(arr, 4, 1, 10); });
		}
		TEST_METHOD(FailWithWrongIndexing1)
		{
			auto indexer = Indexer(arr, 4, 1, 2);
			Assert::ExpectException<out_of_range>([&] { indexer[-1]; });
		}
		TEST_METHOD(FailWithWrongIndexing2)
		{
			auto indexer = Indexer(arr, 4, 1, 2);
			Assert::ExpectException<out_of_range>([&] { indexer[10]; });
		}
	};
}