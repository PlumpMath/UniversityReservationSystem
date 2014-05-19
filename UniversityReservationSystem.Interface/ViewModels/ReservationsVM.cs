using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Threading;
using System.Windows;
using GalaSoft.MvvmLight;
using UniversityReservationSystem.Interface.Models;

namespace UniversityReservationSystem.Interface.ViewModels
{
    public class ReservationsVM : IViewModel<Reservation>
    {
        private string _name;
        private Group _selectedGroup;
        private IRoom _selectedRoom;
        private Teacher _selectedTeacher;
        private DateTime? _dateOfStart;
        private DateTime? _dateOfEnd;
        private bool _isNameFocused;

        public ObservableCollection<Group> Groups { get; set; }
        public ObservableCollection<IRoom> Rooms { get; set; }
        public ObservableCollection<Teacher> Teachers { get; set; }
        public ObservableCollection<Reservation> Reservations { get; set; }
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
        public Group SelectedGroup
        {
            get { return _selectedGroup; }
            set
            {
                if (_selectedGroup != value)
                {
                    _selectedGroup = value;
                    RaisePropertyChanged("SelectedGroup");
                }
            }
        }
        public IRoom SelectedRoom
        {
            get { return _selectedRoom; }
            set
            {
                if (_selectedRoom != value)
                {
                    _selectedRoom = value;
                    RaisePropertyChanged("SelectedRoom");
                }
            }
        }
        public Teacher SelectedTeacher
        {
            get { return _selectedTeacher; }
            set
            {
                if (_selectedTeacher != value)
                {
                    _selectedTeacher = value;
                    RaisePropertyChanged("SelectedTeacher");
                }
            }
        }
        public DateTime? DateOfStart
        {
            get { return _dateOfStart; }
            set
            {
                if (value != _dateOfStart && value != null)
                {
                    _dateOfStart = value;
                    RaisePropertyChanged("DateOfStart");
                }
            }
        }
        public DateTime? DateOfEnd
        {
            get { return _dateOfEnd; }
            set
            {
                if (value != _dateOfEnd)
                {
                    _dateOfEnd = value;
                    RaisePropertyChanged("DateOfEnd");
                }
            }
        }
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

        public ReservationsVM()
        {
            if (IsInDesignMode) return;
            Groups = App.Groups;
            Rooms = App.Rooms;
            Teachers = App.Teachers;
            Reservations = App.Reservations;
            SelectedItem = Reservations.FirstOrDefault();
        }

        protected override void Add()
        {
            var reservationToAdd = new Reservation(
                "Type description", DateTime.Today.AddYears(10),
                DateTime.Today.AddYears(10).AddHours(1),
                Teachers.First(), Rooms.First(), Groups.First());

            Reservations.Add(reservationToAdd);
            SelectedItem = Reservations.Last();
            IsNameFocused = true;
        }

        private void RefreshDependencies()
        {
            ViewModelLocator.Groups.RefreshCalendar();
            ViewModelLocator.Students.RefreshCalendar();
            ViewModelLocator.Teachers.RefreshCalendar();
            //ViewModelLocator.Rooms.RefreshCalendar();
        }

        protected override void SaveChanges()
        {
            if (DateOfEnd == null || DateOfStart == null) return;

            if (!SelectedItem.Edit(
                Name, DateOfStart.Value, DateOfEnd.Value,
                SelectedTeacher, SelectedRoom, SelectedGroup))
            {
                MessageBox.Show("Collisions detected! Changes not accepted!");
            }

            RefreshDependencies();
            ViewModelLocator.Groups.ReloadData();
            ViewModelLocator.Students.ReloadData();
        }

        protected override void Delete()
        {
            ViewModelLocator.Groups.ReservationsOfSelected.Remove(SelectedItem);
            ViewModelLocator.Students.ReservationsOfSelected.Remove(SelectedItem);
            ViewModelLocator.Teachers.ReservationsOfSelected.Remove(SelectedItem);
            //ViewModelLocator.Rooms.ReservationsOfSelected.Remove(SelectedItem);

            SelectedItem.Delete();
            Reservations.Remove(SelectedItem);
            SelectedItem = Reservations.LastOrDefault();

            RefreshDependencies();
        }

        protected override void UpdateAfterSelection(bool isNull)
        {
            if (!isNull)
            {
                Name = SelectedItem.Name;
                DateOfStart = SelectedItem.DateOfStart;
                DateOfEnd = SelectedItem.DateOfEnd;
                SelectedGroup = SelectedItem.Group;
                SelectedRoom = SelectedItem.Room;
                SelectedTeacher = SelectedItem.Teacher;
            }
            else
            {
                Name = String.Empty;
                DateOfStart = null;
                DateOfEnd = null;
                SelectedGroup = null;
                SelectedRoom = null;
                SelectedTeacher = null;
            }
        }
    }
}
