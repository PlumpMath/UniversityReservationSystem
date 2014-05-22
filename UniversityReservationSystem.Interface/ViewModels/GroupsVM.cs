using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows;
using MonthCalendar;
using UniversityReservationSystem.Interface.Models;

namespace UniversityReservationSystem.Interface.ViewModels
{
    public class GroupsVM : IReservableViewModel<Group>
    {
        private int _year;
        private string _degreeCourse;
        private int _groupNumber;
        private bool _isDegreeFocused;

        public ObservableCollection<Group> Groups { get; private set; }
        public ObservableCollection<Student> StudentsOfSelectedGroup { get; set; }

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

            StudentsOfSelectedGroup = new ObservableCollection<Student>();
            Groups = App.Groups;
            SelectedItem = Groups.FirstOrDefault();

            UpdateAfterSelection(false);
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
                if (ReservationsOfSelected != null)
                {
                    SelectedItem.GetStudents(StudentsOfSelectedGroup);
                    SelectedItem.GetReservations(ReservationsOfSelected);
                    MonthChanged(_currentDateOnCalendar);
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
                ReservationsOfSelected.Clear();
                ReservationsOfSelectedOnCalendar.Clear();
            }
        }

        protected override void Delete()
        {
            var studentsToDelete = App.Students.Where(student => student.Group.Ptr == SelectedItem.Ptr).ToList();

            foreach (var student in studentsToDelete)
            {
                App.Students.Remove(student);
            }

            SelectedItem.Delete();
            Groups.Remove(SelectedItem);
            SelectedItem = Groups.LastOrDefault();

            ViewModelLocator.Teachers.ReloadData();
            ViewModelLocator.Rooms.ReloadData();
        }

        public void ReservationClicked(IntPtr reservationptr)
        {
            MessageBox.Show(App.Reservations.Single(x => x.Ptr == reservationptr).ToString());
        }
    }
}
