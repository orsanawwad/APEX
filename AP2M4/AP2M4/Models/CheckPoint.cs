using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Web;

namespace AP2M4.Models
{
    /// <summary>
    /// Class used for saving all the required params for /save
    /// </summary>
    public struct CheckPoint
    {
        public double Longitude;
        public double Latitude;
        public double Throttle;
        public double Rudder;

        public CheckPoint(double longitude, double latitude, double throttle, double rudder)
        {
            this.Longitude = longitude;
            this.Latitude = latitude;
            this.Throttle = throttle;
            this.Rudder = rudder;
        }
    }
}