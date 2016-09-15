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
            SimManager S = new SimManager(new OutputManager());
            S.accuracyMode = false;
            S.CompStep_ = 0.5;
            S.DispStep_ = 0.3;
            S.Duration_ = 12;




            S.addMaterialPoint(0, 0, 0, 0, 0, 0, 1, 0);
            S.addActionPoint(0, 1, 1, 1);
            //-----------------------------------------------------------------



            //-----------------------------------------------------------------

            S.increment();
            foreach (var c in S.sceneElems_)
            { Console.Write(c.ToString() + " "); }
            Console.WriteLine();

            S.increment();
            foreach (var c in S.sceneElems_)
            { Console.Write(c.ToString() + " "); }
            Console.WriteLine();

            S.increment();
            foreach (var c in S.sceneElems_)
            { Console.Write(c.ToString() + " "); }
            Console.WriteLine();

            S.increment();
            foreach (var c in S.sceneElems_)
            { Console.Write(c.ToString() + " "); }
            Console.WriteLine();


            Console.ReadKey();
        }

        private static void incrmnt(object sender, ElapsedEventArgs e)
        {

        }
    }
}
