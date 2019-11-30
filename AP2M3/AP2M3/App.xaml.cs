using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using AP2M3.Model.DialogService;
using AP2M3.ViewModels.Windows;
using AP2M3.Views;

namespace AP2M3
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        /// <summary>
        /// Setup dialog service on startup and include main window as main owner
        /// and register required dialogs.
        /// </summary>
        /// <param name="e"></param>
        protected override void OnStartup(StartupEventArgs e)
        {
            IDialogService dialogService = DialogService.Instance;
            dialogService.SetRootWindow(this.MainWindow);
            dialogService.Register<SettingsWindowViewModel, SettingsDialogWindow>();
        }
    }
}
