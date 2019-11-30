using System;
using System.Collections.Generic;
using System.Text;

namespace Ex1Lib
{
    public class ComposedMission : IMission
    {

        List<Func<double, double>> missionFunctions = new List<Func<double, double>>();

        public ComposedMission(string name)
        {
            this.Name = name;
        }

        public ComposedMission Add(Func<double,double> func)
        {
            missionFunctions.Add(func);
            return this;
        }

        public string Name { get; private set; }

        public string Type { get; private set; } = "Composed";

        public event EventHandler<double> OnCalculate;

        public double Calculate(double value)
        {
            double result = value;
            foreach (var func in missionFunctions)
            {
                result = func(result);
            }
            OnCalculate?.Invoke(this, result);
            return result;
        }
    }
}
