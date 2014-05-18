using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Runtime.InteropServices;

namespace UniversityReservationSystem.Interface.Models
{
    public class Group : IReservable
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
        public int GroupNumber
        {
            get { return GetGroupNumber(Ptr); }
        }
        public uint NumOfStudents
        {
            get { return GetGroupStudentsCount(Ptr); }
        }

        public string Info { get { return DegreeCourse + " " + Year; } }
        public string ExInfo { get { return DegreeCourse + " " + Year + " Group: " + GroupNumber; } }
        public Group(IntPtr thisPtr) : base(thisPtr) { }

        public Group(string degreeCourse, int year, int groupNumber)
            : base(CreateNewGroup(degreeCourse, year, groupNumber)) { }

        public void Edit(int year, string degreeCourse, int groupNumber)
        {
            EditGroup(Ptr, degreeCourse, year, groupNumber);
            OnPropertyChanged("DegreeCourse");
            OnPropertyChanged("GroupNumber");
            OnPropertyChanged("Year");
        }

        public void GetStudents(ObservableCollection<Student> collection)
        {
            var ptr = GetArrayOfPointersOnStudents(Ptr);
            var count = GetGroupStudentsCount(Ptr);

            var studentsOfGroup = new IntPtr[count];
            Marshal.Copy(ptr, studentsOfGroup, 0, (int)count);

            collection.Clear();

            foreach (var studentPtr in studentsOfGroup)
            {
                collection.Add(App.Students.First(x => x.Ptr == studentPtr));
            }

            FreeArrayOfPointersOnStudents(ptr);
        }

        public void Delete()
        {
            DeleteGroup(Ptr);
        }

        public override string ToString()
        {
            return String.Format("ID: {0}, DegreeCourse: {1}, Year: {2}, GroupNumber: {3}, NumOfStudents: {4}",
                Id, DegreeCourse, Year, GroupNumber, NumOfStudents);
        }

        #region InterOp Stuff

        [DllImport("UniversityReservationSystem.dll")] private static extern IntPtr GetGroupDegreeCourse(IntPtr groupPtr);
        [DllImport("UniversityReservationSystem.dll")] private static extern int GetGroupYear(IntPtr groupPtr);
        [DllImport("UniversityReservationSystem.dll")] private static extern int GetGroupNumber(IntPtr groupPtr);
        [DllImport("UniversityReservationSystem.dll")] private static extern uint GetGroupStudentsCount(IntPtr groupPtr);
        [DllImport("UniversityReservationSystem.dll")] private static extern IntPtr CreateNewGroup(string degreeCourse, int year, int groupNumber);
        [DllImport("UniversityReservationSystem.dll")] private static extern void EditGroup(IntPtr groupPtr, string degreeCourse, int year, int groupNumber);
        [DllImport("UniversityReservationSystem.dll")] private static extern void DeleteGroup(IntPtr groupPtr);
        [DllImport("UniversityReservationSystem.dll")] private static extern uint FreeArrayOfPointersOnStudents(IntPtr groupPtr);
        [DllImport("UniversityReservationSystem.dll")] private static extern IntPtr GetArrayOfPointersOnStudents(IntPtr groupPtr);

        #endregion
    }
}