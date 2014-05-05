using System;
using System.Runtime.InteropServices;

namespace UniversityReservationSystem.Interface.Models
{
    public abstract class ISerializable
    {
        public IntPtr Ptr { get; private set; }
        public int Id
        {
            get { return GetID(Ptr); }
        }

        public ISerializable(IntPtr thisPtr)
        {
            Ptr = thisPtr;
        }

        [DllImport("UniversityReservationSystem.dll")]
        private static extern int GetID(IntPtr groupPtr);
    }
}
