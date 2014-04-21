using System;
using System.Runtime.InteropServices;
// ReSharper disable once CheckNamespace


namespace UniversityReservationSystem.Interface.Models
{
    public abstract class IRoom : ISerializable
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

        protected IRoom(IntPtr thisPtr) : base(thisPtr) { }

        #region InterOp Stuff

        [DllImport("UniversityReservationSystem.dll")]
        private static extern IntPtr GetRoomName(IntPtr roomPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern int GetRoomCapacity(IntPtr roomPtr);

        #endregion
    }
}
