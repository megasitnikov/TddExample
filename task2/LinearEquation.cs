using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace task2
{
    public class LinearEquation
    {
        double[] coefficients;
        public LinearEquation(string str)
        {
            string[] sArr = str.Split(new char[] { ' ', '\t', '\n', '\r' }, StringSplitOptions.RemoveEmptyEntries);
            if (sArr.Length == 0) this.coefficients = new double[] { 0, 0 };
            else if (sArr.Length == 1)
            {
                try
                {
                    this.coefficients = new double[] { double.Parse(sArr[0]), 0 };
                }
                catch
                {
                    throw new ArgumentException();
                }
            }
            else
            {
                this.coefficients = new double[sArr.Length];
                try
                {
                    for (int i = 0; i < sArr.Length; i++)
                    {
                        this.coefficients[i] = double.Parse(sArr[i]);
                    }
                }
                catch
                {
                    throw new ArgumentException();
                }
            }
        }
        public LinearEquation(IList<double> list)
        {
            if (list.Count == 0) this.coefficients = new double[] { 0, 0 };
            else if (list.Count == 1) this.coefficients = new double[] { list[0], 0 };
            else this.coefficients = (double[])list.ToArray().Clone();
        }
        public LinearEquation(LinearEquation le)
        {
            this.coefficients = (double[])le.coefficients.Clone();
        }
        public LinearEquation(int n)
        {
            if (n >= 2) this.coefficients = new double[n];
            else if (n >= 0) this.coefficients = new double[2];
            else throw new ArgumentException();
        }
        public void FillByDuplicates(double number)
        {
            this.coefficients = Enumerable.Repeat(number, this.coefficients.Length).ToArray();
        }
        public void FillByRandom(double minValue, double maxValue, int seed)
        {
            if (maxValue < minValue) throw new ArgumentException();
            Random Rand = new Random(seed);
            for (int i = 0; i < this.coefficients.Length; i++)
            {
                this.coefficients[i] = Rand.NextDouble() * (maxValue - minValue) + minValue;
            }
        }
        public void FillByRandom(double minValue, double maxValue)
        {
            if (maxValue < minValue) throw new ArgumentException();
            Random Rand = new Random();
            for (int i = 0; i < this.coefficients.Length; i++)
            {
                this.coefficients[i] = Rand.NextDouble() * (maxValue - minValue) + minValue;
            }
        }
        public int Degree
        {
            get
            {
                int degree = 0;
                for (int i = 0; i < this.coefficients.Length; i++)
                {
                    if (this.coefficients[i] != 0) degree = i;
                }
                return degree;
            }
        }
        public static LinearEquation operator +(LinearEquation le1, LinearEquation le2)
        {
            int count = Math.Max(le1.coefficients.Length, le2.coefficients.Length);
            LinearEquation result = new LinearEquation(count);
            for (int i = 0; i < count; i++)
            {
                result.coefficients[i] = ((i < le1.coefficients.Length) ? le1.coefficients[i] : 0) + ((i < le2.coefficients.Length) ? le2.coefficients[i] : 0);
            }
            return result;
        }
        public static LinearEquation operator -(LinearEquation le1, LinearEquation le2)
        {
            int count = Math.Max(le1.coefficients.Length, le2.coefficients.Length);
            LinearEquation result = new LinearEquation(count);
            for (int i = 0; i < count; i++)
            {
                result.coefficients[i] = ((i < le1.coefficients.Length) ? le1.coefficients[i] : 0) - ((i < le2.coefficients.Length) ? le2.coefficients[i] : 0);
            }
            return result;
        }
        public static LinearEquation operator *(LinearEquation le, double k)
        {
            LinearEquation result = new LinearEquation(le);
            for (int i = 0; i < result.coefficients.Length; i++)
            {
                result.coefficients[i] *= k;
            }
            return result;
        }
        public static LinearEquation operator *(double k, LinearEquation le)
        {
            return le * k;
        }
        public static LinearEquation operator -(LinearEquation le)
        {
            return -1 * le;
        }
        public static bool operator ==(LinearEquation le1, LinearEquation le2)
        {
            int count = Math.Max(le1.coefficients.Length, le2.coefficients.Length);
            for (int i = 0; i < count; i++)
            {
                bool isInequal = (i < le1.coefficients.Length && i >= le2.coefficients.Length && le1.coefficients[i] != 0) ||
                                 (i >= le1.coefficients.Length && i < le2.coefficients.Length && le2.coefficients[i] != 0) ||
                                 (i < le1.coefficients.Length && i < le2.coefficients.Length && le1.coefficients[i] != le2.coefficients[i]);
                if (isInequal) return false;
            }
            return true;
        }
        public static bool operator !=(LinearEquation le1, LinearEquation le2)
        {
            return !(le1 == le2);
        }
        public static bool operator true(LinearEquation le)
        {
            if (le.coefficients[0] == 0) return true;
            for (int i = 1; i < le.coefficients.Length; i++)
            {
                if (le.coefficients[i] != 0) return true;
            }
            return false;
        }
        public static bool operator false(LinearEquation le)
        {
            return le ? false : true;
        }
        public override string ToString()
        {
            string result = "";
            for (int i = this.coefficients.Length - 1; i >= 0; i--)
            {
                if (this.coefficients[i] != 0)
                {
                    if (result != "" && this.coefficients[i] > 0) result += "+";
                    result += $"{this.coefficients[i]}";
                    if (i != 0) result += $"x{i}";
                }
            }
            if (result == "") result += "0";
            result += "=0";
            return result;
        }
        public double this[int index]
        {
            get
            {
                if (index < 0 || index > this.Degree) throw new ArgumentOutOfRangeException();
                return this.coefficients[index];
            }
        }
        public static implicit operator double[](LinearEquation le)
        {
            return le.coefficients;
        }
    }
}
