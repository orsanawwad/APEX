using System.Windows;

namespace AP2M3.Model.DialogService
{
    /// <summary>
    /// Required functions for implementing a dialog service for MVVM dialogs.
    /// </summary>
    public interface IDialogService
    {
        void Register<TViewModel, TView>() where TViewModel : IDialogRequestClose
                                           where TView : IDialog;

        bool? ShowDialog<TViewModel>(TViewModel viewModel) where TViewModel : IDialogRequestClose;

        void SetRootWindow(Window w);
    }
}