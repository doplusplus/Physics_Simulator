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
    class SimManager
    {
        ManagedModel M;
        OutputManager outMan;

        DispatcherTimer time = new DispatcherTimer();

    
        double accuracy_ = 0.00001;
    
        string testResult = string.Empty;

        public double CompStep_ { get; set; }
        public double DispStep_ { get; set; }
        public double Duration_ { get; set; }
        public bool SimMode { get; set; } //accuracy true, RT false
        public   List<double> sceneElems_ { get { return M.getCoordinates().ToList<double>(); } }

        public SimManager(OutputManager OutManager)
        {
            M = new ManagedModel();
            outMan = OutManager;

            //        time.Tick += new EventHandler(dispatcherTimer_Tick); //for the output manager?
            //        time.Tick += new EventHandler(checkStep);

        }

        internal void simulate(string targetFile)
        {
            M.SimulateToFileOnly(Duration_, DispStep_, accuracy_, targetFile);
            outMan.PlayRequest(targetFile);
        }


      //  public void sim2file(object obj) { M.SimulateToFileOnly(duration_, compStep_, accuracy_, target); }



        internal void addActionPoint(uint v, double value1, double value2, double value3)
        {
            M.addActionPoint(v, value1, value2, value3);
        }

        internal void addMaterialPoint(double inputCx, double inputCy, double inputCz, int v1, int v2, int v3, double mass, int v4)
        {
            M.addMaterialPoint(inputCx,inputCy,inputCz,(double)  v1, (double)v2, (double) v3, mass,  v4);
        }
    }
}
