using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows;
using UniversityReservationSystem.Interface.Models;

namespace UniversityReservationSystem.Interface.ViewModels
{
    public class StudentsVM : IReservableViewModel<Student>
    {
        private Group _selectedGroup;
        private string _firstName;
        private string _lastName;
        private int _passedTerms;
        private double _averageOfMarks;
        private bool _isFirstNameFocused;

        public ObservableCollection<Student> Students { get; set; }
        public ObservableCollection<Group> Groups { get; private set; }
        public string FirstName
        {
            get { return _firstName; }
            set
            {
                if (_firstName != value)
                {
                    _firstName = value;
                    RaisePropertyChanged("FirstName");
                }
            }
        }
        public string LastName
        {
            get { return _lastName; }
            set
            {
                if (_lastName != value)
                {
                    _lastName = value;
                    RaisePropertyChanged("LastName");
                }
            }
        }
        public int PassedTerms
        {
            get { return _passedTerms; }
            set
            {
                if (_passedTerms != value)
                {
                    _passedTerms = value;
                    RaisePropertyChanged("PassedTerms");
                }
            }
        }
        public double AverageOfMarks
        {
            get { return _averageOfMarks; }
            set
            {
                if (_averageOfMarks != value)
                {
                    _averageOfMarks = value;
                    RaisePropertyChanged("AverageOfMarks");
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
        public bool IsFirstNameFocused
        {
            get { return _isFirstNameFocused; }
            set
            {
                if (_isFirstNameFocused != value)
                {
                    _isFirstNameFocused = value;
                    RaisePropertyChanged("IsFirstNameFocused");
                }
            }
        }

        public StudentsVM()
        {
            if (IsInDesignMode) return;

            Groups = App.Groups;
            Students = App.Students;
            SelectedItem = Students.FirstOrDefault();

            UpdateAfterSelection(false);
        }


        protected override void Add()
        {
            var studentToAdd = new Student(
                "Type first name", "Type last name",
                Groups.First(), 0, 0);
            Students.Add(studentToAdd);
            SelectedItem = Students.Last();
            IsFirstNameFocused = true;
        }

        protected override void SaveChanges()
        {
            SelectedItem.Edit(FirstName, LastName, SelectedGroup, PassedTerms, AverageOfMarks);
        }

        protected override sealed void UpdateAfterSelection(bool isNull)
        {
            if (!isNull && SelectedItem != null)
            {
                if (ReservationsOfSelected != null)
                {
                    SelectedItem.GetReservations(ReservationsOfSelected);
                    MonthChanged(_currentDateOnCalendar);
                }
                FirstName = SelectedItem.FirstName;
                LastName = SelectedItem.LastName;
                PassedTerms = SelectedItem.PassedTerms;
                AverageOfMarks = SelectedItem.AvgOfMarks;
                SelectedGroup = SelectedItem.Group;
            }
            else
            {
                FirstName = String.Empty;
                LastName = String.Empty;
                PassedTerms = 0;
                AverageOfMarks = 0;
                SelectedGroup = null;
                ReservationsOfSelected.Clear();
                ReservationsOfSelectedOnCalendar.Clear();
            }
        }

        protected override void Delete()
        {
            ViewModelLocator.Groups.StudentsOfSelectedGroup.Remove(SelectedItem);

            SelectedItem.Delete();
            Students.Remove(SelectedItem);
            SelectedItem = Students.FirstOrDefault();
        }

        public void ReservationClicked(IntPtr reservationptr)
        {
            MessageBox.Show(App.Reservations.Single(x => x.Ptr == reservationptr).ToString());
        }
    }
}
