using System;
using System.Collections.Generic;
using System.Windows;

namespace AP2M3.Model.DialogService
{
    /// <summary>
    /// Dialog service implementation used to register dialogs with its VMs
    /// and displays them on demand, this class is responsible in building the view and
    /// connecting the VMs to it, that way we prevent the ViewModel from instantiating
    /// dialogs on its own.
    ///
    /// This way we can use dialogs in MVVM way.
    /// </summary>
    public class DialogService : IDialogService
    {
        private readonly SetOnce<Window> owner = new SetOnce<Window>();
        public Window Owner
        {
            get { return owner; }
            set { owner.Value = value; }
        }

        public void SetRootWindow(Window w)
        {
            this.Owner = w;
        }

        private DialogService() { Mappings = new Dictionary<Type, Type>(); }
        private static IDialogService m_Instance = null;
        public static IDialogService Instance
        {
            get
            {
                if (m_Instance == null)
                {
                    m_Instance = new DialogService();
                }

                return m_Instance;
            }
        }


        public IDictionary<Type, Type> Mappings { get; }

        public void Register<TViewModel, TView>() where TViewModel : IDialogRequestClose
                                                  where TView : IDialog
        {
            if (Mappings.ContainsKey(typeof(TViewModel)))
            {
                throw new ArgumentException($"Type {typeof(TViewModel)} is already mapped to type {typeof(TView)}");
            }

            Mappings.Add(typeof(TViewModel), typeof(TView));
        }

        /// <summary>
        /// Build the corresponding view of the dialog and supply the ViewModel for it.
        /// </summary>
        /// <typeparam name="TViewModel">VM Interface</typeparam>
        /// <param name="viewModel">ViewModel related to View.</param>
        /// <returns></returns>
        public bool? ShowDialog<TViewModel>(TViewModel viewModel) where TViewModel : IDialogRequestClose
        {
            //Find the view related to ViewModel.
            Type viewType = Mappings[typeof(TViewModel)];

            //Create new instance of the dialog.
            IDialog dialog = (IDialog)Activator.CreateInstance(viewType);

            
            EventHandler<DialogCloseRequestedEventArgs> handler = null;

            handler = (sender, e) =>
            {
                viewModel.CloseRequested -= handler;

                if (e.DialogResult.HasValue)
                {
                    dialog.DialogResult = e.DialogResult;
                }
                else
                {
                    dialog.Close();
                }
            };

            //Add handler to VM.
            viewModel.CloseRequested += handler;

            //Set view's data context to VM
            dialog.DataContext = viewModel;
            //Set view's owner to main window (or anything else that is in focus)
            dialog.Owner = owner;

            return dialog.ShowDialog();
        }
    }
}