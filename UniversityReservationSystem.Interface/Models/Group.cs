using System;
using System.Runtime.InteropServices;

namespace UniversityReservationSystem.Interface.Models
{
    public class Group : ISerializable
    {
        public string DegreeCourse
        {
            get
            {
                return Marshal.PtrToStringAnsi(
                    GetGroupDegreeCourse(Ptr));
            }
        }
        public int Year
        {
            get { return GetGroupYear(Ptr); }
        }
        public int GroupsCount
        {
            get { return GetGroupNumber(Ptr); }
        }
        public uint NumOfStudents
        {
            get { return GetGroupStudentsCount(Ptr); }
        }

        public Group(IntPtr thisPtr) : base(thisPtr) { }

        public Group(string degreeCourse, int year, int groupNumber)
            : base(CreateNewGroup(degreeCourse, year, groupNumber)) { }

        public override string ToString()
        {
            return String.Format("ID: {0}, DegreeCourse: {1}, Year: {2}, GroupNumber: {3}, NumOfStudents: {4}",
                Id, DegreeCourse, Year, GroupsCount, NumOfStudents);
        }

        #region InterOp Stuff

        [DllImport("UniversityReservationSystem.dll")]
        private static extern IntPtr GetGroupDegreeCourse(IntPtr groupPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern int GetGroupYear(IntPtr groupPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern int GetGroupNumber(IntPtr groupPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern uint GetGroupStudentsCount(IntPtr groupPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern IntPtr CreateNewGroup(string degreeCourse, int year, int groupNumber);

        #endregion
    }
}