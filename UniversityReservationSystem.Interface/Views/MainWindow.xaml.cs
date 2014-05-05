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
        }
    }
}
