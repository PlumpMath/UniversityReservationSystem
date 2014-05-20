using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows;
using UniversityReservationSystem.Interface.Models;

namespace UniversityReservationSystem.Interface.ViewModels
{
    public class RoomsVM : IReservableViewModel<IRoom>
    {
        private string _name;
        private int _capacity;

        public ObservableCollection<IRoom> Rooms { get; set; }

        public string Name
        {
            get { return _name; }
            set
            {
                if (_name != value)
                {
                    _name = value;
                    RaisePropertyChanged("Name");
                }
            }
        }
        public int Capacity
        {
            get { return _capacity; }
            set
            {
                if (_capacity != value)
                {
                    _capacity = value;
                    RaisePropertyChanged("Capacity");
                }
            }
        }

        public RoomsVM()
        {
            if (IsInDesignMode) return;

            Rooms = App.Rooms;
            SelectedItem = Rooms.FirstOrDefault();

            UpdateAfterSelection(false);
        }

        protected override void Add()
        {
            throw new System.NotImplementedException();
        }

        protected override void SaveChanges()
        {
            throw new System.NotImplementedException();
        }

        protected override void Delete()
        {
            throw new System.NotImplementedException();
        }

        protected override sealed void UpdateAfterSelection(bool isNull)
        {
            if (!isNull)
            {
                if (ReservationsOfSelected != null)
                {
                    SelectedItem.GetReservations(ReservationsOfSelected);
                    MonthChanged(_currentDateOnCalendar);
                }

                Name = SelectedItem.Name;
                Capacity = SelectedItem.Capacity;
            }
            else
            {
                Name = String.Empty;
                Capacity = 0;
                ReservationsOfSelected.Clear();
                ReservationsOfSelectedOnCalendar.Clear();
            }
        }

        public void ReservationClicked(IntPtr reservationptr)
        {
            MessageBox.Show(App.Reservations.Single(x => x.Ptr == reservationptr).ToString());
        }
    }
}
