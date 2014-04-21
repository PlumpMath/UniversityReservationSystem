using System;
using System.Runtime.InteropServices;

// ReSharper disable once CheckNamespace
namespace UniversityReservationSystem.Interface.Models
{
    public class Teacher : IPerson
    {
        public string Email
        {
            get
            {
                return Marshal.PtrToStringAnsi(
                    GetTeacherEmail(Ptr));
            }
        }
        public string PhoneNumber
        {
            get
            {
                return Marshal.PtrToStringAnsi(
                    GetTeacherPhoneNumber(Ptr));
            }
        }
        public string AcademicTitle
        {
            get
            {
                return Marshal.PtrToStringAnsi(
                    GetTeacherAcademicTitle(Ptr));
            }
        }

        public Teacher(IntPtr thisPtr) : base(thisPtr) { }

        public Teacher(string firstName, string lastName, string email, string phoneNumber, string academicTitle)
            : base(CreateNewTeacher(firstName, lastName, email, phoneNumber, academicTitle)) { }

        public override string ToString()
        {
            return String.Format("ID: {0}, FirstName: {1}, LastName: {2}, Email: {3}, PhoneNumber: {4}, AcademicTitle: {5}",
                Id, FirstName, LastName, Email, PhoneNumber, AcademicTitle);
        }

        #region InterOp Stuff

        [DllImport("UniversityReservationSystem.dll")]
        private static extern IntPtr GetTeacherEmail(IntPtr teacherPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern IntPtr GetTeacherPhoneNumber(IntPtr teacherPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern IntPtr GetTeacherAcademicTitle(IntPtr teacherPtr);

        [DllImport("UniversityReservationSystem.dll")]
        private static extern IntPtr CreateNewTeacher(
            string firstName, string lastName, string email,
            string phoneNumber, string academicTitle);

        #endregion
    }
}
