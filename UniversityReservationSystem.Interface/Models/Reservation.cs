using System;
using System.Linq;
using System.Runtime.InteropServices;
using UniversityReservationSystem.Interface.Helpers;

namespace UniversityReservationSystem.Interface.Models
{
    public class Reservation : ISerializable
    {
        private Teacher _teacher;
        private IRoom _room;
        private Group _group;

        public Teacher Teacher
        {
            get { return _teacher; }
            private set
            {
                if (Equals(value, _teacher)) return;
                _teacher = value;
                OnPropertyChanged();
            }
        }
        public IRoom Room
        {
            get { return _room; }
            private set
            {
                if (Equals(value, _room)) return;
                _room = value;
                OnPropertyChanged();
            }
        }
        public Group Group
        {
            get { return _group; }
            private set
            {
                if (Equals(value, _group)) return;
                _group = value;
                OnPropertyChanged();
            }
        }
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

        public Reservation(IntPtr thisPtr) : base(thisPtr)
        {
            Teacher = App.Teachers.SingleOrDefault(x => x.Ptr == GetReservationTeacher(thisPtr));
            Room = App.Rooms.SingleOrDefault(x => x.Ptr == GetReservationRoom(thisPtr));
            Group = App.Groups.SingleOrDefault(x => x.Ptr == GetReservationGroup(thisPtr));
        }

        public Reservation(Teacher teacher, IRoom room, Group group)
            : base(FindSpaceForNewReservation(teacher, room, group))
        {
            Teacher = teacher;
            Room = room;
            Group = group;
        }

        private static IntPtr FindSpaceForNewReservation(Teacher teacher, IRoom room, Group group)
        {
            var start = DateTime.Now.Subtract(TimeSpan.FromMinutes(DateTime.Now.Minute)).AddHours(1);
            var end = start.AddHours(1);

            while (!CheckCollisionsBeforeAdding(start, end, teacher, room, group))
            {
                start += TimeSpan.FromHours(1);
                end += TimeSpan.FromHours(1);
            }

            return CreateNewReservation(
                "Type the name",
                start.ToUnixTimestamp(),
                end.ToUnixTimestamp(),
                teacher.Ptr,
                room.Ptr, group.Ptr);
        }

        private static bool CheckCollisionsBeforeAdding(DateTime dateOfStart, DateTime dateOfEnd, Teacher teacher, IRoom room, Group group)
        {
            return CheckCollisions(dateOfStart.ToUnixTimestamp(), dateOfEnd.ToUnixTimestamp(), teacher.Ptr, room.Ptr, group.Ptr);
        }

        public bool Edit(string name, DateTime dateOfStart, DateTime dateOfEnd, Teacher teacher, IRoom room, Group group)
        {
            if (EditReservation(Ptr, name, dateOfStart.ToUnixTimestamp(), dateOfEnd.ToUnixTimestamp(), teacher.Ptr, room.Ptr, group.Ptr))
            {
                Teacher = App.Teachers.SingleOrDefault(x => x.Ptr == GetReservationTeacher(Ptr));
                Room = App.Rooms.SingleOrDefault(x => x.Ptr == GetReservationRoom(Ptr));
                Group = App.Groups.SingleOrDefault(x => x.Ptr == GetReservationGroup(Ptr));

                OnPropertyChanged("Name");
                OnPropertyChanged("DateOfStart");
                OnPropertyChanged("DateOfEnd");
                InvokePropertyChanged();

                return true;
            }

            return false;
        }

        public void Delete()
        {
            DeleteReservation(Ptr);
        }

        public void InvokePropertyChanged()
        {
            OnPropertyChanged("Teacher");
            OnPropertyChanged("Room");
            OnPropertyChanged("Group");
        }

        public override string ToString()
        {
            return String.Format("##### Reservation Details #####\nName: {0}\nDate Of Start: {1}\nDate Of End: {2}\n\n## Teacher:\n{3}\n\n## Room:\n{4}\n\n## Group:\n{5}",
                Name, DateOfStart, DateOfEnd, Teacher, Room.FullInfo, Group);
        }

        #region InterOp Stuff

        [DllImport("UniversityReservationSystem.Backend.dll")] private static extern IntPtr GetReservationName(IntPtr reservPtr);
        [DllImport("UniversityReservationSystem.Backend.dll")] private static extern int GetReservationDateOfStart(IntPtr reservPtr);
        [DllImport("UniversityReservationSystem.Backend.dll")] private static extern int GetReservationDateOfEnd(IntPtr reservPtr);
        [DllImport("UniversityReservationSystem.Backend.dll")] private static extern IntPtr GetReservationTeacher(IntPtr reservPtr);
        [DllImport("UniversityReservationSystem.Backend.dll")] private static extern IntPtr GetReservationRoom(IntPtr reservPtr);
        [DllImport("UniversityReservationSystem.Backend.dll")] private static extern IntPtr GetReservationGroup(IntPtr reservPtr);
        [DllImport("UniversityReservationSystem.Backend.dll")] private static extern IntPtr CreateNewReservation(string name, int dateOfStart, int dateOfEnd, IntPtr teacherPtr, IntPtr roomPtr, IntPtr groupPtr);
        [DllImport("UniversityReservationSystem.Backend.dll")] [return: MarshalAs(UnmanagedType.I1)] private static extern bool CheckCollisions(int dateOfStart, int dateOfEnd, IntPtr teacherPtr, IntPtr roomPtr, IntPtr groupPtr);
        [DllImport("UniversityReservationSystem.Backend.dll")] [return: MarshalAs(UnmanagedType.I1)] private static extern bool EditReservation(IntPtr reservPtr, string name, int dateOfStart, int dateOfEnd, IntPtr teacherPtr, IntPtr roomPtr, IntPtr groupPtr);
        [DllImport("UniversityReservationSystem.Backend.dll")] private static extern void DeleteReservation(IntPtr reservPtr);

        #endregion
    }
}
