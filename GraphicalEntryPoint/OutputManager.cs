using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
//using System.Threading;
using System.Threading.Tasks;
using System.Timers;
using System.Windows.Input;
using System.Windows.Threading;

namespace SimulationTool
{
    public class OutputManager
    {
        DisplayVM disVM;
        OutputPanelVM outPan;
        FileModel fileVm_;
        SimManager simMan;

        Timer RTTimer = new Timer();

        private Object thisLock = new Object();


        public OutputManager()
        { }

        public void link(DisplayVM dispVM, FileModel FVM, OutputPanelVM outPanel, SimManager sM)
        {
            disVM = dispVM;
            outPan = outPanel;
            fileVm_ = FVM;
            simMan = sM;

            RTTimer.Elapsed += IncrementRT;
            RTTimer.AutoReset = true;
        }

        public string SimTime { get { return outPan.SimTime; } }

        internal void displayElements()
        {
            if (outPan.fromSim)
            {
                disVM.displayElements(simMan.sceneElems_);
            }
        }

        public void launch()
        {
            if (!simMan.accuracyMode && outPan.fromSim && outPan.DisplayEnbld)
            {
                simMan.computeFieldForces();
                LaunchRTSim();
            }
            else
            {
                bool b = false;
                string tFile = outPan.TargetFile;
                if (outPan.fromSim)
                {
                    simMan.computeFieldForces();
                    b = !outPan.EnableLog;
                    if (b) { tFile = Path.GetTempFileName(); }
                    simMan.DispStep_ = Double.Parse(outPan.DisplayStep, NumberStyles.AllowDecimalPoint,
                        CultureInfo.InvariantCulture);
                    simMan.simulate(tFile);
                }
                PlayRequest(tFile);
                if (b) { File.Delete(tFile); }
            }
        }

        internal void PlayRequest(string target)
        {
            if (outPan.DisplayEnbld) { play(target); }
        }

        private void play(string target)
        {
            fileVm_.select(target);
            fileVm_.FilterFile(Double.Parse(outPan.DisplayStep, NumberStyles.AllowDecimalPoint,
                CultureInfo.InvariantCulture));
        }

        private void LaunchRTSim()
        {
            setRTTimer(simMan.CompStep_);
            lock (thisLock)
            {
                simMan.increment();
            }
            RTTimer.Start();
        }

        private void setRTTimer(double compStep_)
        {
            RTTimer.Interval = compStep_ * 1000;
        }

        private void IncrementRT(object sender, EventArgs e)
        {
            simMan.increment();
        }

        internal void startTimer()
        {
            RTTimer.Start();
        }

        public void stopTimer()
        {
            RTTimer.Stop();
        }
    }

}

