using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using System.Windows.Media.Media3D;
using System.Globalization;
using System.ComponentModel;
using System.Windows;

namespace SimulationTool
{
    class EnvironmentDefVM : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        SimManager SMan;
        // Gravity Field Properties-------------------------------------------------------------------------------------
        Vector3D pushedGravAction = new Vector3D(0, 0, 0);

        bool gField = false;
        public bool gravityOn
        {
            get { return gField; }
            set { gField = value; }
        }
        public bool gravityOff
        {
            get { return !gField; }
            set { gField = !value; }
        }


        double? gX;
        double? gY;
        double? gZ;

        public string Xgravity
        {
            get
            {
                return (gX.HasValue) ? gX.Value.ToString() : "X";
            }
            set { gX = double.Parse(value, NumberStyles.Any, CultureInfo.InvariantCulture); Notify("gravityIntensity"); }
        }
        public string Ygravity
        {
            get
            {
                return (gY.HasValue) ? gY.Value.ToString() : "Y";
            }
            set { gY = double.Parse(value, NumberStyles.Any, CultureInfo.InvariantCulture); Notify("gravityIntensity"); }
        }
        public string Zgravity
        {
            get
            {
                return (gZ.HasValue) ? gZ.Value.ToString() : "Z";
            }
            set { gZ = double.Parse(value, NumberStyles.Any, CultureInfo.InvariantCulture); Notify("gravityIntensity"); }
        }

        //  double? gIntensity;
        public string gravityIntensity
        {
            get
            {
                return (gX.HasValue && gY.HasValue && gZ.HasValue) ? Math.Sqrt(gX.Value * gX.Value + gY.Value * gY.Value + gZ.Value * gZ.Value).ToString() : "Intensity";
            }
            // set { gIntensity = double.Parse(value, NumberStyles.Any, CultureInfo.InvariantCulture); }
        }

        // ElectricField Properties-------------------------------------------------------------------------------------
        Vector3D pushedElecAction = new Vector3D(0, 0, 0);

        bool elecField = false;
        public bool elecOn
        {
            get { return elecField; }
            set { elecField = value; }
        }
        public bool elecOff
        {
            get { return !elecField; }
            set { elecField = !value; }
        }

        double? eX;
        double? eY;
        double? eZ;

        public string Xelec
        {
            get
            {
                return (eX.HasValue) ? eX.Value.ToString() : "X";
            }
            set { eX = double.Parse(value, NumberStyles.Any, CultureInfo.InvariantCulture); Notify("elecIntensity"); }
        }
        public string Yelec
        {
            get
            {
                return (eY.HasValue) ? eY.Value.ToString() : "Y";
            }
            set { eY = double.Parse(value, NumberStyles.Any, CultureInfo.InvariantCulture); Notify("elecIntensity"); }
        }
        public string Zelec
        {
            get
            {
                return (eZ.HasValue) ? eZ.Value.ToString() : "Z";
            }
            set { eZ = double.Parse(value, NumberStyles.Any, CultureInfo.InvariantCulture); Notify("elecIntensity"); }
        }

        //        double? eIntensity;
        public string elecIntensity
        {
            get
            {
                return (eX.HasValue && eY.HasValue && eZ.HasValue) ? Math.Sqrt(eX.Value * eX.Value + eY.Value * eY.Value + eZ.Value * eZ.Value).ToString() : "Intensity";
                // return (eIntensity.HasValue) ? eIntensity.Value.ToString() : "Intensity";
            }
            //            set { eIntensity = double.Parse(value, NumberStyles.Any, CultureInfo.InvariantCulture); }
        }




        public ICommand UpdateEnvironment { get; set; }

        public EnvironmentDefVM(SimManager SManager_)
        {
            SMan = SManager_;
            UpdateEnvironment = new RelayCommand(new Action<object>(setEnvironement));
        }

        Vector3D Regularize(double x, double y, double z, double intensity)
        {
            double sqNorm = x * x + y * y + z * z;
            Vector3D res = new Vector3D((intensity * x) / Math.Sqrt(sqNorm), (intensity * y) / Math.Sqrt(sqNorm), (intensity * z) / Math.Sqrt(sqNorm));
            return res;
        }

        private void setEnvironement(object obj)
        {
            if (gField)
            {
                if (!(gX.HasValue && gY.HasValue && gZ.HasValue))
                    { MessageBox.Show("Please set all the gravity parameters or disable it"); return; }
                SMan.GravAction = new Vector3D( gX.Value, gY.Value, gZ.Value);
            }
            if (elecField)
            {
                if (!(eX.HasValue && eY.HasValue && eZ.HasValue))
                    { MessageBox.Show("Please set all the gravity parameters or disable it"); return; }
                SMan.ElecAction = new Vector3D(eX.Value, eY.Value, eZ.Value);
            }          
        }





            /*   private void setEnvironement(object obj)
               {
                   double x = 0, y = 0, z = 0;
                   if (gField)
                   {
                       if (!(gX.HasValue && gY.HasValue && gZ.HasValue 
                           /*&& gIntensity.HasValue*/
            //)) { MessageBox.Show("Please set all the gravity parameters or disable it"); return; }
            //Vector3D V = Regularize(gX, gY, gZ, gIntensity);
            /*           x += gX.Value - pushedGravAction.X;
                       y += gY.Value - pushedGravAction.Y;
                       z += gZ.Value - pushedGravAction.Z;
                       pushedGravAction.X = gX.Value;
                       pushedGravAction.Y = gY.Value;
                       pushedGravAction.Z = gZ.Value;
                   }

                   if (elecField)
                   {
                       if (!(eX.HasValue && eY.HasValue && eZ.HasValue /*&& gIntensity.HasValue*/
            /*         )) { MessageBox.Show("Please set all the gravity parameters or disable it"); return; }
                     x += eX.Value - pushedElecAction.X;
                     y += eY.Value - pushedElecAction.Y;
                     z += eZ.Value - pushedElecAction.Z;
                     pushedElecAction.X = eX.Value;
                     pushedElecAction.Y = eY.Value;
                     pushedElecAction.Z = eZ.Value;
                 }
                 for (uint i = 0; i < SMan.card; i++)
                 {
                     SMan.addActionPoint(i, x, y, z);
                 }
             }
         */

            void Notify(string propName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propName));
            }
        }

    }


}