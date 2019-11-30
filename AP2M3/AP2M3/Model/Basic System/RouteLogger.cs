using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AP2M3.Model
{
    /// <summary>
    /// used to mange the saving and even for new points.
    /// </summary>
    class RouteLogger
    {
        public delegate void pointLogged(Tuple<double, double> newPoint);
        public event pointLogged pointLoggedEvent;
        Queue<Tuple<double, double>> points;
        public double Lat
        {
            get { return points.Peek().Item2; }
        }
        public double Lon
        {
            get { return points.Peek().Item1; }
        }

        public RouteLogger()
        {
            points = new Queue<Tuple<double, double>>();
        }

        public void logPonit(double lon, double lat)
        {
            Tuple<double, double> point = new Tuple<double, double>(lon, lat);
            points.Enqueue(point);
            pointLoggedEvent?.Invoke(point);
        }

        public Queue<Tuple<double, double>> getPoints()
        {
            return points;

        }
    }
}
