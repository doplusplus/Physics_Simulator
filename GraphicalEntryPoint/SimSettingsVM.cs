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

        bool precisionMde = true;
        public bool PrecisionMode
        {
            get { return precisionMde; }
            set { precisionMde = value;/* Notify("PrecisionMode"); Notify("RTMode")*/; }
        }
        public bool RTMode
        {
            get { return !precisionMde; }
            set { precisionMde = !value;/* Notify("PrecisionMode"); Notify("RTMode")*/; }
        }

        SimManager SMan;

        public SimSettingsVM(SimManager SManager_) { SMan = SManager_; }

        private void setToRT(object obj) { SMan.accuracyMode = false; }

        private void setToPrecision(object obj) { SMan.accuracyMode = true; }

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

        void Notify(string propName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propName));
            }
        }

    }
}
