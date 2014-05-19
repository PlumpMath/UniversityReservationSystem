using System;
using System.Windows.Controls;
using MonthCalendar;
using UniversityReservationSystem.Interface.ViewModels;

namespace UniversityReservationSystem.Interface.Views
{
    public partial class GroupsTab : UserControl
    {
        public GroupsTab()
        {
            InitializeComponent();
            if (System.ComponentModel.DesignerProperties.GetIsInDesignMode(this)) return;
        }

        private void DisplayMonthChanged(MonthChangedEventArgs e)
        {
            var vm = DataContext as GroupsVM;
            if (vm != null)
            {
                vm.MonthChanged(e.NewDisplayStartDate);
            }
        }

        private void Calendar_OnReservationClicked(IntPtr reservationptr)
        {
            var vm = DataContext as GroupsVM;
            if (vm != null)
            {
                vm.ReservationClicked(reservationptr);
            }
        }
    }
}
