using System;
using System.Runtime.InteropServices;

// ReSharper disable once CheckNamespace
namespace UniversityReservationSystem.Interface.Models
{
    public class IRoom : IReservable
    {
        public string Name
        {
            get
            {
                return Marshal.PtrToStringAnsi(
                    GetRoomName(Ptr));
            }
        }
        public int Capacity
        {
            get { return GetRoomCapacity(Ptr); }
        }

        public IRoom(IntPtr thisPtr) : base(thisPtr) { }

        public override string ToString()
        {
            return String.Format("ID: {0}, Name: {1}, Capacity: {2}", Id, Name, Capacity);
        }

        #region InterOp Stuff

        [DllImport("UniversityReservationSystem.dll")] private static extern IntPtr GetRoomName(IntPtr roomPtr);
        [DllImport("UniversityReservationSystem.dll")] private static extern int GetRoomCapacity(IntPtr roomPtr);

        #endregion
    }
}
