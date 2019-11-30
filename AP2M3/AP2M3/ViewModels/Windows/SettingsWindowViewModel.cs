using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using AP2M3.Model;
using AP2M3.Model.DialogService;
using AP2M3.Model.Interface;

namespace AP2M3.ViewModels.Windows
{
    /// <summary>
    /// Settings Window ViewModel used to keep track of text box values
    /// and update the Software built-in properties system.
    /// </summary>
    public class SettingsWindowViewModel : BaseNotify, IDialogRequestClose
    {
        private ISettingsModel model;

        public SettingsWindowViewModel(ISettingsModel model)
        {
            this.model = model;
        }

        /// <summary>
        /// Initial values are taken from the model, then after that
        /// it gets updated here locally in the VM, once OK has been clicked
        /// it gets sent to the model.
        /// </summary>

        private string flightServerIP = null;
        public string FlightServerIP
        {
            get
            {
                if (flightServerIP == null)
                {
                    flightServerIP = model.FlightServerIP;
                }

                return flightServerIP;
            }
            set
            {
                this.flightServerIP = value;
            }
        }

        public int? flightCommandPort = null;
        public int FlightCommandPort
        {
            get
            {
                if (flightCommandPort == null)
                {
                    flightCommandPort = model.FlightCommandPort;
                }
                return (int) flightCommandPort;
            }
            set
            {
                this.flightCommandPort = value;
            }
        }


        public int? flightInfoPort = null;
        public int FlightInfoPort
        {
            get
            {
                if (flightInfoPort == null)
                {
                    flightInfoPort = model.FlightInfoPort;
                }
                return (int) flightInfoPort;
            }
            set
            {
                this.flightInfoPort = value;
            }
        }

     

        public void SaveSettings()
        {
            model.SaveSettings();
        }

        public void ReloadSettings()
        {
            model.ReloadSettings();
        }

        #region Commands
        #region ClickCommand
        /// <summary>
        /// Invoked when clicking OK in the settings dialog, updates all the
        /// values in the model and notifies subscribers of change.
        /// </summary>
        private ICommand _clickCommand;
        public ICommand ClickCommand
        {
            get
            {
                return _clickCommand ?? (_clickCommand = new CommandHandler(() => OnClick()));
            }
        }
        private void OnClick()
        {
            model.FlightServerIP = this.FlightServerIP;
            model.FlightCommandPort = this.FlightCommandPort;
            model.FlightInfoPort = this.FlightInfoPort;

            model.SaveSettings();

            NotifyPropertyChanged("FlightServerIP");
            NotifyPropertyChanged("FlightCommandPort");
            NotifyPropertyChanged("FlightInfoPort");


            CloseRequested?.Invoke(this, new DialogCloseRequestedEventArgs(true));
        }
        #endregion

        #region CancelCommand
        /// <summary>
        /// Closes the dialog when clicking cancel.
        /// </summary>
        private ICommand _cancelCommand;
        public ICommand CancelCommand
        {
            get
            {
                return _cancelCommand ?? (_cancelCommand = new CommandHandler(() => OnCancel()));
            }
        }
        private void OnCancel()
        {
            model.ReloadSettings();
            CloseRequested?.Invoke(this, new DialogCloseRequestedEventArgs(false));
        }
        #endregion
        #endregion

        public event EventHandler<DialogCloseRequestedEventArgs> CloseRequested;
    }
}

