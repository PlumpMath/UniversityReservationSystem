using System;

namespace UniversityReservationSystem.Interface.Helpers
{
    public static class DateTimeHelpers
    {
        public static int ToUnixTimestamp(this DateTime dateTime)
        {
            return (int)((dateTime.ToUniversalTime() - new DateTime(1970, 1, 1, 0, 0, 0, 0, DateTimeKind.Utc))).TotalSeconds;
        }

        public static DateTime ToDateTime(this int timeStamp)
        {
            var unixEpochDateTime = new DateTime(1970, 1, 1, 0, 0, 0, 0, DateTimeKind.Utc);
            return unixEpochDateTime.AddSeconds(timeStamp).ToLocalTime();
        }
    }
}
