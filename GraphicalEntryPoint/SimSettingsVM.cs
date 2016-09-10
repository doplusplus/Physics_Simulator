using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace SimulationTool
{
    class SimSettingsVM : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        private double duration_ = -1;
        private double computationalStep = -1;
        private string targetFile_ = "file path";
        private bool fileAllowed_ = true;

        private ICommand allowLog_;
        private ICommand disableLog_;

        public ICommand precisionMode { get; set; }
        public ICommand RTMode { get; set; }

        SimManager SMan;

        public SimSettingsVM(SimManager SManager_)
        {
            AllowLog = new RelayCommand(new Action<object>(enableLog));
            ForbidLog = new RelayCommand(new Action<object>(forbidLog));

            precisionMode = new RelayCommand(new Action<object>(setToPrecision));
            RTMode = new RelayCommand(new Action<object>(setToRT));
            SMan = SManager_;
        }

        private void setToRT(object obj)
        {
            SMan.SimMode = false;
        }

        private void setToPrecision(object obj)
        {
            SMan.SimMode = true;
        }

        public string Duration
        {
            get
            {
                if (duration_ > 0) { return duration_.ToString(CultureInfo.InvariantCulture); }
                else { return "duration in s"; }
            }
            set
            {
                duration_ = Double.Parse(value, System.Globalization.NumberStyles.AllowDecimalPoint, CultureInfo.InvariantCulture);
                SMan.Duration_ = duration_;
                Notify("Duration");
            }
        }

        public string ComputStep
        {
            get
            {
                if (computationalStep > 0) { return computationalStep.ToString(CultureInfo.InvariantCulture); }
                else { return "comp. step in s"; }
            }
            set
            {
                double d;
                bool b = Double.TryParse(value, System.Globalization.NumberStyles.AllowDecimalPoint, CultureInfo.InvariantCulture, out d);
                computationalStep = b && d > 0 ? d : -1;
                SMan.CompStep_ = computationalStep;
                Notify("ComputStep");
            }
        }

        public string TargetFile
        {
            get { return targetFile_; }
            set
            {
                targetFile_ = value;
                Notify("TargetFile");
            }
        }

        public bool FileAllowed
        {
            get { return fileAllowed_; }
            set
            {
                fileAllowed_ = value;
                Notify("FileAllowed");
            }
        }

        public ICommand AllowLog
        {
            get { return allowLog_; }
            set { allowLog_ = value; }
        }

        public void enableLog(object obj)
        {
            FileAllowed = true;
        }

        public ICommand ForbidLog
        {
            get { return disableLog_; }
            set { disableLog_ = value; }
        }

        public void forbidLog(object obj)
        {
            FileAllowed = false;
        }


        void Notify(string propName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propName));
            }
        }


    }
}
