using System;

namespace MonthCalendar
{
    public class Appointment
    {

        private int _appointmentId;
        private string _subject;
        private string _location;
        private string _details;
        private DateTime? _startTime;
        private DateTime? _endTime;
        private DateTime _reccreatedDate;

    public int AppointmentId
        {
            get { return _appointmentId; }
            set
            {
                if (((_appointmentId == value) == false))
                {
                    _appointmentId = value;
                }
            }
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

        public string Location
        {
            get { return _location; }
            set
            {
                if ((string.Equals(_location, value) == false))
                {
                    _location = value;
                }
            }
        }

        public string Details
        {
            get { return _details; }
            set
            {
                if ((string.Equals(_details, value) == false))
                {
                    _details = value;
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

        public DateTime? EndTime
        {
            get { return _endTime; }
            set
            {
                if ((_endTime.Equals(value) == false))
                {
                    _endTime = value;
                }
            }
        }

        public DateTime ReccreatedDate
        {
            get { return _reccreatedDate; }
            set
            {
                if (((_reccreatedDate == value) == false))
                {
                    _reccreatedDate = value;
                }
            }
        }
    }
}
