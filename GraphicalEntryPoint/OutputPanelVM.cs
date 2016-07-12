using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ManagedClasses;
using System.Globalization;
using System.ComponentModel;

namespace SimulationTool
{
    class OutputPanelVM : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        public OutputPanelVM()
        { }


        private double simTime_ = -1;
        public string SimTime
        {
            get
            {
                if (simTime_ >= 0) { return simTime_.ToString(); }
                else { return "time in s"; }
            }
            set { simTime_ = Double.Parse(value, CultureInfo.InvariantCulture); Notify("SimTime");  }
        }

        public double Time { set { simTime_ = value; Notify(" SimTime"); } }

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

        void Notify(string propName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propName));
            }
        }

    }
}
