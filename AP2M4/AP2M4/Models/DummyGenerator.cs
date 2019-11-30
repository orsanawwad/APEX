using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace AP2M4.Models
{
    /// <summary>
    /// Used for generating random points for testing.
    /// </summary>
    public class DummyGenerator
    {
        private CheckPoint currentPosition;

        private Random rnd = new Random();


        static readonly DummyGenerator _instance = new DummyGenerator();

        static DummyGenerator() { }

        private DummyGenerator()
        {
            this.currentPosition.Longitude = rnd.Next(1, 180);
            this.currentPosition.Latitude = rnd.Next(1, 180);
            this.currentPosition.Throttle = rnd.Next(0, 1);
            this.currentPosition.Rudder = rnd.Next(0, 1);
        }

        /// <summary>
        /// Generate random data
        /// </summary>
        /// <returns>Random Data</returns>
        public CheckPoint getNextPoint()
        {
            this.currentPosition.Longitude = rnd.Next(1, 180);
            this.currentPosition.Latitude = rnd.Next(1, 180);
            this.currentPosition.Throttle = rnd.Next(0, 1);
            this.currentPosition.Rudder = rnd.Next(0, 1);
            this.currentPosition.Longitude %= 180;
            this.currentPosition.Latitude %= 180;
            return currentPosition;
        }

        public static DummyGenerator Instance
        {
            get { return _instance; }
        }
    }
}