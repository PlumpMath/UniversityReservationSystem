using System;
using System.Linq;
using System.Runtime.InteropServices;

// ReSharper disable once CheckNamespace
namespace UniversityReservationSystem.Interface.Models
{
    public class LabRoom : IRoom
    {
        public string AdditionalEquipment
        {
            get
            {
                return Marshal.PtrToStringAnsi(
                    GetLabRoomAdditionalEquipment(Ptr));
            }
        }
        public int NumOfComputers
        {
            get { return GetLabRoomNumOfComputers(Ptr); }
        }

        public LabRoom(IntPtr thisPtr) : base(thisPtr) { }

        public LabRoom(string name, int capacity, string additionalEquipment, int numOfComputers)
            : base(CreateNewLabRoom(name, capacity, additionalEquipment, numOfComputers)) { }

        public void Edit(string name, int capacity, string additionalEquipment, int numOfComputers)
        {
            EditLabRoom(Ptr, name, capacity, additionalEquipment, numOfComputers);

            OnPropertyChanged("Name");
            OnPropertyChanged("Capacity");
            OnPropertyChanged("AdditionalEquipment");
            OnPropertyChanged("NumOfComputers");
            OnPropertyChanged("AdditionalInfo");

            App.Reservations.Where(x => x.Room.Ptr == Ptr).ToList().ForEach(x => x.InvokePropertyChanged());
        }

        public override string ToString()
        {
            return String.Format("Number of computers: {0}\nAdditional equipment: {1}",
                NumOfComputers, AdditionalEquipment);
        }

        #region InterOp Stuff

        [DllImport("UniversityReservationSystem.dll")] private static extern IntPtr GetLabRoomAdditionalEquipment(IntPtr labRoomPtr);
        [DllImport("UniversityReservationSystem.dll")] private static extern int GetLabRoomNumOfComputers(IntPtr labRoomPtr);
        [DllImport("UniversityReservationSystem.dll")] private static extern IntPtr CreateNewLabRoom(string name, int capacity, string additionalEquipment, int numOfComputers);
        [DllImport("UniversityReservationSystem.dll")] private static extern void EditLabRoom(IntPtr labRoomPtr, string name, int capacity, string additionalEquipment, int numOfComputers);

        #endregion
    }
}
