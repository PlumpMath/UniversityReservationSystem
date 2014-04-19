using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace UniversityReservationSystem.Interface.Models
{
    public class Student : ISerializable
    {
        public string FirstName
        {
            get
            {
                return Marshal.PtrToStringAnsi(
                    GetStudentFirstName(Ptr));
            }
        }
        public string LastName
        {
            get
            {
                return Marshal.PtrToStringAnsi(
                    GetStudentLastName(Ptr));
            }
        }
        public int PassedTerms
        {
            get { return GetStudentPassedTerms(Ptr); }
        }
        public double AvgOfMarks
        {
            get { return GetStudentAvgOfMarks(Ptr); }
        }

        public Student(IntPtr thisPtr) : base(thisPtr) { }

        public Student(string firstName, string lastName, Group group, int passedTerms, double avgOfMarks)
            : base(CreateNewStudent(firstName, lastName, group.Ptr, passedTerms, avgOfMarks)) { }

        public override string ToString()
        {
            return String.Format("ID: {0}, FirstName: {1}, LastName: {2}, PassedTerms: {3}, AvgOfMarks: {4}",
                Id, FirstName, LastName, PassedTerms, AvgOfMarks);
        }

        #region InterOp Stuff

        [DllImport("UniversityReservationSystem.dll")]
        private static extern IntPtr GetStudentGroup(IntPtr studentPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern int GetStudentPassedTerms(IntPtr studentPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern double GetStudentAvgOfMarks(IntPtr studentPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern IntPtr GetStudentFirstName(IntPtr studentPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern IntPtr GetStudentLastName(IntPtr studentPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern IntPtr CreateNewStudent(
            string firstName, string lastName, IntPtr groupPtr,
            int passedTerms, double avgOfMarks);

        #endregion
    }
}
