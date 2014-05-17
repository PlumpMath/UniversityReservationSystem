using System;
using System.Linq;
using System.Runtime.InteropServices;
using UniversityReservationSystem.Interface.Helpers;

namespace UniversityReservationSystem.Interface.Models
{
    public class Reservation : ISerializable
    {
        public Teacher Teacher { get; private set; }
        public IRoom Room { get; private set; }
        public Group Group { get; private set; }
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
        //public uint GroupsCount
        //{
        //    get { return GetReservationGroupsCount(Ptr); }
        //}

        public Reservation(IntPtr thisPtr) : base(thisPtr)
        {
            Teacher = App.Teachers.SingleOrDefault(x => x.Ptr == GetReservationTeacher(thisPtr));
            Room = App.Rooms.SingleOrDefault(x => x.Ptr == GetReservationRoom(thisPtr));
            Group = App.Groups.SingleOrDefault(x => x.Ptr == GetReservationGroup(thisPtr));
        }

        public Reservation(string name, DateTime dateOfStart, DateTime dateOfEnd, Teacher teacher, IRoom room, Group group)
            : base(CreateNewReservation(name, dateOfStart.ToUnixTimestamp(), dateOfEnd.ToUnixTimestamp(), teacher.Ptr, room.Ptr, group.Ptr))
        {
            Teacher = teacher;
            Room = room;
            Group = group;
        }

        public static bool CheckCollisionsBeforeAdding(DateTime dateOfStart, DateTime dateOfEnd, Teacher teacher, IRoom room, Group group)
        {
            return CheckCollisions(dateOfStart.ToUnixTimestamp(), dateOfEnd.ToUnixTimestamp(), teacher.Ptr, room.Ptr, group.Ptr);
        }

        public bool Edit(string name, DateTime dateOfStart, DateTime dateOfEnd, Teacher teacher, IRoom room, Group group)
        {
            if (EditReservation(Ptr, name, dateOfStart.ToUnixTimestamp(), dateOfEnd.ToUnixTimestamp(), Teacher.Ptr, Room.Ptr, Group.Ptr))
            {
                Teacher = App.Teachers.SingleOrDefault(x => x.Ptr == GetReservationTeacher(Ptr));
                Room = App.Rooms.SingleOrDefault(x => x.Ptr == GetReservationRoom(Ptr));
                Group = App.Groups.SingleOrDefault(x => x.Ptr == GetReservationGroup(Ptr));

                OnPropertyChanged("Teacher");
                OnPropertyChanged("Room");
                OnPropertyChanged("Group");
                OnPropertyChanged("Name");
                OnPropertyChanged("DateOfStart");
                OnPropertyChanged("DateOfEnd");

                return true;
            }

            return false;
        }

        public void Delete()
        {
            DeleteReservation(Ptr);
        }

        public override string ToString()
        {
            return String.Format("ID: {0}, Name: {1}, DateOfStart: {2}, DateOfEnd: {3}",
                Id, Name, DateOfStart, DateOfEnd);
        }

        #region InterOp Stuff

        [DllImport("UniversityReservationSystem.dll")]
        private static extern IntPtr GetReservationName(IntPtr reservPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern int GetReservationDateOfStart(IntPtr reservPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern int GetReservationDateOfEnd(IntPtr reservPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern IntPtr GetReservationTeacher(IntPtr reservPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern IntPtr GetReservationRoom(IntPtr reservPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern uint GetReservationGroupsCount(IntPtr reservPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern IntPtr GetReservationGroup(IntPtr reservPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern IntPtr CreateNewReservation(
            string name, long dateOfStart, long dateOfEnd,
            IntPtr teacherPtr, IntPtr roomPtr, IntPtr groupPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern bool CheckCollisions( long dateOfStart,
            long dateOfEnd, IntPtr teacherPtr, IntPtr roomPtr, IntPtr groupPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern bool EditReservation(IntPtr reservPtr, 
            string name, long dateOfStart, long dateOfEnd,
            IntPtr teacherPtr, IntPtr roomPtr, IntPtr groupPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern void DeleteReservation(IntPtr reservPtr);

        #endregion
    }
}
