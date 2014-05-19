using System;
using System.Runtime.InteropServices;

// ReSharper disable once CheckNamespace
namespace UniversityReservationSystem.Interface.Models
{
    public abstract class IPerson : IReservable
    {
        public string FirstName
        {
            get
            {
                return Marshal.PtrToStringAnsi(
                    GetPersonFirstName(Ptr));
            }
        }
        public string LastName
        {
            get
            {
                return Marshal.PtrToStringAnsi(
                    GetPersonLastName(Ptr));
            }
        }

        public virtual string FullName
        {
            get { return FirstName + " " + LastName; }
        }

        protected IPerson(IntPtr thisPtr) : base(thisPtr) { }

        #region InterOp Stuff

        [DllImport("UniversityReservationSystem.dll")] private static extern IntPtr GetPersonFirstName(IntPtr personPtr);
        [DllImport("UniversityReservationSystem.dll")] private static extern IntPtr GetPersonLastName(IntPtr personPtr);

        #endregion
    }
}
