using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Windows;
using GalaSoft.MvvmLight;
using GalaSoft.MvvmLight.Command;
using UniversityReservationSystem.Interface.Models;

namespace UniversityReservationSystem.Interface.ViewModels
{
    public class GroupsVM : ViewModelBase
    {
        private int _year;
        private string _degreeCourse;
        private int _groupNumber;

        public ObservableCollection<Group> Groups { get; set; }
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

            Year = DateTime.Today.Year;
            DegreeCourse = "Type here the desired degree course";
            GroupNumber = 1;

            if (IsInDesignMode) return;

            for (uint i = 0; i < App.GetGroupsCount(); i++)
            {
                Groups.Add(new Group(App.GetGroupByIndex(i)));
            }
        }

        private void Add()
        {
            Groups.Add(new Group(DegreeCourse, Year, GroupNumber));
        }

        #region Relay Commands

        public RelayCommand AddGroupCommand { get; private set; }

        private void InitializeCommands()
        {
            AddGroupCommand = new RelayCommand(Add);
        }

        #endregion
    }
}
