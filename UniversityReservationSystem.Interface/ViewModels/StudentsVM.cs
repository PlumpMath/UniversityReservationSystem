using System;
using System.Collections.ObjectModel;
using System.Linq;
using UniversityReservationSystem.Interface.Models;

namespace UniversityReservationSystem.Interface.ViewModels
{
    public class StudentsVM : IViewModel<Student>
    {
        public ObservableCollection<Student> Students { get; set; }


        public StudentsVM()
        {
            if (IsInDesignMode) return;

            Students = App.Students;
            SelectedItem = Students.FirstOrDefault();
        }


        protected override void Add()
        {
            //var studentToAdd = new Student(
            //    "Type here the desired degree course name",
            //    DateTime.Today.Year, 1);
            //Students.Add(studentToAdd);
            //SelectedItem = Students.Last();
            //IsDegreeFocused = true;
        }

        protected override void SaveChanges()
        {
            //SelectedItem.Edit(Year, DegreeCourse, GroupNumber);
        }

        protected override void UpdateAfterSelection(bool isNull)
        {
            //if (!isNull)
            //{
            //    Year = SelectedItem.Year;
            //    DegreeCourse = SelectedItem.DegreeCourse;
            //    GroupNumber = SelectedItem.GroupNumber;
            //}
            //else
            //{
            //    Year = 0;
            //    DegreeCourse = String.Empty;
            //    GroupNumber = 0;
            //}
        }

        protected override void Delete()
        {
            //SelectedItem.Delete();
            //Groups.Remove(SelectedItem);
            //SelectedItem = Groups.LastOrDefault();
        }
    }
}
