using System;
using System.Threading;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AP2M3.Model
{
    /// <summary>
    /// used to hold all the data, used as a middle man between the si,ulator and the view's model. 
    /// </summary>
    class DataBase
    {
        public delegate void dataUpdate(string name, double newVal);
        public event dataUpdate dataUpdateEvent;
        Dictionary<string, double> symbolTaable;
        Mutex mutex;
        RouteLogger routeLogger;


        public double this[string name]
        {
            get { return symbolTaable[name]; }
            set
            {
                mutex.WaitOne();
                symbolTaable[name] = value;
                dataUpdateEvent?.Invoke(name,value);
                mutex.ReleaseMutex();
            }
        }

        public bool isInDataBase(string name)
        {
            return symbolTaable.ContainsKey(name);
        }


        public DataBase()
        {
            this.mutex = new Mutex();
            symbolTaable = new Dictionary<string, double>();
            routeLogger = new RouteLogger();
        }

        public double getValue(string name)
        {
            return symbolTaable[name];
        }


        public Queue<Tuple<double, double>> getLogger()
        {
            return routeLogger.getPoints();
        }

        public void updateFromServer(Dictionary<string, double> updates)
        {
            bool isNowPoint = false;
            foreach (var update in updates)
            {
                
                if (update.Key == "Lon" || update.Key == "Lat") { isNowPoint = true; }
                symbolTaable[update.Key] = update.Value;

            }
            if (isNowPoint) { routeLogger.logPonit(this["Lon"], this["Lat"]); }

        }

        public void printData()
        {
            foreach (var k in symbolTaable.Keys)
            {
                Console.Write("(" + k + "," + symbolTaable[k] + "),");
            }
        }

        public void addFuncToLoggedPointEvent(RouteLogger.pointLogged func)
        {
            routeLogger.pointLoggedEvent += func;
        }
    }
    

}
