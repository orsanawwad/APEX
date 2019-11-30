using System;
using System.Collections.Generic;
using System.Text;

namespace Ex1Lib
{
    public class SingleMission : IMission
    {
        Func<double, double> functionMission;

        public SingleMission(Func<double, double> func,string name)
        {
            this.Name = name;
            this.functionMission = func;
        }

        public string Name { get; private set; }

        public string Type { get; private set; } = "Single";

        public event EventHandler<double> OnCalculate;

        public double Calculate(double value)
        {
            double result = functionMission(value);
            OnCalculate?.Invoke(this, result);
            return result;
        }
    }
}
