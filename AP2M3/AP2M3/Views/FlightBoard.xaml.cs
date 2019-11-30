using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using AP2M3.Model;
using AP2M3.ViewModels;
using Microsoft.Research.DynamicDataDisplay;
using Microsoft.Research.DynamicDataDisplay.DataSources;

namespace AP2M3.Views
{
    /// <summary>
    /// Interaction logic for MazeBoard.xaml
    /// </summary>
    public partial class FlightBoard : UserControl
    {
        //Flight board VM.
        FlightBoardViewModel vm = new FlightBoardViewModel();

        ObservableDataSource<Point> planeLocations = null;
        public FlightBoard()
        {
            InitializeComponent();
            // Change data context to FlightBoard VM.
            this.DataContext = vm;
        }

        private void UserControl_Loaded(object sender, RoutedEventArgs e)
        {
            planeLocations = new ObservableDataSource<Point>();
            // Set identity mapping of point in collection to point on plot
            planeLocations.SetXYMapping(p => p);

            plotter.AddLineGraph(planeLocations, 2, "Route");
            //Subscribe to event changes for points.
            vm.PropertyChanged += Vm_PropertyChanged;

        }

        /// <summary>
        /// Property changed event.
        /// </summary>
        private void Vm_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
        
            if(e.PropertyName.Equals("Lat") || e.PropertyName.Equals("Lon"))
            {
                //Create new points and plot it asynchronously.
                Point p1 = new Point(vm.Lon,vm.Lat);
                planeLocations.AppendAsync(Dispatcher, p1);
            }
        }

    }

}

