using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AP2M3.Model.Interface
{
    interface IFlightBoardModel
    {
        void connect(); //connect to the server and the simulator 
        void addFuncToLoggedPointEvent(RouteLogger.pointLogged func); //add function tot he event of new point

    }
}
