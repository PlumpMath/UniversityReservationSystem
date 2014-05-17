using System;
using System.Collections.ObjectModel;
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
                if (value != _dateOfStart)
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

        public ReservationsVM()
        {
            if (IsInDesignMode) return;

            Groups = App.Groups;
            Rooms = App.Rooms;
            Teachers = App.Teachers;
            Reservations = App.Reservations;
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
