using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AP2M3.Model.Interface
{
    interface IFlightControlModel
    {
        string script //the messages to send to the server
        {
            set;
        }
        double throttle
        {
            set;
        }
        double rudder
        {
            set;
        }
        double alieron
        {
            get;
            set;

        }
        double elevator
        {
            get;
            set;
        }
        //norm the values from the view. at fi
        double norm(double value);
    }
}

