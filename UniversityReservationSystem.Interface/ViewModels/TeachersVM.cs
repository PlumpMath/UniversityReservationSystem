using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows;
using UniversityReservationSystem.Interface.Models;

namespace UniversityReservationSystem.Interface.ViewModels
{
    public class TeachersVM : IReservableViewModel<Teacher>
    {
        private string _firstName;
        private string _lastName;
        private string _phoneNumber;
        private string _email;
        private string _academicTitle;
        private bool _isFirstNameFocused;

        public ObservableCollection<Teacher> Teachers { get; set; }

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
        public string PhoneNumber
        {
            get { return _phoneNumber; }
            set
            {
                if (_phoneNumber != value)
                {
                    _phoneNumber = value;
                    RaisePropertyChanged("PhoneNumber");
                }
            }
        }
        public string Email
        {
            get { return _email; }
            set
            {
                if (_email != value)
                {
                    _email = value;
                    RaisePropertyChanged("Email");
                }
            }
        }
        public string AcademicTitle
        {
            get { return _academicTitle; }
            set
            {
                if (_academicTitle != value)
                {
                    _academicTitle = value;
                    RaisePropertyChanged("AcademicTitle");
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

        public TeachersVM()
        {
            if (IsInDesignMode) return;

            Teachers = App.Teachers;
            SelectedItem = Teachers.FirstOrDefault();
            ReservationsOfSelected = new ObservableCollection<Reservation>();

            UpdateAfterSelection(false);
        }


        protected override void Add()
        {
            var teacherToAdd = new Teacher(
                "Type first name", "Type last name",
                "Type email", "Type number",
                "dr");
            Teachers.Add(teacherToAdd);
            SelectedItem = Teachers.Last();
            IsFirstNameFocused = true;
        }

        protected override void SaveChanges()
        {
            SelectedItem.Edit(AcademicTitle, FirstName, LastName, PhoneNumber, Email);
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
                AcademicTitle = SelectedItem.AcademicTitle;
                FirstName = SelectedItem.FirstName;
                LastName = SelectedItem.LastName;
                Email = SelectedItem.Email;
                PhoneNumber = SelectedItem.PhoneNumber;
            }
            else
            {
                FirstName = String.Empty;
                LastName = String.Empty;
                Email = String.Empty;
                PhoneNumber = String.Empty;
                ReservationsOfSelected.Clear();
            }
        }

        protected override void Delete()
        {
            SelectedItem.Delete();
            Teachers.Remove(SelectedItem);
            SelectedItem = Teachers.LastOrDefault();

            ViewModelLocator.Groups.ReloadData();
            ViewModelLocator.Students.ReloadData();
            ViewModelLocator.Rooms.ReloadData();
        }

        public void ReservationClicked(IntPtr reservationptr)
        {
            MessageBox.Show(App.Reservations.Single(x => x.Ptr == reservationptr).ToString());
        }
    }
}
