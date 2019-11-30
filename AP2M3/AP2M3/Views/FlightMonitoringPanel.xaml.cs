using System;
using System.Collections.Generic;
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
using AP2M3.ViewModels.Windows;

namespace AP2M3.Views
{
    /// <summary>
    /// Interaction logic for FlightMonitoringPanel.xaml
    /// </summary>
    public partial class FlightMonitoringPanel : UserControl
    {
        public FlightMonitoringPanel()
        {
            InitializeComponent();
            //Set data context to FlightBoardVM
            this.DataContext = new FlightBoardViewModel();
        }
    }
}
