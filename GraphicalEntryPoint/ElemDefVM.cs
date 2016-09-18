using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using ManagedClasses;
using System.Windows.Input;

namespace SimulationTool
{
    class ElemDefVM : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        private ICommand mPointCreation;
        private ICommand actionAdd;

        private double? mass;
        private double? InputCx, InputCy, InputCz;
        private double? InputFx, InputFy, InputFz;
        private uint selected = 0; //element 0 is selected as 1

        private SimManager simMgr;
        private OutputManager outMan;

       public ElemDefVM(SimManager SManager_,OutputManager outMngr)
        {
            mass = InputCx = InputCy = InputCz = InputFx = InputFy = InputFz = null;
            simMgr = SManager_;
            outMan = outMngr;

            MPointCreation = new RelayCommand(new Action<object>(addMPoint));
            ActionAdd = new RelayCommand(new Action<object>(addAction));
        }

        void Notify(string propName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propName));
            }
        }

        public string massInput
        {
            get { return (mass != null) ? mass.ToString() : "mass"; }
            set
            {
                double d = 0;
                bool b = Double.TryParse(value, NumberStyles.AllowDecimalPoint, CultureInfo.InvariantCulture, out d);
                if (d >= 0) { mass = d; }
                else { MessageBox.Show("We don't deal with negative masses"); }
                Notify("massInput");
            }
        }

        public string Xinput
        {
            get { return (InputCx != null) ? InputCx.ToString() : "X"; }
            set
            {
                double result = 0;
                bool b = Double.TryParse(value, NumberStyles.Any, CultureInfo.InvariantCulture, out result);
                InputCx = b ? (double?)result : null;
                Notify("Xinput");              
            }
        }

        public string Yinput
        {
            get { return (InputCy != null) ? InputCy.ToString() : "Y"; }
            set
            {
                InputCy = Double.Parse(value, NumberStyles.Any, CultureInfo.InvariantCulture);
                Notify("Yinput");
            }
        }

        public string Zinput
        {
            get { return (InputCz != null) ? InputCz.ToString() : "Z"; }
            set
            {
                InputCz = Double.Parse(value, NumberStyles.Any, CultureInfo.InvariantCulture);
                Notify("Zinput");
            }
        }

        public string FXinput
        {
            get { return (InputFx != null) ? InputFx.ToString() : "X"; }
            set
            {
                double result = 0;
                bool b = Double.TryParse(value, NumberStyles.Any, CultureInfo.InvariantCulture, out result);
                InputFx = b ? (double?)result : null;
                Notify("FXinput");
            }
        }

        public string FYinput
        {
            get { return (InputFy != null) ? InputFy.ToString() : "Y"; }
            set
            {
                var fmt = new NumberFormatInfo();
                fmt.NegativeSign = "−";
                
                InputFy = Double.Parse(value, NumberStyles.Any, CultureInfo.InvariantCulture);
                Notify("FYinput");
            }
        }

        public string FZinput
        {
            get { return (InputFz != null) ? InputFz.ToString() : "Z"; }
            set
            {
                InputFz = Double.Parse(value, NumberStyles.Any, CultureInfo.InvariantCulture);
                Notify("FZinput");
            }
        }

        public string SelectedItem
        {
            get { return selected != 0 ? selected.ToString() : "N/A"; }
            set
            {
                selected = UInt32.Parse(value, NumberStyles.Integer, CultureInfo.InvariantCulture);
                Notify("SelectedItem");
            }
        }


        public ICommand MPointCreation
        {
            get { return mPointCreation; }
            set { mPointCreation = value; }
        }

        public ICommand ActionAdd
        {
            get { return actionAdd; }
            set { actionAdd = value; }
        }


        public void addAction(object obj)
        {
            bool create = (InputFx != null) && (InputFy != null) && (InputFz != null);
            if (selected > 0 && create)
            {
                if (InputFx == 0 && InputFy == 0 && InputFz == 0) { MessageBox.Show("Null actions are useless, ignoring it"); }
                else
                {
                    simMgr.addActionPoint(selected - 1, InputFx.Value, InputFy.Value, InputFz.Value);
                }
            }
            else { MessageBox.Show("invalid input or no element created"); }
        }


        public void addMPoint(object obj)
        {
            //MessageBox.Show("Trying to create a material Point");

            string message = String.Empty;
            string massMessage = String.Empty;
            string massRejectMessage = String.Empty;
            string positionMessage = String.Empty;
            string positionRejectMessage = String.Empty;

            bool creation = true;

            //Mass checking
            if (mass != null && mass > 0)
            { massMessage += "mass: " + mass.ToString(); }
            else
            {
                massRejectMessage += "- Not going anywhere without a positive mass" + Environment.NewLine;
                creation = false;
            }

            //Position Checking

            //Cx

            if (Xinput.Equals("X") && creation)
            {
                Xinput = "0";
                positionMessage += " Cx = 0 ";
            }
            else
            {
                if (InputCx == null)
                {
                    positionRejectMessage += "- Numerical value required for Cx" + Environment.NewLine;
                    creation = false;
                }
                else { positionMessage = (creation) ? positionMessage + " Cx = " + InputCx.ToString() : positionMessage; }
            }

            //Cy
            if (Yinput.Equals("Y") && creation)
            { Yinput = "0"; positionMessage += " Cy = 0 "; }
            else
            {
                if (InputCy == null)
                {
                    positionRejectMessage += "- Numerical value required for Cy" + Environment.NewLine;
                    creation = false;
                }
                else { positionMessage = (creation) ? positionMessage + " Cy = " + InputCy.ToString() : positionMessage; }
            }

            //Cz
            if (Zinput.Equals("Z") && creation)
            { Zinput = "0"; positionMessage += " Cz = 0 "; }
            else
            {
                if (InputCz == null)
                {
                    positionRejectMessage += "- Numerical value required for Cz" + Environment.NewLine;
                    creation = false;
                }
                else { positionMessage = (creation) ? positionMessage + " Cz = " + InputCz.ToString() : positionMessage; }
            }

            if (creation)
            {
                message =
                    massMessage + Environment.NewLine +
                    "Position of the center of mass: " + Environment.NewLine +
                    positionMessage;
                MessageBox.Show(message, "Confirmation");
                simMgr.addMaterialPoint((double)InputCx, (double)InputCy, (double)InputCz, 0, 0, 0, (double)mass, 0);
                selected++;
                Notify("SelectedItem");
                outMan.displayElements();
            }
            else
            {
                message =
                    "The Material Point will not be created:" + Environment.NewLine +
                    massRejectMessage + positionRejectMessage;
                MessageBox.Show(message, "Rejection");
            }
        }









    }
}
