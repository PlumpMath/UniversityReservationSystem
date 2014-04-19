using System.Runtime.InteropServices;
using System.Windows;
using UniversityReservationSystem.Interface.Models;

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
            

            var group2 = new Group("nowy", 2023, 3);
            MessageBox.Show(group2.ToString());

            var stud = new Student("szymon", "bartnik", group2, 3, 3.3);
            MessageBox.Show(stud.ToString());

            App.FreeDB();
        }
    }
}
