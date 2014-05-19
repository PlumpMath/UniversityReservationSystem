using System;
using System.Collections.Generic;
using System.Windows.Controls;
using MonthCalendar;

namespace UniversityReservationSystem.Interface.Views
{
    public partial class TeachersTab : UserControl
    {
        public TeachersTab()
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
            
        }
    }
}
