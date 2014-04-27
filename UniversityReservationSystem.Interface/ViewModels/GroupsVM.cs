using System.Collections.ObjectModel;
using GalaSoft.MvvmLight;
using UniversityReservationSystem.Interface.Models;

namespace UniversityReservationSystem.Interface.ViewModels
{
    public class GroupsVM : ViewModelBase
    {
        public ObservableCollection<Group> Groups { get; set; }

        public GroupsVM()
        {
            Groups = new ObservableCollection<Group>();
            if (IsInDesignMode) return;

            App.LoadDB("home");
            for (uint i = 0; i < App.GetGroupsCount(); i++)
            {
                Groups.Add(new Group(App.GetGroupByIndex(i)));
            }

            //App.SaveDB();
        }
    }
}
