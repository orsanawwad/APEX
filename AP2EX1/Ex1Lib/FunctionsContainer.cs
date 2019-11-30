using System;
using System.Collections.Generic;
using System.Text;

namespace Ex1Lib
{
    public class FunctionsContainer
    {
        Dictionary<string, Func<double, double>> functions = new Dictionary<string, Func<double, double>>();
        public Func<double, double> this[string key]
        {
            get {
                if (functions.ContainsKey(key))
                {
                    return functions[key];
                }
                else
                {
                    functions[key] = val => val;
                    return functions[key];
                }
            }
            set { functions[key] = value; }
        }

        public List<string> getAllMissions()
        {
            return new List<string>(functions.Keys);
        }
    }
}
