using System;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using task2;

namespace SOLETest
{
    [TestClass]
    public class UnitTestSystemOfLinearEquation
    {
        [TestMethod]
        public void Constructor()
        {
            int m = 2;
            SystemOfLinearEquation sole = new SystemOfLinearEquation(m);
            Assert.AreEqual("0=0\n0=0\n", sole.ToString());
        }
        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void ConstructorWithNegativeArgument()
        {
            int m = -2;
            Assert.Equals(typeof(ArgumentException), new SystemOfLinearEquation(m));
        }
        [TestMethod]
        public void Get()
        {
            SystemOfLinearEquation sole = new SystemOfLinearEquation(1);
            Assert.AreEqual("0=0", sole[0].ToString());
        }
        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void GetWithIncorrectArgument()
        {
            SystemOfLinearEquation sole = new SystemOfLinearEquation(1);
            Assert.Equals(typeof(ArgumentException), sole[-4].ToString());
        }
        [TestMethod]
        public void SetAndGet()
        {
            SystemOfLinearEquation sole = new SystemOfLinearEquation(2);
            sole[0] = new LinearEquation(new double[] { 1, 2, 3 });
            Assert.AreEqual("3x2+2x1+1=0", sole[0].ToString());
        }
        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void SetWithIncorrectArgument()
        {
            SystemOfLinearEquation sole = new SystemOfLinearEquation(2);
            Assert.Equals(typeof(ArgumentException), sole[3] = new LinearEquation(new double[4] { 1, 2, 3, 6 }));
        }
        [TestMethod]
        public void Triangular()
        {
            SystemOfLinearEquation sole = new SystemOfLinearEquation(3);
            sole[0] = new LinearEquation(new double[] { -8, -1, 1, 2 });
            sole[1] = new LinearEquation(new double[] { 11, 2, -1, -3 });
            sole[2] = new LinearEquation(new double[] { 3, 2, 1, -2 });
            sole.ToTriangular();
            Assert.AreEqual("2x3+1x2-1x1-8=0\n0,5x2+0,5x1-1=0\n-1x1-1=0\n", sole.ToString());
        }
        [TestMethod]
        public void Solve()
        {
            SystemOfLinearEquation sole = new SystemOfLinearEquation(3);
            sole[0] = new LinearEquation(new double[] { -8, -1, 1, 2 });
            sole[1] = new LinearEquation(new double[] { 11, 2, -1, -3 });
            sole[2] = new LinearEquation(new double[] { 3, 2, 1, -2 });
            Assert.IsTrue(new double[] { -1, 3, 2 }.SequenceEqual(sole.Solve()));
        }
        [TestMethod]
        public void SolveWithSameEquations()
        {
            SystemOfLinearEquation sole = new SystemOfLinearEquation(4);
            sole[0] = new LinearEquation(new double[] { -8, -1, 1, 2 });
            sole[1] = new LinearEquation(new double[] { 11, 2, -1, -3 });
            sole[2] = new LinearEquation(new double[] { 11, 2, -1, -3 });
            sole[3] = new LinearEquation(new double[] { 3, 2, 1, -2 });
            Assert.IsTrue(new double[] { -1, 3, 2 }.SequenceEqual(sole.Solve()));
        }
        [TestMethod]
        [ExpectedException(typeof(ArithmeticException))]
        public void SolveWithContradictoryEquations()
        {
            SystemOfLinearEquation sole = new SystemOfLinearEquation(4);
            sole[0] = new LinearEquation(new double[] { -8, -1, 1, 2 });
            sole[1] = new LinearEquation(new double[] { 11, 2, -1, -3 });
            sole[2] = new LinearEquation(new double[] { 3, 2, 1, -2 });
            sole[3] = new LinearEquation(new double[] { 4, 2, 2, -2 });
            Assert.Equals(typeof(ArithmeticException), sole.Solve());

        }
    }
}