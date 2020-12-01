using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using task2;

namespace LETest
{
    [TestClass]
    public class UnitTestLinearEquation
    {
        [TestMethod]
        public void StringConstructor()
        {
            string s = "1 1,5 2,6 -4 89 13,4";
            LinearEquation le = new LinearEquation(s);
            Assert.IsTrue(new double[] { 1, 1.5, 2.6, -4, 89, 13.4 }.SequenceEqual((double[])le));
        }
        [TestMethod]
        public void StringConstructorWithEmptyString()
        {
            string s = "";
            LinearEquation le = new LinearEquation(s);
            Assert.IsTrue(new double[] { 0, 0 }.SequenceEqual((double[])le));
        }
        [TestMethod]
        public void StringConstructorWithOneElement()
        {
            string s = "2";
            LinearEquation le = new LinearEquation(s);
            Assert.IsTrue(new double[] { 2, 0 }.SequenceEqual((double[])le));
        }
        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void StringConstructorWithIncorrectString()
        {
            string s = "1 g 2.25 -5.7 helloworld 3 k";
            Assert.Equals(typeof(ArgumentException), new LinearEquation(s));
        }
        [TestMethod]
        public void ListConstructorWithArray()
        {
            double[] arr = new double[4] { 0, -5.6, 4, 7 };
            LinearEquation le = new LinearEquation(arr);
            Assert.IsTrue(arr.SequenceEqual((double[])le));
        }
        [TestMethod]
        public void ListConstructorWithList()
        {
            List<double> l = new List<double>() { 5, 7, 2.4, -78, 3 };
            LinearEquation le = new LinearEquation(l);
            Assert.IsTrue(l.SequenceEqual((double[])le));
        }
        [TestMethod]
        public void ListConstructorWithEmptyCollection()
        {
            double[] arr = new double[] { };
            LinearEquation le = new LinearEquation(arr);
            Assert.IsTrue(new double[] { 0, 0 }.SequenceEqual((double[])le));
        }
        [TestMethod]
        public void ListConstructorWithOneElement()
        {
            double[] arr = new double[] { 5 };
            LinearEquation le = new LinearEquation(arr);
            Assert.IsTrue(new double[] { 5, 0 }.SequenceEqual((double[])le));
        }
        [TestMethod]
        public void LinearEquationConstructor()
        {
            double[] arr = new double[4] { 0, -5.6, 4, 7 };
            LinearEquation le1 = new LinearEquation(arr);
            LinearEquation le2 = new LinearEquation(le1);
            Assert.IsTrue(((double[])le1).SequenceEqual((double[])le2));
        }
        [TestMethod]
        public void IntConstructor()
        {
            int n = 3;
            LinearEquation le = new LinearEquation(n);
            Assert.IsTrue(new double[] { 0, 0, 0 }.SequenceEqual((double[])le));
        }
        [TestMethod]
        public void IntConstructorWithZero()
        {
            int n = 0;
            LinearEquation le = new LinearEquation(n);
            Assert.IsTrue(new double[] { 0, 0 }.SequenceEqual((double[])le));
        }
        [TestMethod]
        public void IntConstructorWithOne()
        {
            int n = 1;
            LinearEquation le = new LinearEquation(n);
            Assert.IsTrue(new double[] { 0, 0 }.SequenceEqual((double[])le));
        }
        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void IntConstructorWithNegativeArgument()
        {
            int n = -1;
            Assert.Equals(typeof(ArgumentException), new LinearEquation(n));
        }
        [TestMethod]
        public void FillByDuplicates()
        {
            int n = 4;
            LinearEquation le = new LinearEquation(n);
            le.FillByDuplicates(7.3);
            Assert.IsTrue(new double[] { 7.3, 7.3, 7.3, 7.3 }.SequenceEqual((double[])le));
        }
        [TestMethod]
        public void FillByRandomWithMinMoreThanMaxArguments()
        {
            int n = 3;
            LinearEquation le = new LinearEquation(n);
            Assert.ThrowsException<ArgumentException>(() => le.FillByRandom(100, 10));
        }
        [TestMethod]
        public void FillByRandomWithEqualSeeds()
        {
            int n = 3;
            LinearEquation le1 = new LinearEquation(n);
            LinearEquation le2 = new LinearEquation(n);
            le1.FillByRandom(-5, 10, 100);
            le2.FillByRandom(-5, 10, 100);
            Assert.IsTrue(((double[])le1).SequenceEqual((double[])le2));
        }
        [TestMethod]
        public void Degree()
        {
            LinearEquation le = new LinearEquation(new double[3] { 1, 2, 3 });
            Assert.AreEqual(2, le.Degree);
        }
        [TestMethod]
        public void DegreeWithZeros()
        {
            LinearEquation le = new LinearEquation(new double[5] { 1, 2, 3, 0, 0 });
            Assert.AreEqual(2, le.Degree);
        }
        [TestMethod]
        public void AdditionWithSameCountOfCoefficients()
        {
            LinearEquation le1 = new LinearEquation(new double[3] { 1, 2, 3 });
            LinearEquation le2 = new LinearEquation(new double[3] { 4, 5, 6 });
            Assert.IsTrue((new double[3] { 5, 7, 9 }).SequenceEqual((double[])(le1 + le2)));
        }
        [TestMethod]
        public void AdditionWithDifferentCountOfCoefficients()
        {
            LinearEquation le1 = new LinearEquation(new double[4] { 1, -5, 3, 7 });
            LinearEquation le2 = new LinearEquation(new double[3] { 4, 5, 6 });
            Assert.IsTrue((new double[4] { 5, 0, 9, 7 }).SequenceEqual((double[])(le1 + le2)));
        }
        [TestMethod]
        public void SubstractionWithSameCountOfCoefficients()
        {
            LinearEquation le1 = new LinearEquation(new double[3] { 5, 2, 0 });
            LinearEquation le2 = new LinearEquation(new double[3] { 1, 5, 1 });
            Assert.IsTrue((new double[3] { 4, -3, -1 }).SequenceEqual((double[])(le1 - le2)));
        }
        [TestMethod]
        public void SubstractionWithDifferentCountOfCoefficients()
        {
            LinearEquation le1 = new LinearEquation(new double[3] { 4, 5, 3 });
            LinearEquation le2 = new LinearEquation(new double[4] { 1, 5, 6, 8 });
            Assert.IsTrue((new double[4] { 3, 0, -3, -8 }).SequenceEqual((double[])(le1 - le2)));
        }
        [TestMethod]
        public void LeftMultiplication()
        {
            LinearEquation le = new LinearEquation(new double[3] { 4, -5, 3 });
            double k = 2;
            Assert.IsTrue((new double[3] { 8, -10, 6 }).SequenceEqual((double[])(k * le)));
        }
        [TestMethod]
        public void RightMultiplication()
        {
            LinearEquation le = new LinearEquation(new double[3] { -4, 0, 7 });
            double k = 3;
            Assert.IsTrue((new double[3] { -12, 0, 21 }).SequenceEqual((double[])(le * k)));
        }

        [TestMethod]
        public void UnaryMinus()
        {
            LinearEquation le = new LinearEquation(new double[3] { -2, 0, 4 });
            Assert.IsTrue((new double[3] { 2, 0, -4 }).SequenceEqual((double[])(-le)));
        }
        [TestMethod]
        public void EqualityWithSameCountOfCoefficients()
        {
            LinearEquation le1 = new LinearEquation(new double[3] { 1, 2, 3 });
            LinearEquation le2 = new LinearEquation(new double[3] { 1, 2, 3 });
            Assert.IsTrue(le1 == le2);
        }
        [TestMethod]
        public void EqualityWithDifferentCountOfCoefficients()
        {
            LinearEquation le1 = new LinearEquation(new double[3] { 1, 2, 3 });
            LinearEquation le2 = new LinearEquation(new double[5] { 1, 2, 3, 0, 0 });
            Assert.IsTrue(le1 == le2);
        }
        [TestMethod]
        public void Inequality()
        {
            LinearEquation le1 = new LinearEquation(new double[3] { 1, 2, 3 });
            LinearEquation le2 = new LinearEquation(new double[3] { 1, 6, 3 });
            Assert.IsTrue(le1 != le2);
        }
        [TestMethod]
        public void TrueLinearEquation()
        {
            LinearEquation le = new LinearEquation(new double[3] { 1, 2, 1 });
            Assert.IsTrue(le ? true : false);
        }
        [TestMethod]
        public void FalseLinearEquation()
        {
            LinearEquation le = new LinearEquation(new double[3] { 2, 0, 0 });
            Assert.IsFalse(le ? true : false);
        }
        [TestMethod]
        public void Coefficient()
        {
            LinearEquation le = new LinearEquation(new double[3] { 2, 3, 1 });
            Assert.AreEqual(3, le[1]);
        }
        [TestMethod]
        [ExpectedException(typeof(ArgumentOutOfRangeException))]
        public void CoefficientOutOfRange()
        {
            LinearEquation le = new LinearEquation(new double[6] { 2, 3, 1, 0, 0, 0 });
            Assert.Equals(typeof(ArgumentOutOfRangeException), le[4]);
        }
        [TestMethod]
        public void ToString()
        {
            LinearEquation le = new LinearEquation(new double[3] { 2, 1, 4 });
            Assert.AreEqual("4x2+1x1+2=0", le.ToString());
        }
        [TestMethod]
        public void ToStringWithMinus()
        {
            LinearEquation le = new LinearEquation(new double[3] { 2, -1, 4 });
            Assert.AreEqual("4x2-1x1+2=0", le.ToString());
        }
        [TestMethod]
        public void ToStringWithZeroArgument()
        {
            LinearEquation le = new LinearEquation(new double[4] { 2, 1, 0, 4 });
            Assert.AreEqual("4x3+1x1+2=0", le.ToString());
        }
    }
}