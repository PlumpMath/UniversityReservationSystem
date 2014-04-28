using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Windows;
using GalaSoft.MvvmLight;
using GalaSoft.MvvmLight.Command;
using UniversityReservationSystem.Interface.Models;

namespace UniversityReservationSystem.Interface.ViewModels
{
    public class GroupsVM : IViewModel<Group>
    {
        private int _year;
        private string _degreeCourse;
        private int _groupNumber;
        private Group _selectedItem;
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
        public Group SelectedItem
        {
            get { return _selectedItem; }
            set
            {
                if (_selectedItem != value)
                {
                    _selectedItem = value;

                    UpdateAfterSelection();

                    RaisePropertyChanged("SelectedItem");
                }
            }
        }

        private void UpdateAfterSelection()
        {
            Year = _selectedItem.Year;
            DegreeCourse = _selectedItem.DegreeCourse;
            GroupNumber = _selectedItem.GroupNumber;
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
            InitializeCommands();
            Groups = new ObservableCollection<Group>();

            if (IsInDesignMode) return;

            for (uint i = 0; i < App.GetGroupsCount(); i++)
            {
                Groups.Add(new Group(App.GetGroupByIndex(i)));
            }
            SelectedItem = Groups.FirstOrDefault();
        }

        private void Add()
        {
            var groupToAdd = new Group(
                "Type here the desired degree course name",
                DateTime.Today.Year, 1);
            Groups.Add(groupToAdd);
            SelectedItem = Groups.Last();
            IsDegreeFocused = true;
        }

        private void SaveChanges()
        {
            SelectedItem.Edit(Year, DegreeCourse, GroupNumber);
        }

        #region Relay Commands

        public RelayCommand AddGroupCommand { get; private set; }
        public RelayCommand SaveChangesCommand { get; private set; }

        private void InitializeCommands()
        {
            AddGroupCommand = new RelayCommand(Add);
            SaveChangesCommand = new RelayCommand(SaveChanges);
        }

        #endregion
    }
}
