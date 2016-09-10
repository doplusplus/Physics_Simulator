using System;
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
using System.Windows.Media.Animation;

namespace SimulationTool
{
    public class circle :DependencyObject // INotifyPropertyChanged
    {
        //      public event PropertyChangedEventHandler PropertyChanged;
        public circle(double x_, double y_, double z_, double radius_)
        {
            Xcoord = x_;
            Ycoord = y_;
            Zcoord = z_;
            Radius = radius_;
        }

        public static DependencyProperty XcoordProperty = DependencyProperty.Register("Xcoord", typeof(Double), typeof(circle));
        
        public double Xcoord { get { return (double)GetValue(XcoordProperty); } set { SetValue(XcoordProperty,value); } }
        public double Ycoord { get; set; }
        public double Zcoord { get; set; }
        public double Radius { get; set; }

        /*
                public void Notify(string propName)
                {
                    if (PropertyChanged != null)
                    {
                        PropertyChanged(this, new PropertyChangedEventArgs(propName));
                    }
                }
                */
    }


    public class DisplayVM : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
   //     public event NotifyCollectionChangedEventHandler CollectionChanged;

        private const int radius = 10;


        private ObservableCollection<circle> Items = new ObservableCollection<circle>();
        public ObservableCollection<circle> circleItems { get { return Items; } set { Items = value; } }

        private List<double> coordTodisplay = new List<double>();

        public DisplayVM()
        { }

        private double dX;
        private double dY;
        private double CX;
        private double CY;

        public double DisplayWidth { get; set; }
        public double XUnit { get { return dX; } set { dX = value; Notify("XUnit"); } }
        public double CenterX { get { return CX; } set { CX = value; Notify("CenterX"); } }

        public double DisplayHeight { get; set; }
        public double YUnit { get { return dY; } set { dY = value; Notify("YUnit"); } }
        public double CenterY { get { return CY; } set { CY = value; Notify("CenterY"); } }

        public void displayElements(List<double> toDisp)
        {
            coordTodisplay = toDisp;
            //     Items.Clear();
            int i = 0;
            //for (int i = 0; i < toDisp.Count - 2; i = i + 3)
            //{
            if (toDisp.Count > 0)
            {
                circleItems.Add(new circle(toDisp[i] + DisplayWidth / 2 - radius, toDisp[i + 1] + DisplayHeight / 2 - radius, toDisp[i + 2], 2 * radius));
            }
            //}
        }

        public void RefreshView()
        {
            Items.Clear();
            displayElements(coordTodisplay);
        }

        void Notify(string propName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propName));
            }
        }

  /*      public void LaunchAnimations(List<DoubleAnimation> XAnim, List<DoubleAnimation> YAnim)
        {
            Storyboard sb = new Storyboard();
            //temporaire
            Items.Clear();
            var c = new circle(5, 5, 0, 3);       
            circleItems.Add(c);
            
            foreach (var xa in XAnim)
            {
                sb.Children.Add(xa); Storyboard.SetTarget(xa, circleItems[0]);
                var prop = new PropertyPath(circle.XcoordProperty);
                Storyboard.SetTargetProperty(xa,prop);
            }
    //later        foreach (var ya in YAnim) { sb.Children.Add(ya); }

            sb.Begin();
            
        }

    */
    }


}
