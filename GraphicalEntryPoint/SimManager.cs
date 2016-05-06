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
        }

        public void startSimulation(double comStep, double dispStep, double duration)
        {
            simTime = dispStep;
            compStep_ = comStep;
            dispstep_ = dispStep;
            duration_ = duration;

            M.stepSim(comStep, dispStep);            
            time.Interval = new TimeSpan(0,0,0,0,(int) (dispStep *1000));
            outPanel.SimTime = simTime.ToString(CultureInfo.InvariantCulture);
            time.Start();
        }

        private void dispatcherTimer_Tick(object sender, EventArgs e)
        {
            dVM.RefreshView();
            M.stepSim(compStep_, dispstep_);
            testResult+= M.description();
            simTime += dispstep_;
            outPanel.SimTime = simTime.ToString(CultureInfo.InvariantCulture);
            if (simTime > duration_)
            { time.Stop();
            }
        }



    }
}
