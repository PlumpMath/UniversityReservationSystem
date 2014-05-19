using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Runtime.InteropServices;

namespace UniversityReservationSystem.Interface.Models
{
    public abstract class IReservable : ISerializable
    {
        protected IReservable(IntPtr thisPtr) : base(thisPtr)
        {
        }

        public void GetReservations(ObservableCollection<Reservation> collection)
        {
            var count = GetReservationsOfReservableCount(Ptr);

            collection.Clear();

            for (uint i = 0; i < count; i++)
            {
                collection.Add(App.Reservations.First(x =>
                    x.Ptr == GetReservationOfReservableByIndex(Ptr, i)
                ));
            }
        }

        #region InterOp Stuff

        [DllImport("UniversityReservationSystem.dll")] private static extern uint GetReservationsOfReservableCount(IntPtr reservationPtr);
        [DllImport("UniversityReservationSystem.dll")] private static extern IntPtr GetReservationOfReservableByIndex(IntPtr reservationPtr, uint reservationIndex);

        #endregion
    }
}
