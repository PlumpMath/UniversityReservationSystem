using System;
using System.Collections.Generic;
using System.Windows.Controls;
using MonthCalendar;

namespace UniversityReservationSystem.Interface.Views
{
    public partial class StudentsTab : UserControl
    {
        private List<Appointment> _myAppointmentsList = new List<Appointment>();

        public StudentsTab()
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
            CalendarStudents.MonthAppointments = _myAppointmentsList.FindAll((apt) =>
                apt.StartTime != null &&
                Convert.ToDateTime(apt.StartTime).Month == CalendarStudents.DisplayStartDate.Month &&
                Convert.ToDateTime(apt.StartTime).Year == CalendarStudents.DisplayStartDate.Year);
        }
    }
}
