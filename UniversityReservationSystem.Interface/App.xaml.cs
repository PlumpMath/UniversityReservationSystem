using System;
using System.Collections.ObjectModel;
using System.Runtime.InteropServices;
using System.Windows;
using UniversityReservationSystem.Interface.Models;

namespace UniversityReservationSystem.Interface
{
    public partial class App
    {
        public static ObservableCollection<Group> Groups { get; private set; }
        public static ObservableCollection<Student> Students { get; private set; }
        public static ObservableCollection<Teacher> Teachers { get; private set; }
        public static ObservableCollection<IRoom> Rooms { get; private set; }
        public static ObservableCollection<Reservation> Reservations { get; private set; }

        [DllImport("UniversityReservationSystem.dll")] private static extern bool LoadDB(string filePath);
        [DllImport("UniversityReservationSystem.dll")] private static extern bool SaveDB();
        [DllImport("UniversityReservationSystem.dll")] private static extern bool FreeDB();

        [DllImport("UniversityReservationSystem.dll")] private static extern IntPtr GetGroupByIndex(uint groupIndex);
        [DllImport("UniversityReservationSystem.dll")] private static extern IntPtr GetStudentByIndex(uint studentIndex);
        [DllImport("UniversityReservationSystem.dll")] private static extern IntPtr GetTeacherByIndex(uint teacherIndex);
        [DllImport("UniversityReservationSystem.dll")] private static extern IntPtr GetRoomByIndex(uint roomIndex);
        [DllImport("UniversityReservationSystem.dll")] private static extern IntPtr GetReservationByIndex(uint reservationIndex);

        [DllImport("UniversityReservationSystem.dll")] private static extern uint GetGroupsCount();
        [DllImport("UniversityReservationSystem.dll")] private static extern uint GetStudentsCount();
        [DllImport("UniversityReservationSystem.dll")] private static extern uint GetTeachersCount();
        [DllImport("UniversityReservationSystem.dll")] private static extern uint GetRoomsCount();
        [DllImport("UniversityReservationSystem.dll")] private static extern uint GetReservationsCount();

        public App()
        {
            LoadDB("home");

            uint n = GetGroupsCount();
            Groups = new ObservableCollection<Group>();
            for (uint i = 0; i < n; i++)
            {
                Groups.Add(new Group(GetGroupByIndex(i)));
            }

            n = GetStudentsCount();
            Students = new ObservableCollection<Student>();
            for (uint i = 0; i < n; i++)
            {
                Students.Add(new Student(GetStudentByIndex(i)));
            }

            n = GetTeachersCount();
            Teachers = new ObservableCollection<Teacher>();
            for (uint i = 0; i < n; i++)
            {
                Teachers.Add(new Teacher(GetTeacherByIndex(i)));
            }

            n = GetRoomsCount();
            Rooms = new ObservableCollection<IRoom>();
            for (uint i = 0; i < n; i++)
            {
                Rooms.Add(new IRoom(GetRoomByIndex(i)));
            }

            n = GetReservationsCount();
            Reservations = new ObservableCollection<Reservation>();
            for (uint i = 0; i < n; i++)
            {
                Reservations.Add(new Reservation(GetReservationByIndex(i)));
            }
        }

        protected override void OnExit(ExitEventArgs e)
        {
            FreeDB();
            base.OnExit(e);
        }
    }
}
