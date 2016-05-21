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
using ManagedClasses;

namespace SimulationTool
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private ManagedModel M = new ManagedModel();
        private MainWindowModel MainVM;
        private DisplayVM display;
        private ElemDefVM elemDef;
        private OutputPanelVM outPan;
        private SimManager SManager;
        private SimSettingsVM SimSett;

        public MainWindow()
        {
            InitializeComponent();

            MainVM = new MainWindowModel(M);
            display = new DisplayVM(M);
            elemDef = new ElemDefVM(M, display);
            outPan = new OutputPanelVM();
            SManager = new SimManager(M, display, outPan);
            SimSett = new SimSettingsVM();

            Loaded += MyWindow_Loaded;
            SizeChanged += OnResize;


            this.DataContext = MainVM;
            this.ElemDefTools.DataContext = elemDef;
            this.SceneDisplay.DataContext = display;
            this.OutputPanel.DataContext = outPan;
            this.SimSetTools.DataContext = SimSett;

            //  this.LaunchBtn.DataContext = display;
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
            //  MessageBox.Show(M.description());
            Run();
        }

        private void Run()
        {
            double duration = Double.Parse(SimSett.Duration, System.Globalization.NumberStyles.AllowDecimalPoint, CultureInfo.InvariantCulture);
            double compStep = Double.Parse(SimSett.ComputStep, System.Globalization.NumberStyles.AllowDecimalPoint, CultureInfo.InvariantCulture);
            double dispStep = Double.Parse(outPan.DisplayStep, System.Globalization.NumberStyles.AllowDecimalPoint, CultureInfo.InvariantCulture);

            SManager.startSimulation(compStep, dispStep, duration);
        }

        private void NextButton_Click(object sender, RoutedEventArgs e)
        {

            DefSelector.SelectedIndex++;
        }

        private void prevButton_Click(object sender, RoutedEventArgs e)
        {
            if (DefSelector.SelectedIndex > 0) DefSelector.SelectedIndex--;
        }

        private void RadioButton_Checked(object sender, RoutedEventArgs e)
        { }

        private void elmntNmbr_TextChanged(object sender, RoutedEventArgs e) { }

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
            SimSett.Duration = "12";
            SimSett.ComputStep = "0.01";
            outPan.DisplayStep = "0.3";
        }

        private void SimModeSelect_Checked(object sender, RoutedEventArgs e)
        {

        }
    }
}