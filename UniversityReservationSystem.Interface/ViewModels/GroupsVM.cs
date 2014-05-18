using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using MonthCalendar;
using UniversityReservationSystem.Interface.Models;

namespace UniversityReservationSystem.Interface.ViewModels
{
    public class GroupsVM : IViewModel<Group>
    {
        private int _year;
        private string _degreeCourse;
        private int _groupNumber;
        private bool _isDegreeFocused;

        public ObservableCollection<Group> Groups { get; private set; }
        public ObservableCollection<Student> StudentsOfSelectedGroup { get; set; }
        public ObservableCollection<Reservation> ReservationsOfSelectedGroup { get; set; }

        public bool IsDegreeFocused
        {
            get { return _isDegreeFocused; }
            set
            {
                if (_isDegreeFocused != value)
                {
                    _isDegreeFocused = value;
                    RaisePropertyChanged("IsDegreeFocused");
                }
            }
        }
        public int Year
        {
            get { return _year; }
            set
            {
                if (_year != value)
                {
                    _year = value;
                    RaisePropertyChanged("Year");
                }
            }
        }
        public string DegreeCourse
        {
            get { return _degreeCourse; }
            set
            {
                if (_degreeCourse != value)
                {
                    _degreeCourse = value;
                    RaisePropertyChanged("DegreeCourse");
                }
            }
        }
        public int GroupNumber
        {
            get { return _groupNumber; }
            set
            {
                if (_groupNumber != value)
                {
                    _groupNumber = value;
                    RaisePropertyChanged("GroupNumber");
                }
            }
        }
        
        public GroupsVM()
        {
            if (IsInDesignMode) return;

            Groups = App.Groups;
            SelectedItem = Groups.FirstOrDefault();
            StudentsOfSelectedGroup = new ObservableCollection<Student>();
            ReservationsOfSelectedGroup = new ObservableCollection<Reservation>();

            UpdateAfterSelection(false);
        }

        public void MonthChanged(List<ReservationOnCalendar> reservationsOfMonth, DateTime newDisplayStartDate)
        {
            reservationsOfMonth.Clear();
            reservationsOfMonth.AddRange(ReservationsOfSelectedGroup.Where(x =>
                x.DateOfStart.Month == newDisplayStartDate.Month && x.DateOfStart.Year == newDisplayStartDate.Year)
                .Select(item => new ReservationOnCalendar
                {
                    Ptr = item.Ptr, StartTime = item.DateOfStart, Subject = item.Name,
                }));
        }

        protected override void Add()
        {
            var groupToAdd = new Group(
                "Type here the desired degree course name",
                DateTime.Today.Year, 1);
            Groups.Add(groupToAdd);
            SelectedItem = Groups.Last();
            IsDegreeFocused = true;
        }

        protected override void SaveChanges()
        {
            SelectedItem.Edit(Year, DegreeCourse, GroupNumber);
        }

        protected override sealed void UpdateAfterSelection(bool isNull)
        {
            if (!isNull)
            {
                if (ReservationsOfSelectedGroup != null)
                {
                    SelectedItem.GetStudents(StudentsOfSelectedGroup);
                    SelectedItem.GetReservations(ReservationsOfSelectedGroup);
                }
                Year = SelectedItem.Year;
                DegreeCourse = SelectedItem.DegreeCourse;
                GroupNumber = SelectedItem.GroupNumber;
            }
            else
            {
                Year = 0;
                DegreeCourse = String.Empty;
                GroupNumber = 0;
                StudentsOfSelectedGroup.Clear();
                ReservationsOfSelectedGroup.Clear();
            }
        }

        public override void Refresh()
        {
            
        }

        protected override void Delete()
        {
            SelectedItem.Delete();
            Groups.Remove(SelectedItem);
            SelectedItem = Groups.LastOrDefault();
        }
    }
}
