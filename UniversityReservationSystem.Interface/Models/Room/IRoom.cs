using System;
using System.Runtime.InteropServices;
using UniversityReservationSystem.Interface.ViewModels;

// ReSharper disable once CheckNamespace
namespace UniversityReservationSystem.Interface.Models
{
    public abstract class IRoom : IReservable
    {
        public string Name
        {
            get
            {
                return Marshal.PtrToStringAnsi(
                    GetRoomName(Ptr));
            }
        }
        public string Type
        {
            get
            {
                return Marshal.PtrToStringAnsi(
                    App.GetRoomType(Ptr));
            }

        }
        public int Capacity
        {
            get { return GetRoomCapacity(Ptr); }
        }
        public string AdditionalInfo { get { return ToString(); }}

        public IRoom(IntPtr thisPtr) : base(thisPtr) { }

        public void Delete()
        {
            DeleteRoom(Ptr);
        }

        public string FullInfo {
            get { return String.Format("{0} {1}\nCapacity: {2}\n{3}", Type, Name, Capacity, ToString()); }
        }

        #region InterOp Stuff

        [DllImport("UniversityReservationSystem.dll")] private static extern IntPtr GetRoomName(IntPtr roomPtr);
        [DllImport("UniversityReservationSystem.dll")] private static extern int GetRoomCapacity(IntPtr roomPtr);
        [DllImport("UniversityReservationSystem.dll")] private static extern void DeleteRoom(IntPtr roomPtr);

        #endregion
    }
}
