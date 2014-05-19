using System;
using System.Collections.ObjectModel;
using System.Linq;
using MonthCalendar;
using UniversityReservationSystem.Interface.Models;

// ReSharper disable once CheckNamespace
namespace UniversityReservationSystem.Interface.ViewModels
{
    public abstract class IReservableViewModel<T> : IViewModel<T>
        where T: class
    {
        protected DateTime _currentDateOnCalendar = DateTime.Now;

        public ObservableCollection<Reservation> ReservationsOfSelected { get; set; }
        public ObservableCollection<ReservationOnCalendar> ReservationsOfSelectedOnCalendar { get; set; }

        protected IReservableViewModel()
        {
            ReservationsOfSelected = new ObservableCollection<Reservation>();
            ReservationsOfSelectedOnCalendar = new ObservableCollection<ReservationOnCalendar>();
        }

        public void MonthChanged(DateTime newDisplayStartDate)
        {
            _currentDateOnCalendar = newDisplayStartDate;
            ReservationsOfSelectedOnCalendar.Clear();

            foreach (var item in ReservationsOfSelected.Where(x =>
                x.DateOfStart.Month == newDisplayStartDate.Month && x.DateOfStart.Year == newDisplayStartDate.Year))
            {
                ReservationsOfSelectedOnCalendar.Add(new ReservationOnCalendar
                {
                    Ptr = item.Ptr,
                    StartTime = item.DateOfStart,
                    Subject = item.Name,
                });
            }
        }

        public void ReloadData()
        {
            UpdateAfterSelection(false);
            RefreshCalendar();
        }

        public void RefreshCalendar()
        {
            MonthChanged(_currentDateOnCalendar);
        }
    }
}
