using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows;
using UniversityReservationSystem.Interface.Models;

namespace UniversityReservationSystem.Interface.ViewModels
{
    public enum RoomType
    {
        Lab,
        Exercise,
    };

    public class RoomsVM : IReservableViewModel<IRoom>
    {
        private string _name;
        private RoomType _type;
        private int _capacity;
        private bool _isNameFocused;

        public ObservableCollection<IRoom> Rooms { get; set; }

        public bool IsNameFocused
        {
            get { return _isNameFocused; }
            set
            {
                if (_isNameFocused != value)
                {
                    _isNameFocused = value;
                    RaisePropertyChanged("IsNameFocused");
                }
            }
        }
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
        public RoomType Type
        {
            get { return _type; }
            set
            {
                if (_type != value)
                {
                    _type = value;
                    RaisePropertyChanged("Type");
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

                RoomType roomType;

                if(!Enum.TryParse(SelectedItem.Type, true, out roomType))
                    throw new Exception("Error while parsing the enum!");

                Name = SelectedItem.Name;
                Type = roomType;
                Capacity = SelectedItem.Capacity;
            }
            else
            {
                Name = String.Empty;
                Type = 0;
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
