using System;
using System.Linq;
using System.Runtime.InteropServices;

// ReSharper disable once CheckNamespace
namespace UniversityReservationSystem.Interface.Models
{
    public class ExerciseRoom : IRoom
    {
        public int NumOfTables
        {
            get
            {
                return GetExerciseRoomNumOfTables(Ptr);
            }
        }
        public int NumOfChairs
        {
            get
            {
                return GetExerciseRoomNumOfChairs(Ptr);
            }
        }

        public ExerciseRoom(IntPtr thisPtr) : base(thisPtr) { }

        public ExerciseRoom(string name, int capacity, int numOfChairs, int numOfTables)
            : base(CreateNewExerciseRoom(name, capacity, numOfChairs, numOfTables)) { }

        public void Edit(string name, int capacity, int numOfChairs, int numOfTables)
        {
            EditExerciseRoom(Ptr, name, capacity, numOfChairs, numOfTables);

            OnPropertyChanged("Name");
            OnPropertyChanged("Capacity");
            OnPropertyChanged("NumOfTables");
            OnPropertyChanged("NumOfChairs");
            OnPropertyChanged("AdditionalInfo");

            App.Reservations.Where(x => x.Room.Ptr == Ptr).ToList().ForEach(x => x.InvokePropertyChanged());
        }

        public override string ToString()
        {
            return String.Format("Number of tables: {0}\nNumber of chairs: {1}",
                NumOfTables, NumOfChairs);
        }

        #region InterOp Stuff

        [DllImport("UniversityReservationSystem.Backend.dll")] private static extern int GetExerciseRoomNumOfTables(IntPtr exRoomPtr);
        [DllImport("UniversityReservationSystem.Backend.dll")] private static extern int GetExerciseRoomNumOfChairs(IntPtr exRoomPtr);
        [DllImport("UniversityReservationSystem.Backend.dll")] private static extern IntPtr CreateNewExerciseRoom(string name, int capacity, int numOfChairs, int numOfTables);
        [DllImport("UniversityReservationSystem.Backend.dll")] private static extern IntPtr EditExerciseRoom(IntPtr exRoomPtr, string name, int capacity, int numOfChairs, int numOfTables);

        #endregion
    }
}
