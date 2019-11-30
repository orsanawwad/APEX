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

namespace AP2M3.Views
{
    /// <summary>
    /// Interaction logic for AutoPilotControls.xaml
    /// </summary>
    public partial class AutoPilotControls : UserControl
    {
        // Used for color effect on text change
        private string TextBoxOldValue = "";

        public AutoPilotControls()
        {
            InitializeComponent();
        }

        private void OKClick(object sender, RoutedEventArgs e)
        {
            //Reset text box background color to white
            TextBox tb = (TextBox)FindName("AutoPilotScriptTextBox");
            tb.Background = Brushes.White;
            TextBoxOldValue = tb.Text;
        }

        private void ClearClick(object sender, RoutedEventArgs e)
        {
            //Clear text
            ((TextBox)FindName("AutoPilotScriptTextBox")).Text = "";
        }

        private void OnScriptChangeTextBox(object sender, TextChangedEventArgs e)
        {
            //If text changes, set it to LightCoral, if it changes back to the last known sent text
            //set to white (as if nothing happened, better UX.
            TextBox tb = sender as TextBox;

            if (tb.Text.Equals(TextBoxOldValue))
            {
                ((TextBox)FindName("AutoPilotScriptTextBox")).Background = Brushes.White;
            }
            else
            {
                ((TextBox)FindName("AutoPilotScriptTextBox")).Background = Brushes.LightCoral;
            }
        }
    }
}
