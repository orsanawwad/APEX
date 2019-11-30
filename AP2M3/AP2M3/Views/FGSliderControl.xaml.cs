using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using AP2M3.Model;

namespace AP2M3.Views
{
    /// <summary>
    /// Interaction logic for UserControl1.xaml
    ///
    /// Defines few custom properties used for custom view setup.
    /// 
    /// </summary>
    public partial class FGSliderControl : UserControl
    {
        #region SliderValueProperty
        public static readonly DependencyProperty SliderValueProperty =
            DependencyProperty.Register("SliderValue", typeof(double), typeof(FGSliderControl), new PropertyMetadata(0.0));

        public double SliderValue
        {
            get { return (double)GetValue(SliderValueProperty); }
            set { SetValue(SliderValueProperty, value); }
        }
        #endregion

        #region SliderMinValueProperty
        public static readonly DependencyProperty SliderMinValueProperty =
            DependencyProperty.Register("SliderMinValue", typeof(double), typeof(FGSliderControl), new PropertyMetadata(0.0, SliderMinValueChanged));

        private static void SliderMinValueChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            (d as FGSliderControl).SetMinValue(e);
        }

        private void SetMinValue(DependencyPropertyChangedEventArgs e)
        {
            ((Slider)FindName("FgControlSlider")).Minimum = (double)e.NewValue;
        }

        public double SliderMinValue
        {
            get { return (double)GetValue(SliderMinValueProperty); }
            set { SetValue(SliderMinValueProperty, value); }
        }
        #endregion

        #region SliderMaxValueProperty
        public static readonly DependencyProperty SliderMaxValueProperty =
            DependencyProperty.Register("SliderMaxValue", typeof(double), typeof(FGSliderControl), new PropertyMetadata(0.0, SliderMaxValueChanged));

        private static void SliderMaxValueChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            (d as FGSliderControl).SetMaxValue(e);
        }

        private void SetMaxValue(DependencyPropertyChangedEventArgs e)
        {
            ((Slider)FindName("FgControlSlider")).Maximum = (double)e.NewValue;
        }


        public double SliderMaxValue
        {
            get { return (double)GetValue(SliderMaxValueProperty); }
            set { SetValue(SliderMaxValueProperty, value); }
        }
        #endregion

        #region NameHolderProperty
        public static readonly DependencyProperty NameHolderProperty =
            DependencyProperty.Register("NameHolder", typeof(string), typeof(FGSliderControl), new PropertyMetadata("DefaultName", NameHolderChanged));

        private static void NameHolderChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            (d as FGSliderControl).SetNameHolder(e);
        }

        private void SetNameHolder(DependencyPropertyChangedEventArgs e)
        {
            ((Label)FindName("NameHolderLabel")).Content = e.NewValue;
        }

        public string NameHolder
        {
            get { return (string)GetValue(NameHolderProperty); }
            set { SetValue(NameHolderProperty, value); }
        }
        #endregion

        #region LTRFlagProperty
        public static readonly DependencyProperty LTRFlagProperty =
            DependencyProperty.Register("LTRFlag", typeof(bool), typeof(FGSliderControl), new PropertyMetadata(false, LTRFlagChanged));

        private static void LTRFlagChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            (d as FGSliderControl).ConfigureLTR(e);
        }

        private void ConfigureLTR(DependencyPropertyChangedEventArgs e)
        {
            ((ColumnDefinition) FindName("FirstColumn")).Width = new GridLength(1, GridUnitType.Star);
            ((ColumnDefinition) FindName("SecondColumn")).Width = new GridLength(9, GridUnitType.Star);
            ((Label)FindName("FgControlSliderValueLabel")).SetValue(Grid.ColumnProperty,0);
            ((Label)FindName("FgControlSliderValueLabel")).Margin = new Thickness(0,0,-45,-10);
            ((Slider)FindName("FgControlSlider")).SetValue(Grid.ColumnProperty, 1);
            ((Slider) FindName("FgControlSlider")).TickPlacement = TickPlacement.TopLeft;
            ((Slider)FindName("FgControlSlider")).LayoutTransform = new RotateTransform(180);
            Grid.SetZIndex(((Slider) FindName("FgControlSlider")), 100);
            ((Label)FindName("FgControlSliderValueLabel")).LayoutTransform = new RotateTransform(-90);
            ((Label)FindName("FgControlSliderValueLabel")).Refresh();
        }

        public bool LTRFlag
        {
            get { return (bool)GetValue(LTRFlagProperty); }
            set { SetValue(LTRFlagProperty, value); }
        }
        #endregion


        public FGSliderControl()
        {
            InitializeComponent();
        }

        private void FgControlSlider_OnValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            this.SliderValue = e.NewValue;
        }
    }
}
