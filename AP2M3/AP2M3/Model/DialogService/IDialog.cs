using System.Windows;

namespace AP2M3.Model.DialogService
{
    /// <summary>
    /// IDialog interface used to provide crucial details for MVVM Dialogs.
    /// </summary>
    public interface IDialog
    {
        object DataContext { get; set; }
        bool? DialogResult { get; set; }
        Window Owner { get; set; }
        void Close();
        bool? ShowDialog();
    }
}