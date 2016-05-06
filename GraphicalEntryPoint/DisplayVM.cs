﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ManagedClasses;
using System.Windows.Shapes;
using System.Collections.ObjectModel;
using System.Windows;
using System.Windows.Data;
using System.Globalization;
using System.Collections.Specialized;

namespace SimulationTool
{
    public class circle : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        public circle(double x_, double y_, double z_, double radius_)
        {
            Xcoord = x_;
            Ycoord = y_;
            Zcoord = z_;
            Radius = radius_;
        }

        public double Xcoord { get; set; }
        public double Ycoord { get; set; }
        public double Zcoord { get; set; }
        public double Radius { get; set; }


        public void Notify(string propName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propName));
            }
        }
    }


    public class DisplayVM : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        public event NotifyCollectionChangedEventHandler CollectionChanged;

        private const int radius = 10;

        private ManagedModel M = null;
        private ObservableCollection<circle> Items = new ObservableCollection<circle>();
        public ObservableCollection<circle> circleItems { get { return Items; } set { Items = value; } }

        public DisplayVM(ManagedModel Mod)
        {
            M = Mod;
        }

        private double dX;
        private double dY;
        private double CX;
        private double CY;

        public double DisplayWidth { get; set; }
        public double XUnit { get { return dX; } set { dX = value; Notify("XUnit"); } }
        public double CenterX { get { return CX; } set {CX=value; Notify("CenterX"); } }

        public double DisplayHeight { get; set; }
        public double YUnit { get { return dY; } set { dY = value; Notify("YUnit"); } }
        public double CenterY { get { return CY; } set { CY = value; Notify("CenterY"); } }

        public void displayElements()
        {
            List<double> a = M.getCoordinates().ToList<double>();
            for (int i = 0; i < a.Count - 2; i = i + 3)
            {
                Items.Add(new circle(a[i] + DisplayWidth / 2 - radius, a[i + 1] + DisplayHeight / 2 - radius, a[i + 2], 2 * radius));
            }
        }

        public void RefreshView()
        {
            Items.Clear();
            displayElements();
        }



        void Notify(string propName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propName));
            }
        }


    }


}
