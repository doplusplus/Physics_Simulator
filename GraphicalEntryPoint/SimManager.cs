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

namespace SimulationTool
{
    class SimManager
    {
        ManagedModel M;
        DisplayVM dVM;
        OutputPanelVM outPanel;
        DispatcherTimer time = new DispatcherTimer();
        double simTime = 0;
        double compStep_ = 0;
        double dispstep_ = 0;
        double duration_ = 0;
        string testResult = string.Empty;


        public SimManager(ManagedModel Mod, DisplayVM disp, OutputPanelVM outPanl)
        {
            M = Mod;
            dVM = disp;
            outPanel = outPanl;
            time.Tick += new EventHandler(dispatcherTimer_Tick);
            time.Tick += new EventHandler(checkStep);
        }


        public void startSimulation(double comStep, double dispStep, double duration)
        {
            simTime = dispStep;
            compStep_ = comStep;
            dispstep_ = dispStep;
            duration_ = duration;

            //          M.stepSim(dispStep);
            time.Interval = new TimeSpan(0, 0, 0, 0, (int)(dispStep * 1000));
            outPanel.SimTime = simTime.ToString(CultureInfo.InvariantCulture);
            time.Start();
        }

        private void dispatcherTimer_Tick(object sender, EventArgs e)
        {
           dVM.RefreshView();
          //  M.stepSim(dispstep_);
            //  testResult+= M.description();
            simTime += dispstep_;
            outPanel.SimTime = simTime.ToString(CultureInfo.InvariantCulture);
            if (simTime > duration_)
            {
                time.Stop();
            }
        }


        // RT SECTION
        public List<double> localCoord { get; set; }
        public double RTStep { get; set; }
        public double MinStep { get; set; }
        public double MaxStep { get; set; }
        public bool RTenabled { get; set; }

        public void RTSim(double duration, double timeAccuracy)
        {
            MinStep = MaxStep = RTStep = duration * 0.001;
            //start multithreading here
            time.Interval = new TimeSpan(0, 0, 0, 0, (int)(timeAccuracy * 1000));
            time.Start();
            while (duration > 0)
            {
                M.directIncrement(RTStep);
                localCoord.AddRange(M.getCoordinates());
                duration -= RTStep;
            }
        }

        private void checkStep(object sender, EventArgs e)
        {
            if (RTenabled)
            {
                if (localCoord.Count < 2) { MinStep = RTStep; RTStep = Math.Max(RTStep * 2, (RTStep + MaxStep) * 0.5); return; }
                if (localCoord.Count > 10) { MaxStep = RTStep; RTStep = Math.Min(RTStep * 0.5, (RTStep + MinStep) * 0.5); return; }
            }
        }

        private void fetchData(object sender, EventArgs e)
        {


        }


    }
}
