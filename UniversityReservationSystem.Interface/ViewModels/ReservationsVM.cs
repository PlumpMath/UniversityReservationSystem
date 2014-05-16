using System.Collections.ObjectModel;
using GalaSoft.MvvmLight;
using UniversityReservationSystem.Interface.Models;

namespace UniversityReservationSystem.Interface.ViewModels
{
    public class ReservationsVM : ViewModelBase
    {
        public ObservableCollection<Group> Groups { get; set; }
        public ObservableCollection<IRoom> Rooms { get; set; }
        public ObservableCollection<Teacher> Teachers { get; set; }
        public ObservableCollection<Reservation> Reservations { get; set; }

        public ReservationsVM()
        {
            if (IsInDesignMode) return;

            Groups = App.Groups;
            Rooms = App.Rooms;
            Teachers = App.Teachers;
            Reservations = App.Reservations;
        }
    }
}
