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
        }

        internal void simulate(string targetFile)
        {
            M.SimulateToFileOnly(Duration_, DispStep_, accuracy_, targetFile);
            outMan.PlayRequest(targetFile);
        }

        public void addActionPoint(uint v, double value1, double value2, double value3)
        {
            M.addActionPoint(v, value1, value2, value3);
        }

        public void addMaterialPoint(double inputCx, double inputCy, double inputCz, int v1, int v2, int v3, double mass, int v4)
        {
            M.addMaterialPoint(inputCx, inputCy, inputCz, (double)v1, (double)v2, (double)v3, mass, v4);
            sElem = M.getCoordinates().ToList<double>();
        }

        public void increment()
        {
            M.simpleIncrement(CompStep_);
       
                
            sElem = M.getCoordinates().ToList<double>();

            //   coordString = sceneElems_[0].ToString() +" "+ sceneElems_[1].ToString() + " " + sceneElems_[2].ToString();//test
        }
    }
}
