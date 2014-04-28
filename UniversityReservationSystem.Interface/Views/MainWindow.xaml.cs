using System;
using System.Collections.Generic;
using MonthCalendar;

namespace UniversityReservationSystem.Interface.Views
{
    public partial class MainWindow
    {
        private List<Appointment> _myAppointmentsList = new List<Appointment>();
        public MainWindow()
        {
            InitializeComponent();

            Loaded += (sender, args) =>
            {
                //var rand = new Random(DateTime.Now.Second);

                //for (int i = 1; i <= 50; i++)
                //{
                //    var apt = new Appointment();

                //    apt.AppointmentId = i;
                //    apt.StartTime = new DateTime(DateTime.Now.Year, rand.Next(1, 12),
                //        rand.Next(1, DateTime.DaysInMonth(DateTime.Now.Year, DateTime.Now.Month)));
                //    apt.EndTime = apt.StartTime;
                //    apt.Subject = "Random apt";

                //    _myAppointmentsList.Add(apt);
                //}
                //SetAppointments();
            };

        }

        private void DisplayMonthChanged(MonthChangedEventArgs e)
        {
            SetAppointments();
        }

        private void SetAppointments()
        {
            CalendarControl.MonthAppointments = _myAppointmentsList.FindAll((apt) =>
                apt.StartTime != null &&
                Convert.ToDateTime(apt.StartTime).Month == CalendarControl.DisplayStartDate.Month &&
                Convert.ToDateTime(apt.StartTime).Year == CalendarControl.DisplayStartDate.Year);
        }
    }
}
