using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SimulationTool;
using System.Timers;

namespace ConsoleApplication1
{
    class Program
    {

        static void Main(string[] args)
        {
            OutputManager outMan = new OutputManager();
            SimManager simMan = new SimManager(outMan);
            OutputPanelVM outpan = new OutputPanelVM();

            outMan.link(new DisplayVM(), new FileModel(outMan), outpan, simMan);
            double precision = 0.0001;

            simMan.CompStep_ = 2;
            simMan.Duration_ = 5;
            simMan.accuracyMode = true;

            outpan.fromSim = true;
            outpan.EnableLog = true;
            outpan.DisplayEnbld = false;
            outpan.DisplayStep = "1";
            outpan.TargetFile = "C:\\Users\\Doz\\Source\\Repos\\Physics_Simulator\\ConsoleEntryPoint\\UnitTestOutputFile.txt";

            bool temp = false;
            if (!System.IO.File.Exists(outpan.TargetFile)) { temp = true; System.IO.File.Create(outpan.TargetFile); }

            simMan.addMaterialPoint(0, 0, 0, 0, 0, 0, 1, 0);
            simMan.addActionPoint(0, 0.5, 1, 10.5);
            outMan.launch();
        
            string content = System.IO.File.ReadLines(outpan.TargetFile).Last();
            var sp = content.Split();
            double t = Double.Parse(sp[0]);
            double x = Double.Parse(sp[2]);
            double y = Double.Parse(sp[3]);
            double z = Double.Parse(sp[4]);
            if (temp == true) { System.IO.File.Delete(outpan.TargetFile); }
        }


    }
}
