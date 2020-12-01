using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace task1
{
    public class Indexer
    {
        double[] arr;
        int Index_1, Index_2;
        public Indexer(double[] arr, int FirstIndex, int length)
        {
            if (arr.Length <= FirstIndex + length || FirstIndex < 0 || length < 0) throw new ArgumentException();
            this.arr = arr;
            this.Index_1 = FirstIndex;
            this.Index_2 = FirstIndex + length - 1;
        }
        public int Length
        {
            get => this.Index_2 - this.Index_1 + 1;
        }
        public double this[int index]
        {
            get
            {
                if (index < 0 || index >= this.Length) throw new IndexOutOfRangeException();
                return this.arr[index + Index_1];
            }
            set
            {
                if (index < 0 || index >= this.Length) throw new IndexOutOfRangeException();
                this.arr[index + Index_1] = value;
            }
        }
    }
}
