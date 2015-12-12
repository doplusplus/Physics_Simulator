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

namespace MultiPhys_GUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void DefSelector_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cBox = sender as ComboBox;
            ComboBoxItem Selection = cBox.SelectedItem as ComboBoxItem;
            DefToolsPres.Visibility = Visibility.Collapsed;

            switch (Selection.Name)
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
            }
        }

        private void LaunchButton_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("nah joking!...it's a placehoder", "Launching the simulation");
        }

        private void MaterialPoint_Click(object sender, RoutedEventArgs e)
        {
            double mass; bool b;
            double InputCx, InputCy, InputCz;
            string message = String.Empty;

            b = Double.TryParse(massInput.Text, System.Globalization.NumberStyles.AllowDecimalPoint, CultureInfo.InvariantCulture, out mass);
            if (b) { message += "mass: "+ mass.ToString() + Environment.NewLine; }
            else   { message += "not going anywhere without mass" + Environment.NewLine ; }

            message += "Position of the center of mass: "+Environment.NewLine;
            //Cx
            if (Cx.Text.Equals("x")) { message += " Cx = 0 "; }
            else
            {
                b = Double.TryParse(Cx.Text, System.Globalization.NumberStyles.AllowDecimalPoint, CultureInfo.InvariantCulture, out InputCx);
                if (b) { message += " Cx = "+ InputCx.ToString() ; }
                else { MessageBox.Show("numerical value required for Cx", " bad result"); }
            }
            //Cy
            if (Cy.Text.Equals("y")) { message += " Cy = 0 "; }
            else
            {
                b = Double.TryParse(Cy.Text, System.Globalization.NumberStyles.AllowDecimalPoint, CultureInfo.InvariantCulture, out InputCy);
                if (b) { message += " Cy = " + InputCy.ToString(); }
                else { MessageBox.Show("this is text", " bad result"); }
            }
            //Cz
            if (Cz.Text.Equals("z")) { message += " Cz = 0 "; }
            else
            {
                b = Double.TryParse(Cz.Text, System.Globalization.NumberStyles.AllowDecimalPoint, CultureInfo.InvariantCulture, out InputCz);
                if (b) { message += " Cz= " + InputCz.ToString(); }
                else { MessageBox.Show("this is text", " bad result"); }
            }
            MessageBox.Show("Proceed with: " + Environment.NewLine + message , "data check", MessageBoxButton.OKCancel);
        }

        private void RadioButton_Checked(object sender, RoutedEventArgs e)
        {

        }
    }
}
