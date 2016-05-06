using System;
using System.Windows;
using System.Globalization;
using System.ComponentModel;
using System.Windows.Input;
using ManagedClasses;

namespace SimulationTool
{
    public class MainWindowModel : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        private ManagedModel M;

        void Notify(string propName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propName));
            }
        }

        public MainWindowModel(ManagedModel Mod)
        {
            M = Mod;      
        }

    }
}
