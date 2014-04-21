using System;
using System.Runtime.InteropServices;
using UniversityReservationSystem.Interface.Helpers;

namespace UniversityReservationSystem.Interface.Models
{
    public class Reservation : ISerializable
    {
        public string Name
        {
            get
            {
                return Marshal.PtrToStringAnsi(
                    GetReservationName(Ptr));
            }
        }
        public DateTime DateOfStart
        {
            get
            {
                return GetReservationDateOfStart(Ptr).ToDateTime();
            }
        }
        public DateTime DateOfEnd
        {
            get
            {
                return GetReservationDateOfEnd(Ptr).ToDateTime();
            }
        }
        public uint GroupsCount
        {
            get { return GetReservationGroupsCount(Ptr); }
        }

        public Reservation(IntPtr thisPtr) : base(thisPtr) { }

        public Reservation(string name, DateTime dateOfStart, DateTime dateOfEnd, Teacher teacher, IRoom room)
            : base(CreateNewReservation(name, dateOfStart.ToUnixTimestamp(), dateOfEnd.ToUnixTimestamp(), teacher.Ptr, room.Ptr)) { }

        public override string ToString()
        {
            return String.Format("ID: {0}, Name: {1}, DateOfStart: {2}, DateOfEnd: {3}, GroupsCount: {4}",
                Id, Name, DateOfStart, DateOfEnd, GroupsCount);
        }

        #region InterOp Stuff

        [DllImport("UniversityReservationSystem.dll")]
        private static extern IntPtr GetReservationName(IntPtr reservPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern long GetReservationDateOfStart(IntPtr reservPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern long GetReservationDateOfEnd(IntPtr reservPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern IntPtr GetReservationTeacher(IntPtr reservPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern IntPtr GetReservationRoom(IntPtr reservPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern uint GetReservationGroupsCount(IntPtr reservPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern IntPtr CreateNewReservation(
            string name, long dateOfStart, long dateOfEnd,
            IntPtr teacherPtr, IntPtr roomPtr);

        #endregion
    }
}
