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
    /// Interaction logic for FGNameValue.xaml
    /// </summary>
    public partial class FGNameValue : UserControl
    {
        public static readonly DependencyProperty NameHolderProperty =
            DependencyProperty.Register(
                "NameHolder", typeof(string),
                typeof(FGNameValue),
                new PropertyMetadata("DefaultControl", NameHolderChanged)
            );

        public string NameHolder
        {
            get { return (string)GetValue(NameHolderProperty); }
            set { SetValue(NameHolderProperty, value); }
        }

        private static void NameHolderChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            (d as FGNameValue).SetNameHolder(e);
        }

        private void SetNameHolder(DependencyPropertyChangedEventArgs e)
        {
            ((Label) FindName("NameHolderLabel")).Content = e.NewValue;
        }

        public static readonly DependencyProperty ValueHolderProperty =
            DependencyProperty.Register(
                "ValueHolder", typeof(string),
                typeof(FGNameValue),
                new PropertyMetadata("DefaultControl", ValueHolderChanged)
            );

        public string ValueHolder
        {
            get { return (string)GetValue(ValueHolderProperty); }
            set { SetValue(ValueHolderProperty, value); }
        }

        private static void ValueHolderChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            (d as FGNameValue).SetValueHolder(e);
        }

        private void SetValueHolder(DependencyPropertyChangedEventArgs e)
        {
            string s = string.Format("{0:#,#0.00}", e.NewValue);
            if (s.Equals("0"))
            {
                s = "0.00";
            }
            ((Label)FindName("ValueHolderLabel")).Content = s;
        }

        public FGNameValue()
        {
            InitializeComponent();
        }
    }
}
