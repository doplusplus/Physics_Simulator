using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ManagedClasses;
using System.Timers;
using System.Diagnostics;
using System.Globalization;
using System.Windows.Threading;
using System.Windows.Input;
using System.Windows.Media.Media3D;

namespace SimulationTool
{
    public class SimManager
    {
        ManagedModel M = new ManagedModel();


        OutputManager outMan;

        double accuracy_ = 0.00001;
        string testResult = string.Empty;

        public double CompStep_ { get; set; }
        public double DispStep_ { get; set; }
        public double Duration_ { get; set; }
        public bool accuracyMode { get; set; } //accuracy true, RT false

        Dictionary<int, Tuple<double, Point3D, Vector3D>> backUp = new Dictionary<int, Tuple<double, Point3D, Vector3D>>(); //element -(mass - coord - force)
        public int card { get; set; }

        internal void clearAll()
        {
            ManagedModel reloadModel = new ManagedModel();
            uint i = 0;
            foreach (var elem in backUp)
            {
                reloadModel.addMaterialPoint(elem.Value.Item2.X, elem.Value.Item2.Y, elem.Value.Item2.Z, 0, 0, 0, elem.Value.Item1, 1);
                reloadModel.addActionPoint(i, elem.Value.Item3.X, elem.Value.Item3.Y, elem.Value.Item3.Z);
                i++;
            }
            M = reloadModel;
        }

        //   public string coordString { get; set; }
        List<double> sElem = new List<double>();
        public List<double> sceneElems_
        {
            get { return sElem; }
        }

        public string SimCoordList { get { return sceneElems_.ToString(); } }

        public SimManager(OutputManager OutManager)
        {
            outMan = OutManager;
            accuracyMode = true;
            sElem = M.getCoordinates().ToList<double>();
            card = 0;
        }

        internal void simulate(string targetFile)
        {
            M.SimulateToFileOnly(Duration_, DispStep_, accuracy_, targetFile);
        }

        public void addActionPoint(uint v, double value1, double value2, double value3)
        {
            M.addActionPoint(v, value1, value2, value3);

            //Backup part
            Vector3D NewForce = backUp[Convert.ToInt32(v)].Item3;
            NewForce.X += value1;
            NewForce.Y += value2;
            NewForce.Z += value3;

            backUp[Convert.ToInt32(v)] = new Tuple<double, Point3D, Vector3D>
                (backUp[Convert.ToInt32(v)].Item1, backUp[Convert.ToInt32(v)].Item2, NewForce);
        }

        public void addMaterialPoint(double inputCx, double inputCy, double inputCz, double no1, double no2, double no3, double mass, double no4)
        {
            M.addMaterialPoint(inputCx, inputCy, inputCz, no1, no2, no3, mass, no4);
            sElem = M.getCoordinates().ToList<double>();
            backUp.Add(card, new Tuple<double, Point3D, Vector3D>(mass, new Point3D(inputCx, inputCy, inputCz), new Vector3D(0, 0, 0)));
            card++;
        }

        public void increment()
        {
            M.simpleIncrement(CompStep_);
            sElem = M.getCoordinates().ToList<double>();
        }
    }
}
