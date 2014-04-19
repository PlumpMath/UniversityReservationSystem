using System.Collections.ObjectModel;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Documents;
using UniversityReservationSystem.Interface.Models;

namespace UniversityReservationSystem.Interface
{
    public partial class MainWindow
    {
        public MainWindow()
        {
            InitializeComponent();

            App.LoadDB("home");
            //App.SaveDB();

            var groupsList = new ObservableCollection<Group>();

            for (uint i = 0; i < App.GetGroupsCount(); i++)
            {
                groupsList.Add(new Group(App.GetGroupByIndex(i)));
            }

            GroupsGrid.ItemsSource = groupsList;

            //var group2 = new Group("nowy", 2023, 3);
            //MessageBox.Show(group2.ToString());

            //var stud = new Student("szymon", "bartnik", group2, 3, 3.3);
            //MessageBox.Show(stud.ToString());

            //App.FreeDB();
        }
    }
}
