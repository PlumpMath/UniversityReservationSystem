using System;
using UniversityReservationSystem.Interface.Models;

namespace UniversityReservationSystem.Interface.ViewModels
{
    public class RoomsVM : IReservableViewModel<IRoom>
    {
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
            throw new System.NotImplementedException();
        }

        public void ReservationClicked(IntPtr reservationptr)
        {
            throw new NotImplementedException();
        }
    }
}
