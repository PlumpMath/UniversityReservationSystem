using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Data;
using UniversityReservationSystem.Interface.ViewModels;

namespace UniversityReservationSystem.Interface.Helpers
{
    class RoomTypeToVisibilityConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            var roomType = (RoomType) value;
            var param = System.Convert.ToBoolean(parameter, culture);

            if (param) return roomType == RoomType.Lab ? Visibility.Visible : Visibility.Collapsed;

            return roomType == RoomType.Exercise ? Visibility.Visible : Visibility.Collapsed;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
