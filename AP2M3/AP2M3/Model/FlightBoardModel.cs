using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AP2M3.Model.Interface;

namespace AP2M3.Model
{
    /// <summary>
    /// impliment the interface for the FlightBoardModel
    /// </summary>
    class FlightBoardModel : IFlightBoardModel
    {

        public void connect()
        {
            //thos line is very long, but what it realy does is call the NetWork's commandConnect and StartInfo function with the values from the setting
            ModelSystem.instance.netManager.commandsConnect(ApplicationSettingsModel.Instance.FlightServerIP, ApplicationSettingsModel.Instance.FlightCommandPort);
            ModelSystem.instance.netManager.StartInfo("127.0.0.1", ApplicationSettingsModel.Instance.FlightInfoPort, 30);
        }
        public void addFuncToLoggedPointEvent(RouteLogger.pointLogged func)
        {
            ModelSystem.instance.dataHolder.addFuncToLoggedPointEvent(func);
        }

    }
}
