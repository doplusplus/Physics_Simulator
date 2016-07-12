using System;
using System.Windows;
using System.Globalization;
using System.ComponentModel;
using System.Windows.Input;

namespace SimulationTool
{
    public class MainWindowModel : INotifyPropertyChanged
    {
        private double? mass;
        private double? InputCx, InputCy, InputCz;
        private ICommand mPointCreation;


        public event PropertyChangedEventHandler PropertyChanged;
        void Notify(string propName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propName));
            }
        }



        public MainWindowModel()
        {
            mass = InputCx = InputCy = InputCz = null;
            MPointCreation = new RelayCommand(new Action<object>(addMPoint));
        }

        public string massInput
        {
            get { return (mass != null) ? mass.ToString() : "enter mass"; }
            set
            {
                double d = 0;
                bool b= Double.TryParse(value, System.Globalization.NumberStyles.AllowDecimalPoint, CultureInfo.InvariantCulture,out d);
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
                bool b = Double.TryParse(value, System.Globalization.NumberStyles.AllowDecimalPoint, CultureInfo.InvariantCulture, out result);
                InputCx = b ? (double?)result : null;
                Notify("Xinput");
            }
        }
        public string Yinput
        {
            get { return (InputCy != null) ? InputCy.ToString() : "Y"; }
            set
            {
                InputCy = Double.Parse(value, System.Globalization.NumberStyles.AllowDecimalPoint, CultureInfo.InvariantCulture);
                Notify("Yinput");
            }
        }
        public string Zinput
        {
            get { return (InputCz != null) ? InputCz.ToString() : "Z"; }
            set
            {
                InputCz = Double.Parse(value, System.Globalization.NumberStyles.AllowDecimalPoint, CultureInfo.InvariantCulture);
                Notify("Zinput");
            }
        }


        public ICommand MPointCreation
        {
            get { return mPointCreation; }
            set { mPointCreation = value; }
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
                massRejectMessage += "- Not going anywhere without a positive mass"+Environment.NewLine;
                creation = false;
            }

            //Position Checking

            //Cx
            if (InputCx == null)
            {
                positionRejectMessage += "- Numerical value required for Cx" + Environment.NewLine;
                creation = false;
            }
            else
            {
                if (Xinput.Equals("x")) { Xinput = "0"; message += " Cx = 0 "; }
                else { message += " Cx = " + InputCx.ToString(); }
            }

            //Cy
            if (InputCy == null)
            {
                positionRejectMessage += "- Numerical value required for Cy" + Environment.NewLine;
                creation = false;
            }
            else
            {
                if (Yinput.Equals("y")) { Yinput = "0"; positionMessage += " Cy = 0 "; }
                else { positionMessage += " Cy = " + InputCy.ToString(); }
            }

            //Cz
            if (InputCz == null)
            {
                positionRejectMessage += "- Numerical value required for Cz" + Environment.NewLine;
                creation = false;
            }
            else
            {
                if (Zinput.Equals("z")) { Zinput = "0"; positionMessage += " Cz = 0 "; }
                else { positionMessage += " Cz = " + InputCz.ToString(); }
            }

            if (creation)
            {
                message =
                    massMessage + Environment.NewLine +
                    "Position of the center of mass: " + Environment.NewLine +
                    positionMessage;
                MessageBox.Show(message,"Confirmation");
            }

            else
            {
                message =
                    "The Material Point will not be created:"+ Environment.NewLine+
                    massRejectMessage + positionRejectMessage;
                MessageBox.Show(message, "Rejection");
            }

           
        }


    }
}
