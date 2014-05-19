using System;

namespace MonthCalendar
{
    public class ReservationOnCalendar
    {
        private string _subject;
        private DateTime? _startTime;
        private IntPtr _ptr;

        public IntPtr Ptr
        {
            get { return _ptr; }
            set { _ptr = value; }
        }

        public string Subject
        {
            get { return _subject; }
            set
            {
                if ((string.Equals(_subject, value) == false))
                {
                    _subject = value;
                }
            }
        }

        public DateTime? StartTime
        {
            get { return _startTime; }
            set
            {
                if ((_startTime.Equals(value) == false))
                {
                    _startTime = value;
                }
            }
        }
    }
}
