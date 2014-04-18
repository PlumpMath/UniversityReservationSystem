using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace UniversityReservationSystem.Interface
{
    public partial class MainWindow
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            App.LoadDB("home");
            App.SaveDB();
        }
    }
}
