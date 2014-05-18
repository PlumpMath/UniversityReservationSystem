using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using MonthCalendar;
using UniversityReservationSystem.Interface.ViewModels;

namespace UniversityReservationSystem.Interface.Views
{
    public partial class GroupsTab : UserControl
    {
        private List<ReservationOnCalendar> _reservation = new List<ReservationOnCalendar>();
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
                vm.MonthChanged(_reservation, e.NewDisplayStartDate);
                CalendarGroups.MonthReservations = _reservation;
            }
        }

        private void CalendarGroups_OnReservationClicked(IntPtr reservationptr)
        {
            var vm = DataContext as GroupsVM;
            if (vm != null)
            {
                vm.ReservationClicked(reservationptr);
            }
        }
    }
}
