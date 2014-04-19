using System;
using System.Runtime.InteropServices;
using System.Windows;

namespace UniversityReservationSystem.Interface
{
    public partial class App
    {
        [DllImport("UniversityReservationSystem.dll")]
        public static extern bool LoadDB(string filePath);

        [DllImport("UniversityReservationSystem.dll")]
        public static extern bool SaveDB();

        [DllImport("UniversityReservationSystem.dll")]
        public static extern bool FreeDB();

        [DllImport("UniversityReservationSystem.dll")]
        public static extern IntPtr GetGroupByIndex(uint groupIndex);

        [DllImport("UniversityReservationSystem.dll")]
        public static extern uint GetGroupsCount();

        protected override void OnExit(ExitEventArgs e)
        {
            FreeDB();
            base.OnExit(e);
        }
    }
}
