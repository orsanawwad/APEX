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
using AP2M3.ViewModels;

namespace AP2M3.Views
{
    /// <summary>
    /// Interaction logic for FGSliderControl.xaml
    /// </summary>
    public partial class PlaneControlsPanel : UserControl
    {
        public PlaneControlsPanel()
        {
            InitializeComponent();
            // Use flight controls VM as context.
            this.DataContext = new FlightControlsViewModel();
        }
    }
}
