using System;
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
using System.Windows.Threading;
using System.Windows.Media.Media3D;
using System.Diagnostics;
using System.Timers;

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
                outPan.resetTimeTracker();
                dispTimer.Interval = TimeSpan.Parse("0:00:" + outPan.DisplayStep);
                stopButton.Visibility = Visibility.Visible;
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
            List<Point3D> pointList;
            if (simSett.RTMode)
            {
                pointList = new List<Point3D>();
                var elemList = sManager.sceneElems_;
                string s = "";
                for (int i = 0; i < elemList.Count - 2; i = i + 3)
                {
                    pointList.Add(new Point3D(elemList[i], elemList[i], 0));
                    s = s + pointList.Last().X.ToString() + " " + pointList.Last().Y.ToString();
                }
                CoordTracker.Text = s;
                display.circleItems.Clear();
            }
            else
            {
                if (!fileVM_.Read)
                {
                    dispTimer.Stop();
                    (LaunchBtn.Template.FindName("buttnColor", LaunchBtn) as Path).Fill = Brushes.LightGray;
                    return;
                }

                pointList = fileVM_.CurrentLoc;
                fileVM_.next();
                display.circleItems.Clear();
            }

            foreach (var crcle in pointList)
            {
                display.addToDisplay(crcle);
            }
            outPan.increment();
        }

        //-------------------------------------------------------------------------------------------------------------


        //TEST-TOOLS-------------------------------------------------------------
        static double testCoord = 0;
        private void TestButton_Click(object sender, RoutedEventArgs e)
        {
            elemDef.massInput = "1.0";
            this.elemDef.Xinput = this.elemDef.Yinput = this.elemDef.Zinput = testCoord.ToString(CultureInfo.InvariantCulture); testCoord += 2;
            this.elemDef.FXinput = this.elemDef.FZinput = this.elemDef.FYinput = "1.0";
            MaterialPoint.Command.Execute(null);
            AddAction.Command.Execute(null);
        }

        private void SimTestButton_Click(object sender, RoutedEventArgs e)
        {
            simSett.Duration = "12";
            simSett.ComputStep = "0.5";
            simSett.RTMode = true;
            outPan.DisplayStep = "1";
        }

        private void RTtimer_Clicked(object sender, RoutedEventArgs e)
        {
            // outManager.startTimer();
            //sManager.increment();
            var elemList = sManager.sceneElems_;
            string s = "";
            for (int i = 0; i < elemList.Count - 2; i = i + 3)
            {
                s = s + elemList[0].ToString() + " " + elemList[1].ToString() + " " + elemList[2].ToString();
            }
            CoordTracker.Text = s;
        }

        //-----------------------------------------------------------------------------------






        private void OpenBrowser(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog openF = new Microsoft.Win32.OpenFileDialog();
            openF.InitialDirectory = System.IO.Path.GetDirectoryName(outPan.TargetFile);
            openF.ShowDialog();

            outPan.TargetFile = openF.FileName;
        }

        private void stpButtonClicked(object sender, RoutedEventArgs e)
        {
            if (dispTimer.IsEnabled) { dispTimer.Stop(); }
            else { dispTimer.Start(); }
        }

        private void onRTModeSelected(object sender, RoutedEventArgs e)
        {
            enableDisplay.IsChecked = true;
            enableDisplay.IsEnabled = false;
            proLog.IsEnabled = false;
            proLog.IsChecked = false;
            noLog.IsChecked = true;
        }

        private void onPrecsnMdSelected(object sender, RoutedEventArgs e)
        {
            if (outPan.fromSim) { proLog.IsEnabled = true; enableDisplay.IsEnabled = true; }
        }

        private void onClick(object sender, RoutedEventArgs e)
        {
            if (outPan.fromSim)
            {
                proLog.IsEnabled = false;
                proLog.IsChecked = false;
                noLog.IsChecked = true;
                enableDisplay.IsEnabled = false;
                enableDisplay.IsChecked = true;
            }
            else { if (sManager.accuracyMode) { proLog.IsEnabled = true; enableDisplay.IsEnabled = true; } }
        }
    }
}