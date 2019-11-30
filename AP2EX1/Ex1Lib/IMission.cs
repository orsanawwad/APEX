using System;
using System.Collections.Generic;
using System.Text;

namespace Ex1Lib
{
    public interface IMission
    {
        event EventHandler<double> OnCalculate;  // An Event of when a mission is activated

        String Name { get; }
        String Type { get; }

        double Calculate(double value);
    }
}
