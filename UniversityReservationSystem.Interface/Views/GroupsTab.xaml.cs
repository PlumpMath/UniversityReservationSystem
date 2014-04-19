using System.Collections.ObjectModel;
using System.Windows.Controls;
using UniversityReservationSystem.Interface.Models;

namespace UniversityReservationSystem.Interface.Views
{
    public partial class GroupsTab : UserControl
    {
        public GroupsTab()
        {
            InitializeComponent();
            if (System.ComponentModel.DesignerProperties.GetIsInDesignMode(this)) return;

            App.LoadDB("home");

            var groupsList = new ObservableCollection<Group>();

            for (uint i = 0; i < App.GetGroupsCount(); i++)
            {
                groupsList.Add(new Group(App.GetGroupByIndex(i)));
            }

            GroupsGrid.ItemsSource = groupsList;

            //App.SaveDB();
        }
    }
}
