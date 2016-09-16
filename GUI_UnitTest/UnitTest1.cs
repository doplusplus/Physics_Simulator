using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using SimulationTool;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;

namespace GUI_UnitTest
{
    [TestClass]
    public class SimTestClass
    {
        [TestMethod]
        public void trivialTest()
        {
            double[] a = { 1, 2, 3 };
            List<double> result = new List<double>(a);

            OutputManager outMan = new OutputManager();
            SimManager simMan = new SimManager(outMan);

            simMan.addMaterialPoint(1, 2, 3, 0, 0, 0, 1, 0);
            simMan.CompStep_ = 12;
            simMan.increment();

            CollectionAssert.AreEqual(simMan.sceneElems_, result);
        }

        [TestMethod]
        public void unitDispTest()
        {
            double precision = 0.001;
            double[] a = { 1, 2, 21 };

            OutputManager outMan = new OutputManager();
            SimManager simMan = new SimManager(outMan);

            simMan.addMaterialPoint(0, 0, 0, 0, 0, 0, 1, 0);
            simMan.addActionPoint(0, 0.5, 1, 10.5);
            simMan.CompStep_ = 2;
            simMan.increment();

            Assert.IsTrue(simMan.sceneElems_[0] - a[0] < precision);
            Assert.IsTrue(simMan.sceneElems_[1] - a[1] < precision);
            Assert.IsTrue(simMan.sceneElems_[2] - a[2] < precision);
        }

        [TestMethod]
        public void EquivalenceTest()
        {
            double precision = 0.001;
            OutputManager outMan = new OutputManager();
            SimManager simMan = new SimManager(outMan);

            simMan.addMaterialPoint(0, 0, 0, 0, 0, 0, 1, 0);
            simMan.addActionPoint(0, 0.5, 1, 10.5);
            simMan.CompStep_ = 2;
            simMan.increment();
            //------------------------------------------------------
            OutputManager outMan2 = new OutputManager();
            SimManager simManBis = new SimManager(outMan);

            simManBis.addMaterialPoint(0, 0, 0, 0, 0, 0, 1, 0);
            simManBis.addActionPoint(0, 0.5, 1, 10.5);
            simManBis.CompStep_ = 1;
            simManBis.increment();
            simManBis.increment();

            Assert.IsTrue(simMan.sceneElems_[0] - simManBis.sceneElems_[0] < precision);
            Assert.IsTrue(simMan.sceneElems_[1] - simManBis.sceneElems_[1] < precision);
            Assert.IsTrue(simMan.sceneElems_[2] - simManBis.sceneElems_[2] < precision);
        }

        [TestMethod]
        public void RToutputTest()
        {
            OutputManager outMan = new OutputManager();
            SimManager simMan = new SimManager(outMan);
            OutputPanelVM outpan = new OutputPanelVM();

            outMan.link(new DisplayVM(), new FileModel(outMan), outpan, simMan);

            simMan.CompStep_ = 2;
            simMan.accuracyMode = false;

            outpan.fromSim = true;
            outpan.EnableLog = false;
            outpan.DisplayEnbld = true;
            outpan.DisplayStep = "1";

            simMan.addMaterialPoint(0, 0, 0, 0, 0, 0, 1, 0);
            simMan.addActionPoint(0, 0.5, 1, 10.5);

            outMan.launch();
            System.Threading.Thread.Sleep(5000);
            outMan.stopTimer();
            double t = 5;
            Assert.IsTrue(simMan.sceneElems_[0] < 0.5 * 0.5 * (t + simMan.CompStep_) * (t + simMan.CompStep_));
            Assert.IsTrue(simMan.sceneElems_[0] > 0.5 * 0.5 * (t - simMan.CompStep_) * (t - simMan.CompStep_));
        }

        [TestMethod]
        public void FileOutputTest()
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

            Assert.IsTrue(x - 0.5 * 0.5 * t * t < precision);
            Assert.IsTrue(y - 0.5 * t * t < precision);
            Assert.IsTrue(z - 0.5 * 10.5 * t * t < precision);
        }

        [TestMethod]
        public void noLogPrecModeTest()
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
            outpan.EnableLog = false;
            outpan.DisplayEnbld = true;
            outpan.DisplayStep = "1";
            outpan.TargetFile = "C:\\Users\\Doz\\Source\\Repos\\Physics_Simulator\\ConsoleEntryPoint\\UnitTestOutputFile.txt";

            if (!System.IO.File.Exists(outpan.TargetFile)) { System.IO.File.Create(outpan.TargetFile); }

            simMan.addMaterialPoint(0, 0, 0, 0, 0, 0, 1, 0);
            simMan.addActionPoint(0, 0.5, 1, 10.5);
            outMan.launch();

            System.IO.File.Delete(outpan.TargetFile);

            Assert.IsTrue(simMan.sceneElems_[0] - 0.5 * 0.5 * 25 < precision);
            Assert.IsTrue(simMan.sceneElems_[1] - 0.5 * 25 < precision);
            Assert.IsTrue(simMan.sceneElems_[2] - 0.5 * 10.5 * 25 < precision);
        }




    }
}
