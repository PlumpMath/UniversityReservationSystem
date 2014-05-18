using System.Windows.Controls;
using UniversityReservationSystem.Interface.ViewModels;
using Xceed.Wpf.AvalonDock.Controls;

namespace UniversityReservationSystem.Interface.Views
{
    public partial class MainWindow
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Selector_OnSelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            IRefreshable vm = null;

            if (GroupsTab.IsSelected)
            {
                var groupsTab = (GroupsTab)FindName("GroupsTabInside");
                if (groupsTab != null)
                    vm = groupsTab.DataContext as IRefreshable;
            }
            else if (ReservationsTab.IsSelected)
            {
                var reservationsTab = (ReservationsTab)FindName("ReservationsTabInside");
                if (reservationsTab != null)
                    vm = reservationsTab.DataContext as IRefreshable;
            }
            else if (RoomsTab.IsSelected)
            {
                var findName = (RoomsTab)FindName("RoomsTabInside");
                if (findName != null)
                    vm = findName.DataContext as IRefreshable;
            }
            else if (StudentsTab.IsSelected)
            {
                var studentsTab = (StudentsTab)FindName("StudentsTabInside");
                if (studentsTab != null)
                    vm = studentsTab.DataContext as IRefreshable;
            }
            else if (TeachersTab.IsSelected)
            {
                var teachersTab = (TeachersTab)FindName("TeachersTabInside");
                if (teachersTab != null)
                    vm = teachersTab.DataContext as IRefreshable;
            }

            if (vm != null) vm.Refresh();
        }
    }
}
