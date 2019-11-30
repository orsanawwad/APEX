using AP2M3.Model.Interface;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using AP2M3.Model;
using AP2M3.Model.Interface;
using AP2M3.Model.DialogService;
using AP2M3.ViewModels.Windows;

namespace AP2M3.ViewModels
{
    public class FlightBoardViewModel : BaseNotify
    {
        /// <summary>
        /// Create new instance of FlightBoard model and subscribe to events.
        /// </summary>
        IFlightBoardModel model;
        public FlightBoardViewModel()
        {
            model = new FlightBoardModel();
            model.addFuncToLoggedPointEvent(OnNewData);
        }

        /// <summary>
        /// Once new data has been given, update Lon and Lat.
        /// </summary>
        /// <param name="newPoint"></param>
        private void OnNewData(Tuple<double, double> newPoint)
        {
            Lon = newPoint.Item1;
            Lat = newPoint.Item2;
        }

        /// <summary>
        /// Lon and Lat getters and setters.
        /// </summary>
        private double lon;
        public double Lon
        {
            get { return lon; }
            set
            {
                lon = value;
                NotifyPropertyChanged("Lon");
            }
        }

        private double lat;
        public double Lat
        {
            get { return lat; }
            set
            {
                lat = value;
                NotifyPropertyChanged("Lat");
            }
        }

        

        /// <summary>
        /// Show Settings command invoked on Settings button click.
        /// </summary>
        private ICommand _showSettingsCommand;
        public ICommand ShowSettingsCommand
        {
            get
            {
                return _showSettingsCommand ?? (_showSettingsCommand = new CommandHandler(() => ShowSettings()));
            }
        }
        private void ShowSettings()
        {
            var viewModel = new SettingsWindowViewModel(new ApplicationSettingsModel());
            bool? result = DialogService.Instance.ShowDialog(viewModel);
            //Currently there is no need to check for result value, if user clicked ok it automatically saves and reload the model, if cancel got clicked nothing happens.
        }

        /// <summary>
        /// Connect command used to open the server for Command and Information channels,
        /// Invoked when clicking "Connect".
        /// </summary>
        private ICommand _connectCommand;
        public ICommand ConnectCommand
        {
            get
            {
                return _connectCommand ?? (_connectCommand = new CommandHandler(() => Connect()));
            }
        }
        private void Connect()
        {
            model.connect();
        }
    }
}
