using System;
using System.Linq;
using System.Runtime.InteropServices;
using UniversityReservationSystem.Interface.ViewModels;
using UniversityReservationSystem.Interface.Views;

// ReSharper disable once CheckNamespace
namespace UniversityReservationSystem.Interface.Models
{
    public class Student : IPerson
    {
        public Group Group { get; private set; }
        public int PassedTerms
        {
            get { return GetStudentPassedTerms(Ptr); }
        }
        public double AvgOfMarks
        {
            get { return GetStudentAvgOfMarks(Ptr); }
        }

        public Student(IntPtr thisPtr) : base(thisPtr)
        {
            Group = App.Groups.SingleOrDefault(x => x.Ptr == GetStudentGroup(thisPtr));
        }

        public Student(string firstName, string lastName, Group group, int passedTerms, double avgOfMarks)
            : base(CreateNewStudent(firstName, lastName, group.Ptr, passedTerms, avgOfMarks))
        {
            Group = group;
        }

        public void Edit(string firstName, string lastName, Group group, int passedTerms, double avgOfMarks)
        {
            EditStudent(Ptr, firstName, lastName, group.Ptr, passedTerms, avgOfMarks);
            Group = App.Groups.SingleOrDefault(x => x.Ptr == GetStudentGroup(Ptr));

            OnPropertyChanged("FirstName");
            OnPropertyChanged("LastName");
            OnPropertyChanged("PassedTerms");
            OnPropertyChanged("AvgOfMarks");

            ViewModelLocator.Students.ReloadData();
            ViewModelLocator.Groups.ReloadData();
            InvokePropertyChanged();
        }

        public void Delete()
        {
            DeleteStudent(Ptr);

            ViewModelLocator.Students.ReloadData();
            ViewModelLocator.Groups.ReloadData();
            InvokePropertyChanged();
        }

        public override string ToString()
        {
            return String.Format("{0} {1}\nPassedTerms: {2}\nAvgOfMarks: {3}",
                FirstName, LastName, PassedTerms, AvgOfMarks);
        }

        #region InterOp Stuff

        [DllImport("UniversityReservationSystem.dll")] private static extern IntPtr GetStudentGroup(IntPtr studentPtr);
        [DllImport("UniversityReservationSystem.dll")] private static extern int GetStudentPassedTerms(IntPtr studentPtr);
        [DllImport("UniversityReservationSystem.dll")] private static extern double GetStudentAvgOfMarks(IntPtr studentPtr);
        [DllImport("UniversityReservationSystem.dll")] private static extern IntPtr CreateNewStudent(string firstName, string lastName, IntPtr groupPtr, int passedTerms, double avgOfMarks);
        [DllImport("UniversityReservationSystem.dll")] private static extern void EditStudent(IntPtr studentPtr, string firstName, string lastName, IntPtr groupPtr, int passedTerms, double avgOfMarks);
        [DllImport("UniversityReservationSystem.dll")] private static extern void DeleteStudent(IntPtr studentPtr);

        #endregion

        public void InvokePropertyChanged()
        {
            OnPropertyChanged("Group");
        }
    }
}
