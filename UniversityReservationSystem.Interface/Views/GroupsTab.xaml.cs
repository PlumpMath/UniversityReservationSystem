using System;
using System.Collections.Generic;
using System.Windows.Controls;
using MonthCalendar;

namespace UniversityReservationSystem.Interface.Views
{
    public partial class GroupsTab : UserControl
    {
        private List<Appointment> _myAppointmentsList = new List<Appointment>();
        public GroupsTab()
        {
            InitializeComponent();
            if (System.ComponentModel.DesignerProperties.GetIsInDesignMode(this)) return;
        }

        private void DisplayMonthChanged(MonthChangedEventArgs e)
        {
            SetAppointments();
        }

        private void SetAppointments()
        {
            CalendarGroups.MonthAppointments = _myAppointmentsList.FindAll((apt) =>
                apt.StartTime != null &&
                Convert.ToDateTime(apt.StartTime).Month == CalendarGroups.DisplayStartDate.Month &&
                Convert.ToDateTime(apt.StartTime).Year == CalendarGroups.DisplayStartDate.Year);
        }
    }
}
