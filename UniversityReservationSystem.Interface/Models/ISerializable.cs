using System;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using UniversityReservationSystem.Interface.Annotations;

namespace UniversityReservationSystem.Interface.Models
{
    public abstract class ISerializable : INotifyPropertyChanged
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

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChangedEventHandler handler = PropertyChanged;
            if (handler != null) handler(this, new PropertyChangedEventArgs(propertyName));
        }

        #region InterOpStuff

        [DllImport("UniversityReservationSystem.Backend.dll")] private static extern int GetID(IntPtr groupPtr);

        #endregion
    }
}
