using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AP2M3.Model.EventArgs
{
    /// <summary>
    /// Event args used for joystick.
    /// </summary>
    public class VirtualJoystickEventArgs
    {
        public double Aileron { get; set; }
        public double Elevator { get; set; }
    }
}
