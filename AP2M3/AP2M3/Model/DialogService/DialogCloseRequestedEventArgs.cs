using System;

namespace AP2M3.Model.DialogService
{
    /// <summary>
    /// Event used to close the dialog.
    /// </summary>
    public class DialogCloseRequestedEventArgs : System.EventArgs
    {
        public DialogCloseRequestedEventArgs(bool? dialogResult)
        {
            DialogResult = dialogResult;
        }

        public bool? DialogResult { get; }
    }
}