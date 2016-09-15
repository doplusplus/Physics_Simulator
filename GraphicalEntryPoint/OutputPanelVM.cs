using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ManagedClasses;
using System.Globalization;
using System.ComponentModel;
using System.Windows.Input;

namespace SimulationTool
{
    public class OutputPanelVM : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        public OutputPanelVM()
        {
            ToggleSource = new RelayCommand(new Action<object>(toggleSource_));
            EnableLog = true;
            DisplayEnbld = true;
            fromSim = true;
            srcColor = "Gray";
        }

        public bool DisplayEnbld { get; set; }

        bool enbleLog = true;
        public bool EnableLog { get { return enbleLog; } set { enbleLog = value; } }
        public bool DisableLog { get { return !enbleLog; } set { enbleLog = !value; } }

        public bool fromSim { get; set; }
        public string srcColor { get; set; }

        public ICommand ToggleSource { get; set; }
        private void toggleSource_(object obj)
        {
            fromSim = !fromSim;
            if (fromSim)
            { srcColor = "Gray"; Notify("srcColor"); }
            else
            { srcColor = "Orange"; Notify("srcColor"); }
        }

        string targFile = "C:\\Users\\Doz\\Source\\Repos\\Physics_Simulator\\ConsoleEntryPoint\\IOTestFile.txt";
        public string TargetFile { get { return targFile; } set { targFile = value; Notify("TargetFile"); } }

        private double simTime_ = -1;
        public string SimTime
        {
            get
            {
                if (simTime_ >= 0) { return simTime_.ToString(); }
                else { return "time in s"; }
            }
            set { simTime_ = Double.Parse(value, CultureInfo.InvariantCulture); Notify("SimTime"); }
        }

        public double Time
        {
            set { simTime_ = value; Notify("SimTime"); }
            get { return simTime_; }
        }

        public void resetTimeTracker() { Time = 0; }

        public double endTime { get; set; }

        private double dispStep = -1;
        public string DisplayStep
        {
            get
            {
                if (dispStep > 0) { return dispStep.ToString(CultureInfo.InvariantCulture); }
                else { return "disp. step in s"; }
            }
            set
            {
                double d;
                bool b = Double.TryParse(value, System.Globalization.NumberStyles.AllowDecimalPoint, CultureInfo.InvariantCulture, out d);
                dispStep = b && d > 0 ? d : -1;
                Notify("DisplayStep");
            }
        }

        public void increment() { Time += dispStep; }

        void Notify(string propName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propName));
            }
        }

    }
}
