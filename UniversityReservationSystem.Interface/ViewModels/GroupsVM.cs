using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows;
using GalaSoft.MvvmLight.Command;
using GalaSoft.MvvmLight.Messaging;
using UniversityReservationSystem.Interface.Models;

namespace UniversityReservationSystem.Interface.ViewModels
{
    public class GroupsVM : IViewModel<Group>
    {
        private int _year;
        private string _degreeCourse;
        private int _groupNumber;
        private bool _isDegreeFocused;

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
        public ObservableCollection<Group> Groups { get; set; }
        public RelayCommand<IntPtr> ShowStudentsOfGroupCommand { get; private set; }

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
            Groups = new ObservableCollection<Group>();

            if (IsInDesignMode) return;

            for (uint i = 0; i < App.GetGroupsCount(); i++)
            {
                Groups.Add(new Group(App.GetGroupByIndex(i)));
            }
            SelectedItem = Groups.FirstOrDefault();

            ShowStudentsOfGroupCommand = new RelayCommand<IntPtr>(ShowStudentsOfGroup);
        }

        private void ShowStudentsOfGroup(IntPtr ptr)
        {
            MessageBox.Show(ptr.ToString());
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

        protected override void UpdateAfterSelection(bool isNull)
        {
            if (!isNull)
            {
                Year = SelectedItem.Year;
                DegreeCourse = SelectedItem.DegreeCourse;
                GroupNumber = SelectedItem.GroupNumber;
            }
            else
            {
                Year = 0;
                DegreeCourse = String.Empty;
                GroupNumber = 0;
            }
        }

        protected override void Delete()
        {
            SelectedItem.Delete();
            Groups.Remove(SelectedItem);
            SelectedItem = Groups.LastOrDefault();
        }
    }
}
