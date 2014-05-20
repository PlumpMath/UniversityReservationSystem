using System;
using System.Linq;
using System.Runtime.InteropServices;
using UniversityReservationSystem.Interface.ViewModels;

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

        public override string FullName
        {
            get { return AcademicTitle + " " + base.FullName; }
        }

        public Teacher(IntPtr thisPtr) : base(thisPtr) { }

        public Teacher(string firstName, string lastName, string email, string phoneNumber, string academicTitle)
            : base(CreateNewTeacher(firstName, lastName, email, phoneNumber, academicTitle)) { }

        public void Edit(string academicTitle, string firstName, string lastName, string phoneNumber, string email)
        {
            EditTeacher(Ptr, academicTitle, firstName, lastName, phoneNumber, email);

            OnPropertyChanged("AcademicTitle");
            OnPropertyChanged("FirstName");
            OnPropertyChanged("LastName");
            OnPropertyChanged("PhoneNumber");
            OnPropertyChanged("Email");

            App.Reservations.Where(x => x.Teacher.Ptr == Ptr).ToList().ForEach(x => x.InvokePropertyChanged());
        }

        public void Delete()
        {
            DeleteTeacher(Ptr);
        }

        public override string ToString()
        {
            return String.Format("{0} {1} {2}\nEmail: {3}\nPhoneNumber: {4}",
                AcademicTitle, FirstName, LastName, Email, PhoneNumber);
        }

        #region InterOp Stuff

        [DllImport("UniversityReservationSystem.dll")] private static extern IntPtr GetTeacherEmail(IntPtr teacherPtr);
        [DllImport("UniversityReservationSystem.dll")] private static extern IntPtr GetTeacherPhoneNumber(IntPtr teacherPtr);
        [DllImport("UniversityReservationSystem.dll")] private static extern IntPtr GetTeacherAcademicTitle(IntPtr teacherPtr);
        [DllImport("UniversityReservationSystem.dll")] private static extern IntPtr CreateNewTeacher(string firstName, string lastName, string email, string phoneNumber, string academicTitle);
        [DllImport("UniversityReservationSystem.dll")] private static extern void EditTeacher(IntPtr studentPtr, string academicTitle, string firstName, string LastName, string phoneNumber, string email);
        [DllImport("UniversityReservationSystem.dll")] private static extern void DeleteTeacher(IntPtr teacherPtr);

        #endregion
    }
}
