﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Globalization;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Media.Animation;
using System.Threading;
using System.Windows.Threading;
using System.Windows.Media.Media3D;
using System.Diagnostics;

namespace SimulationTool
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private ElemDefVM elemDef;
        private EnvironmentDefVM envDef;
        private SimSettingsVM simSett;

        private OutputPanelVM outPan;

        private SimManager sManager;
        private OutputManager outManager;

        private DisplayVM display;
        private FileModel fileVM_;

        private DispatcherTimer dispTimer = new DispatcherTimer();

        public MainWindow()
        {
            InitializeComponent();

            display = new DisplayVM();
            outPan = new OutputPanelVM();

            outManager = new OutputManager();
            fileVM_ = new FileModel(outManager);
            sManager = new SimManager(outManager);
            outManager.link(display, fileVM_, outPan, sManager);

            elemDef = new ElemDefVM(sManager, outManager);
            envDef = new EnvironmentDefVM(sManager);
            simSett = new SimSettingsVM(sManager);

            this.ElemDefTools.DataContext = elemDef;
            this.EnvDefTools.DataContext = envDef;
            this.SimSetTools.DataContext = simSett;
            this.SceneDisplay.DataContext = display;
            this.OutputPanel.DataContext = outPan;

            Loaded += MyWindow_Loaded;
            SizeChanged += OnResize;
            dispTimer.Tick += onDispStep;
        }

        private void OnResize(object sender, RoutedEventArgs e)
        {
            display.DisplayHeight = SceneDisplay.ActualHeight;
            display.DisplayWidth = SceneDisplay.ActualWidth;
            display.RefreshView();
        }

        private void MyWindow_Loaded(object sender, RoutedEventArgs e)
        {
            const double ratio = 0.1;
            this.Xstroke.DataContext = display;
            display.DisplayHeight = SceneDisplay.ActualHeight;
            display.DisplayWidth = SceneDisplay.ActualWidth;
            display.XUnit = ratio * display.DisplayWidth + display.CenterX;
            display.YUnit = -ratio * display.DisplayHeight + display.CenterY;
        }

        private void DefSelector_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cBox = sender as ComboBox;
            ComboBoxItem Selection = cBox.SelectedItem as ComboBoxItem;
            DefToolsPres.Visibility = Visibility.Collapsed;
            selectTool(Selection.Name);
        }

        private void selectTool(string s)
        {
            switch (s)
            {
                case "Elmnt":
                    ElemDefTools.Visibility = Visibility.Visible;
                    EnvDefTools.Visibility = Visibility.Collapsed;
                    SimSetTools.Visibility = Visibility.Collapsed;
                    break;

                case "Env":
                    ElemDefTools.Visibility = Visibility.Collapsed;
                    EnvDefTools.Visibility = Visibility.Visible;
                    SimSetTools.Visibility = Visibility.Collapsed;
                    break;

                case "Sim":
                    ElemDefTools.Visibility = Visibility.Collapsed;
                    EnvDefTools.Visibility = Visibility.Collapsed;
                    SimSetTools.Visibility = Visibility.Visible;
                    break;

                default:
                    break;
            }

        }

        private void LaunchButton_Click(object sender, RoutedEventArgs e)
        {
            if (outPan.DisplayStep == "disp. step in s" && outPan.DisplayEnbld) { MessageBox.Show("please specify the refresh period"); }

            outManager.launch();
            (LaunchBtn.Template.FindName("buttnColor", LaunchBtn) as Path).Fill = Brushes.DeepPink;
            if (outPan.DisplayEnbld)
            {
                outPan.switchTimeTracker();
                dispTimer.Interval = TimeSpan.Parse("0:00:" + outPan.DisplayStep);
                dispTimer.Start();
            }
        }

        private void NextButton_Click(object sender, RoutedEventArgs e)
        {
            DefSelector.SelectedIndex++;
        }

        private void prevButton_Click(object sender, RoutedEventArgs e)
        {
            if (DefSelector.SelectedIndex > 0) DefSelector.SelectedIndex--;
        }

        private void elmntNmbr_TextChanged(object sender, RoutedEventArgs e) { }

        //Canvas display routine-------------------------------------------------------------------------
        void onDispStep(object sender, EventArgs e)
        {
            if (!fileVM_.Read)
            {
                dispTimer.Stop();
                (LaunchBtn.Template.FindName("buttnColor", LaunchBtn) as Path).Fill = Brushes.LightGray;
                return;
            }

            List<Point3D> pointList = fileVM_.CurrentLoc;
            fileVM_.next();
            display.circleItems.Clear();

            foreach (var crcle in pointList)
            {
                display.circleItems.Add(new circle(crcle.X, crcle.Y, crcle.Z, 4));

            }
            //            circle c = new circle(p.X, p.Y, p.Z, 4);
            outPan.increment();
            //            display.circleItems.Add(c);
            //    display.circleItems.Remove(c);
            //SceneDisplay.UpdateLayout();
        }
        //-------------------------------------------------------------------------------------------------------------


        //TEST-TOOLS-------------------------------------------------------------
        static double testCoord = 0;
        private void TestButton_Click(object sender, RoutedEventArgs e)
        {
            elemDef.massInput = "2";
            this.elemDef.Xinput = this.elemDef.Yinput = this.elemDef.Zinput = testCoord.ToString(CultureInfo.InvariantCulture); testCoord += 2;
            this.elemDef.FXinput = this.elemDef.FYinput = this.elemDef.FZinput = "10.0";
            MaterialPoint.Command.Execute(null);
            AddAction.Command.Execute(null);
        }

        private void SimTestButton_Click(object sender, RoutedEventArgs e)
        {
            simSett.Duration = "12";
            simSett.ComputStep = "0.01";
            outPan.DisplayStep = "0.3";
        }
        //-----------------------------------------------------------------------------------

        private void onRTModeSelected(object sender, RoutedEventArgs e)
        {
            noLog.IsChecked = true;
            proLog.IsEnabled = false;
        }

        private void onPrecsnMdSelected(object sender, RoutedEventArgs e) { proLog.IsEnabled = true; }

        private void OpenBrowser(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog openF = new Microsoft.Win32.OpenFileDialog();
            openF.InitialDirectory = System.IO.Path.GetDirectoryName(outPan.TargetFile);
            openF.ShowDialog();

            outPan.TargetFile = openF.FileName;
        }
    }
}