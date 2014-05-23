using System;
using System.Collections.ObjectModel;
using System.IO;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Navigation;
using UniversityReservationSystem.Interface.Models;

namespace UniversityReservationSystem.Interface
{
    public partial class App
    {
        private const string SAVE_PATH = "home";
        private readonly bool _dbExists;

        public static ObservableCollection<Group> Groups { get; private set; }
        public static ObservableCollection<Student> Students { get; private set; }
        public static ObservableCollection<Teacher> Teachers { get; private set; }
        public static ObservableCollection<IRoom> Rooms { get; private set; }
        public static ObservableCollection<Reservation> Reservations { get; private set; }

        protected override void OnStartup(StartupEventArgs e)
        {
            if (!_dbExists) MessageBox.Show("No base files detected. They'll be created after you exit the program!");
            base.OnStartup(e);
        }

        public App()
        {
            _dbExists = LoadDB(SAVE_PATH);
                
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
                IntPtr currentRoom = GetRoomByIndex(i);
                if (Marshal.PtrToStringAnsi(GetRoomType(currentRoom)) == "Lab")
                    Rooms.Add(new LabRoom(currentRoom));
                else
                    Rooms.Add(new ExerciseRoom(currentRoom));
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
            Directory.CreateDirectory(SAVE_PATH);

            // Saving the base to files
            if (MessageBox.Show("Do you want to save changes?", "Saving changes", MessageBoxButton.YesNo, MessageBoxImage.Question) == MessageBoxResult.Yes)
            {
                if (!SaveDB())
                    MessageBox.Show("There was errors during the process of saving the base!", "Error",
                        MessageBoxButton.OK, MessageBoxImage.Error);
            }

            // Freeing the reservated memory in the DLL
            FreeDB();

            base.OnExit(e);
        }

        #region InterOp Stuff
        [DllImport("UniversityReservationSystem.Backend.dll")] [return: MarshalAs(UnmanagedType.I1)] private static extern bool LoadDB(string filePath);
        [DllImport("UniversityReservationSystem.Backend.dll")] [return: MarshalAs(UnmanagedType.I1)] private static extern bool SaveDB();
        [DllImport("UniversityReservationSystem.Backend.dll")] private static extern void FreeDB();

        [DllImport("UniversityReservationSystem.Backend.dll")] private static extern IntPtr GetGroupByIndex(uint groupIndex);
        [DllImport("UniversityReservationSystem.Backend.dll")] private static extern IntPtr GetStudentByIndex(uint studentIndex);
        [DllImport("UniversityReservationSystem.Backend.dll")] private static extern IntPtr GetTeacherByIndex(uint teacherIndex);
        [DllImport("UniversityReservationSystem.Backend.dll")] private static extern IntPtr GetRoomByIndex(uint roomIndex);
        [DllImport("UniversityReservationSystem.Backend.dll")] private static extern IntPtr GetReservationByIndex(uint reservationIndex);

        [DllImport("UniversityReservationSystem.Backend.dll")] private static extern uint GetGroupsCount();
        [DllImport("UniversityReservationSystem.Backend.dll")] private static extern uint GetStudentsCount();
        [DllImport("UniversityReservationSystem.Backend.dll")] private static extern uint GetTeachersCount();
        [DllImport("UniversityReservationSystem.Backend.dll")] private static extern uint GetRoomsCount();
        [DllImport("UniversityReservationSystem.Backend.dll")] private static extern uint GetReservationsCount();

        [DllImport("UniversityReservationSystem.Backend.dll")] public static extern IntPtr GetRoomType(IntPtr roomPtr);
        #endregion
    }
}
