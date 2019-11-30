using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AP2M3.Model.Interface;

namespace AP2M3.Model
{
    /// <summary>
    /// impiment the interface for FlightControlModel
    /// </summary>
    class FlightControlModel : IFlightControlModel
    {
        AutoPilotScript auto;
        public FlightControlModel()
        {
            auto = new AutoPilotScript();
        }
        public string script
        {
            set
            {
                auto.Script = value;
            }
        }
        public double throttle
        {
            set
            {
                if (ModelSystem.instance.netManager.isCommandsConnect)
                    ModelSystem.instance.dataHolder["/controls/engines/current-engine/throttle"] = value;
            }
        }
        public double rudder
        {
            set
            {
                if (ModelSystem.instance.netManager.isCommandsConnect)
                    ModelSystem.instance.dataHolder["/controls/flight/rudder"] = value;
            }
        }
        public double alieron
        {
            get
            {
                if (ModelSystem.instance.netManager.isCommandsConnect)
                    return ModelSystem.instance.dataHolder["/controls/flight/aileron"];
                return 0;
            }

            set
            {
                if (ModelSystem.instance.netManager.isCommandsConnect)
                    ModelSystem.instance.dataHolder["/controls/flight/aileron"] = value;
            }

        }
        public double elevator
        {
            get
            {
                if (ModelSystem.instance.netManager.isCommandsConnect)
                    return ModelSystem.instance.dataHolder["/controls/flight/elevator"];
                return 0;
            }
            set
            {
                if (ModelSystem.instance.netManager.isCommandsConnect)
                    ModelSystem.instance.dataHolder["/controls/flight/elevator"] = value;
            }
        }
        public double norm(double value)
        {
            return (double)Convert.ToInt32(value * 100) / (double)100;
        }
    }
}
