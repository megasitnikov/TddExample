using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace task2
{
    public class SystemOfLinearEquation
    {
        LinearEquation[] equations;
        public SystemOfLinearEquation(int m)
        {
            if (m <= 0)
            {
                throw new ArgumentException();
            }
            this.equations = new LinearEquation[m];
            for (int i = 0; i < m; i++)
            {
                this.equations[i] = new LinearEquation(2);
            }
        }
        public LinearEquation this[int i]
        {
            get
            {
                if (i < 0 || i >= this.equations.Length)
                {
                    throw new ArgumentException();
                }
                return this.equations[i];
            }
            set
            {
                if (i < 0 || i >= this.equations.Length)
                {
                    throw new ArgumentException();
                }
                this.equations[i] = new LinearEquation(value);
            }
        }
        public void ToTriangular()
        {
            Array.Sort(this.equations, (x, y) => (-1 * x.Degree.CompareTo(y.Degree)));
            int maxDegree = this.equations[0].Degree,
                degreeLimit = Math.Max(maxDegree - this.equations.Length + 1, 1),
                numberOfEquation = 0;
            for (int d = maxDegree; d >= degreeLimit; d--)
            {
                if (this.equations[numberOfEquation].Degree < d) continue;
                for (int i = numberOfEquation + 1; i < this.equations.Length; i++)
                {
                    if (this.equations[i].Degree >= d) this.equations[i] = this.equations[i] - this.equations[numberOfEquation] * (this.equations[i][d] / this.equations[numberOfEquation][d]);
                }
                Array.Sort(this.equations, (x, y) => (-1 * x.Degree.CompareTo(y.Degree)));
                numberOfEquation += 1;
            }
        }
        public double[] Solve()
        {
            SystemOfLinearEquation sole = new SystemOfLinearEquation(this.equations.Length);
            for (int i = 0; i < sole.equations.Length; i++)
            {
                sole.equations[i] = new LinearEquation(this.equations[i]);
            }
            sole.ToTriangular();
            for (int i = 0; i < sole.equations.Length; i++)
            {
                if (sole.equations[i]) continue;
                else throw new ArithmeticException();
            }
            double[] result = new double[sole.equations[0].Degree];
            result = Enumerable.Repeat(double.PositiveInfinity, result.Length).ToArray();
            for (int i = sole.equations.Length - 1; i >= 0; i--)
            {
                if (sole.equations[i].Degree == 0 || !double.IsInfinity(result[sole.equations[i].Degree - 1])) continue;
                result[sole.equations[i].Degree - 1] = -sole.equations[i][0];
                for (int j = sole.equations[i].Degree - 1; j >= 1; j--)
                {
                    if (!double.IsInfinity(result[j - 1])) result[sole.equations[i].Degree - 1] -= sole.equations[i][j] * result[j - 1];
                    else
                    {
                        result[sole.equations[i].Degree - 1] = double.PositiveInfinity;
                        break;
                    }
                }
                result[sole.equations[i].Degree - 1] /= sole.equations[i][sole.equations[i].Degree];
            }
            return result;
        }
        public override string ToString()
        {
            string result = "";
            for (int i = 0; i < this.equations.Length; i++)
            {
                result += this.equations[i] + "\n";
            }
            return result;
        }
    }
}