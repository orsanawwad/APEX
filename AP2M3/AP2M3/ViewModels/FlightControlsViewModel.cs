using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using AP2M3.Model;
using AP2M3.Model.Interface;
using AP2M3.Model.DialogService;

namespace AP2M3.ViewModels
{
    /// <summary>
    /// Flight Controls ViewModel used to keep track of Joystick and slider values
    /// and updated the model accordingly.
    /// </summary>
    class FlightControlsViewModel : BaseNotify
    {
        IFlightControlModel model;

        /// <summary>
        /// Aileron auto-updated value.
        /// </summary>
        private double _aileron;
        public double AileronVM
        {
            get { return (_aileron); }
            set
            {
                value = model.norm(value);
                _aileron = value;
                NotifyPropertyChanged("AileronVM");
                model.elevator = value;
            }
        }

        /// <summary>
        /// Elevator auto-updated value.
        /// </summary>
        private double _elevator;
        public double ElevatorVM
        {
            get { return (_elevator); }
            set
            {
                value = model.norm(value);
                _elevator = value;
                NotifyPropertyChanged("ElevatorVM");
                model.alieron = value;
            }
        }

        /// <summary>
        /// Aileron step constant.
        /// </summary>
        private double _aileronStep;
        public double AileronStepVM
        {
            get { return (_aileronStep); }
            set
            {
                _aileronStep = value;
                NotifyPropertyChanged("AileronStepVM");
                model.elevator += value;
            }
        }


        /// <summary>
        /// Elevator step constant.
        /// </summary>
        private double _elevatorStep;
        public double ElevatorStepVM
        {
            get { return (_elevatorStep); }
            set
            {
                _elevatorStep = value;
                NotifyPropertyChanged("ElevatorStepVM");
                model.alieron += value;
            }
        }

        /// <summary>
        /// Throttle auto-updated value.
        /// </summary>
        private double _throttle;
        public double ThrottleVM
        {
            get { return (_throttle); }
            set
            {
                _throttle = value;
                NotifyPropertyChanged("ThrottleVM");
                model.throttle = value;
            }
        }

        /// <summary>
        /// Rudder auto-updated value.
        /// </summary>
        private double _rudder;
        public double RudderVM
        {
            get { return (_rudder); }
            set
            {
                _rudder = value;
                NotifyPropertyChanged("RudderVM");
                model.rudder = value;
            }
        }

        /// <summary>
        /// Auto Pilot control script.
        /// </summary>
        private string _autoPilotScript;
        public string AutoPilotScriptVM
        {
            get { return (_autoPilotScript); }
            set
            {
                Debug.Print(nameof(AutoPilotScriptVM) + value.ToString());
                _autoPilotScript = value;
                if (ModelSystem.instance.netManager.isCommandsConnect)
                    NotifyPropertyChanged("AutoPilotScriptVM");
            }
        }

        /// <summary>
        /// Flight Control VM used to supply model.
        /// </summary>
        /// <param name="model">Flight Control model</param>
        public FlightControlsViewModel(IFlightControlModel model)
        {
            this.model = model;
        }

        /// <summary>
        /// Flight Control VM used to setup model.
        /// </summary>
        public FlightControlsViewModel()
        {
            this.model = new FlightControlModel();
        }

        /// <summary>
        /// Auto Pilot invocation command, sends the script to the parser module and
        /// controls the flight.
        /// </summary>
        private ICommand _autoPilotOKCommand;
        public ICommand AutoPilotOKCommand
        {
            get
            {
                return _autoPilotOKCommand ?? (_autoPilotOKCommand = new ActionCommand(p => OnOKClick((string)p)));
            }
        }
        private void OnOKClick(string o)
        {
            if (ModelSystem.instance.netManager.isCommandsConnect)
                model.script = o;
        }
    }
}
